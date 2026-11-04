# HI 2020 Pump Efficiency PCHIP Handoff

## Workflow metadata and approval

- Lifecycle: active; implementation in progress, not released.
- Created: 2026-11-03; updated: 2026-11-04. Owner: Codex.
- Suite baseline: `8fa57f453d9bb9b43ee8b73555ae5dd8f35b6e7a`, branch `pump-eff-changes`.
- Desktop baseline: `cbf65e9dd1dcecc2b7da9deca0c2c3da4fa2a542` (pending PumpResult PR #9054).
- Desktop implementation: `/private/tmp/desktop-pump-efficiency-pchip`, branch `codex/pump-efficiency-pchip`.
- Coordination: [Desktop #9063](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9063),
  [Suite #458](https://github.com/ORNL-AMO/MEASUR-Tools-Suite/issues/458), following
  [Desktop #9059](https://github.com/ORNL-AMO/AMO-Tools-Desktop/issues/9059).
- Suite/Desktop PRs: pending final internal review.
- User explicitly approved this behavioral update, NaN numeric failure contract, axial mapping,
  and preservation of saved estimates through specified-efficiency migration on 2026-11-03.
- Earlier behavior-preserving refactor evidence remains in [its handoff](pump-efficiency-refactor.md).

## Module and runtime contract

Three HI curve fits become raw-coordinate, non-extrapolating PCHIP tables. The reusable `util/pchip`
module is C++ only. Pump modules remain one header/source/binding/declaration/test/document per module.

| Surface | Before | After | Embind / ownership | Units and compatibility |
| --- | --- | --- | --- | --- |
| `calculateOptimalPrePumpEfficiency` | Curve-fit scalar | HI 2020 interpolated scalar; NaN unavailable | Function + plain input; no cleanup | Percent; signature preserved, behavior changed |
| `calculateOptimalSpecificSpeedCorrection` | Polynomial scalar | Interpolated points / 100; NaN unavailable | Function + plain input; no cleanup | Fractional decrement; signature preserved |
| `calculateOptimalDeviationFactor` | Log-flow fit | 1 + positive deviation / 100; NaN unavailable | Scalar function; no cleanup | Multiplier; signature preserved |
| `calculateOptimalPumpEfficiency` / `calculatePumpEfficiency` | Unrestricted arithmetic | Same combination, validated duty; NaN unavailable | Functions + plain input/result; no cleanup | Fractions; `{average,max}` unchanged |
| `getPumpEfficiencyLimits` | Absent | Plain supported flag and inclusive flow/speed bounds | Function + value result; no cleanup | US gpm and US customary specific speed; additive |

Specific speed, viscosity formula, units, runtime enums and fractional stage counts remain unchanged.
Axial flow retains V base / nonvertical speed correction. Specified and PD paths bypass HI estimation.

## Engineering provenance and decisions

- Baseline tables: engineering `PCHIP_Methodology_Dev._Ref.docx`, updated 2026-09-23,
  supplied by user; HI 20.3-2020. C/H were digitized by engineering.
- Tangents: SciPy PchipInterpolator weighted harmonic mean and endpoint sign/shape restrictions;
  explicitly use `extrapolate=False` for reference goldens.
- Interpolation uses raw US gpm / specific speed, never log flow.
- Average = `(basePercent / 100) * viscosityCorrection - correctionPoints / 100`;
  maximum = `average * (1 + positiveDeviationPercent / 100)`. No output clamping.
- ANSI/API duty Q=2000 US gpm, n=2000 rpm, nu=1.107 cSt, H=137 ft, stages=1:
  baseline average/max `0.83933686357794668 / 0.86957345321252744`;
  preliminary new values `0.839835675595905 / 0.8673271191483607`.
- Release gates: engineering confirmation of digitized C/H, H's 300–1300 US gpm range and axial mapping;
  obtain companion workbook and verify H at 400 US gpm (70.775 vs printed 70.77%).

## Desktop impact and migration

Preserve exact usable saved `pump_specified` percentages, convert legacy rotodynamic scenarios to style 11,
retain original physical style and provenance, and mark incomplete estimates for review. Never substitute
measured baseline efficiency. Migration is idempotent and covers startup/import, baseline/modifications.
Connected inventory must use retained physical style without restoring automatic estimation or changing
inventory classification. Explicit HI re-estimation replaces a saved value only after success.
Wrappers adopt stateless APIs; forms/graphs use Suite limits and never save NaN. Historical graph points
remain identifiable. Existing energy/cost/savings results must be preserved after migration.

## Package coordination and validation

Change classification: behavioral + additive limits API + saved-data migration. Exact beta/final versions:
not published. Root/process-flow pins and npm-generated lockfiles must stay aligned. No final release before
engineering and Desktop acceptance. Local artifact verification is distinct from published-beta acceptance.

Author validation: full native build/tests passed (8626 assertions / 362 cases). Independent SciPy
1.17.1 goldens use extrapolate=False: 267 base, 116 correction, 19 deviation and 34 composite samples.
Fresh rebuilt/staged WASM passed 301 browser tests after the enum smoke test adopted the new result.
Types, Markdown links and whitespace passed. Doxygen generated the updated pages with the existing
BibTeX failure and unrelated warnings; no new pump/PCHIP diagnostic. All 28 printed document examples
match stated precision. SciPy's H-at-400 value is 70.77499999999999 (Python rounds to 70.77%).

Final independent review by `pchip_review`: **ready with documented follow-up; no actionable findings**.
Intended base: `epic-pump-eff-refactor`, `8fa57f453d9bb9b43ee8b73555ae5dd8f35b6e7a`;
reviewed source head: `18f1e1604150e76729f07fd6697a1bdf096d6358`. Reviewer independently ran the full
8626-assertion / 362-case native suite and 3371 focused assertions / 13 cases, types, links and complete
diff whitespace. Source coordinates matched engineering data; browser/JSON goldens and capture SHA-256
matched. Reviewer inspected successful 301-test rebuilt-WASM evidence. No unresolved P0–P2 findings.
Only handoff review metadata follows the reviewed source. Remaining follow-up: existing BibTeX/tooling
limits, exact published-beta Desktop acceptance and engineering/workbook release gates.

Durable synthetic evidence: `docs/development/evidence/pump-pchip-{before,after}.csv` and
`pump-pchip-differences.json`: 55 duties, 8 now unavailable. The report records the immutable old
capture SHA-256, separate from the earlier behavior-preserving refactor evidence.

Desktop local validation uses this exact fresh WASM and matching declarations in its private ignored
node_modules. Existing package pins are not claimed as PCHIP beta acceptance. Web build and 257
process-flow tests passed; process-flow typecheck passed. Final local Desktop suite: 1666 tests passed,
with application/spec typechecks and the immutable 72-scenario gate unchanged. Desktop candidate
`96c39cccca82db3cdb8a3f52864cf2c28a471e7f` is independently reviewing against its exact #9054 base.
Published-beta adoption remains pending; see Desktop `docs/development/pump-efficiency-pchip.md`.
