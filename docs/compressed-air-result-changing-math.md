# Compressed Air Result-Changing Math

This note records the calculation changes made during the compressed-air documentation and trust
review that can change a returned numerical result. It intentionally excludes documentation-only
edits, naming corrections, test-fixture cleanup, and internal refactors that preserve the previous
equations.

## Summary

| Model area | Changed result | When it changes |
|---|---|---|
| Centrifugal modulation/unload segment selection | Package power and power fraction | Capacity inputs between the unload airflow fraction and the incorrectly used unload power fraction |
| Centrifugal modulation/unload inverse normalization | Reported airflow fraction | Power inputs at or above the unload point; dimensional acfm is preserved |
| Short load/unload constructor | No-load power and the resulting load/unload curve | The eight-input constructor is used with an unloaded-load factor other than the former 1 kW default |
| Start/stop pressure correction | Corrected full-load and maximum power | The new constructor identifies the compressor as reciprocating |

## Symbols

- $P$ is package input power in kW.
- $Q$ is delivered airflow in acfm.
- $P_{FL}$ and $Q_{FL}$ are the corrected full-load reference values.
- $f_P=P/P_{FL}$ is power fraction.
- $f_Q=Q/Q_{FL}$ is airflow fraction.
- Subscripts $NL$, $UL$, and $max$ denote no-load, unload-transition, and maximum-flow anchors.

## 1. Centrifugal modulation/unload segment selection

The capacity-based calculation has two linear segments:

$$
f_P=
\begin{cases}
f_{P,NL}+\dfrac{f_{P,UL}-f_{P,NL}}{f_{Q,UL}}f_Q,
& f_Q<f_{Q,UL} \\
f_{P,UL}+\dfrac{1-f_{P,UL}}{f_{Q,max}-f_{Q,UL}}
(f_Q-f_{Q,UL}),
& f_{Q,UL}\le f_Q<f_{Q,max} \\
1, & f_Q\ge f_{Q,max}
\end{cases}
$$

Previously, the implementation selected the low segment using the dimensionally inconsistent test
$f_Q<f_{P,UL}$. It now selects the segment at the airflow anchor, $f_Q<f_{Q,UL}$.

For the regression fixture:

$$
f_{P,NL}=0.157639,\quad
f_{P,UL}=0.910679,\quad
f_{Q,UL}=0.870300,\quad
f_{Q,max}=0.957616
$$

At $f_Q=0.90$, the former branch selection returned $f_P=0.936378$, or 423.52 kW.
The corrected high segment returns $f_P=0.941061$, or 425.64 kW. Values below the unload airflow
fraction and values at or above maximum airflow retain their established segment behavior.

## 2. Centrifugal modulation/unload inverse normalization

Above unload, the former power-to-airflow path calculated an intermediate fraction on a maximum-flow
basis:

$$
g_Q=\frac{Q}{Q_{max}}
=\frac{Q_{UL}}{Q_{max}}
+\left(1-\frac{Q_{UL}}{Q_{max}}\right)
\frac{f_P-f_{P,UL}}{1-f_{P,UL}}
$$

It correctly reconstructed dimensional airflow as $Q=Q_{max}g_Q$, but incorrectly returned $g_Q$
in the API field documented as $f_Q=Q/Q_{FL}$.

The corrected inverse uses the full-load basis throughout:

$$
f_Q=f_{Q,UL}
+(f_{Q,max}-f_{Q,UL})
\frac{f_P-f_{P,UL}}{1-f_{P,UL}}
$$

$$
Q=Q_{FL}f_Q
$$

For $f_P=0.94$, both implementations produce approximately 2820.95 acfm. The returned airflow
fraction changes from 0.93875 on the incorrect maximum-flow basis to 0.898963 on the documented
full-load basis. Passing 0.898963 through the capacity-based path now returns $f_P=0.94$, restoring
the expected round trip.

## 3. Short load/unload constructor no-load power

The short load/unload constructor accepts an unloaded-load factor $f_{NL}$ from 0 to 1. Previously,
that argument was ignored because the call resolved to the longer constructor, whose default
no-load power was 1 kW. The effective previous behavior was therefore:

$$
P_{NL}=1\ \text{kW}
$$

The short constructor now derives no-load power from the supplied fraction:

$$
P_{NL}=f_{NL}P_{FL}
$$

This value enters the no-load fraction, off-load stage power, blowdown and reload averages, cycle
energy, and the minimum accepted measured-power point. For example, with $P_{FL}=100$ kW and
$f_{NL}=0.60$, the corrected no-load power is 60 kW. A requested power fraction of 0.59 is now below
no-load and returns the model's zero result; previously the implicit 1 kW no-load value allowed that
59 kW point onto the curve. Longer constructors that explicitly supply no-load kW are unchanged.

## 4. Start/stop compressor-type pressure correction

Pressure-corrected package power is calculated as:

$$
P_{adj}=F_P\frac{P_{atm}}{P_{in}}
\frac{BHP_{FL}(0.746)}{\eta_m}R_P
$$

where

$$
R_P=
\frac{\left(\dfrac{P_{op,g}+P_b}{P_b}\right)^{(n-1)/n}-1}
{r_{rated}^{(n-1)/n}-1}
$$

The start/stop model previously always used the screw-compressor pressure base,
$P_b=P_{rated,in}$. The new compressor-type overload selects:

$$
P_b=
\begin{cases}
P_{rated,in}, & \text{screw compressor} \\
P_{atm}, & \text{reciprocating compressor}
\end{cases}
$$

For the regression fixture, the screw correction produces 90.0736 kW and the reciprocating
correction produces 89.3967 kW. The retained four-input constructor still defaults to screw, so
existing callers keep their previous result. A result changes only when a caller uses the new
overload and identifies the compressor as reciprocating.

## Math-related changes that do not alter results by themselves

- Three-phase electrical power was centralized as
  $P=VI(1.732)PF/1000$. The equation is unchanged; tests now use power factor as a realistic 0-to-1
  value with correspondingly scaled current.
- The 0.746 bhp-to-kW factor was moved to a shared constant without changing its value.
- The load/unload stage equations were consolidated into one cycle-state calculation used by both
  direct evaluation and inverse sampling. The five stage-energy equations, 76 equal intervals,
  77 evaluated points, and sixth-order inverse fit were retained.
- Catalog BHP, percentage, sentinel, and specific-package-power metadata were corrected, but stored
  catalog values and compressor equations were not changed by those labeling fixes.
