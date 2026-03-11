# Process Cooling VB Port — Porting Notes & Potential Updates

Below contains discrepancies, and suggested updates
identified by an LLM during the C++ port of the original VB (CWSAT) implementation.

---

## 1. Missing Capacity-Index Lookup in `annualChillerEfficiencyProfileARI()`

**File:** `src/processCooling/process_cooling.cpp`
**Function:** `ProcessCooling::annualChillerEfficiencyProfileARI()`

### Background

When `ChillerInput::isFullLoadEffKnown` is `false`, the function selects a row from one
of the Method 1 lookup tables (`ArrayCDataWater`, `ArrayRDataWater`, `ArraySDataWater`,
`ArrayRDataAir`, `ArraySDataAir`) using a local variable `idx`:

```cpp
int idx = capacityIndex[c];
```

Each lookup table row is keyed by a capacity tier (in tons of refrigeration), stored in
column 0 of each row. The intent — documented in the comment at the declaration site — is
that `capacityIndex[c]` holds the row index whose capacity tier best matches
`chillers[c].capacity` (`ChillerInput::capacity`, units: tons).

### The Bug

`capacityIndex` is declared as:

```cpp
vector<int> capacityIndex(numChillers, 0);
```

It is **never populated** with a value derived from `ChillerInput::capacity`. The
three conditional blocks that follow the declaration are clamping guards intended to
keep a pre-computed index within valid bounds for each chiller type:

| Condition | Guard |
|---|---|
| `ChillerCompressorType::Centrifugal` + `CoolingSystemType::Water` | clamp to `<= 1` (`ArrayCDataWater` has 2 rows) |
| `ChillerCompressorType::Screw` + `CoolingSystemType::Water` | clamp to `<= 8` (`ArraySDataWater` has 9 rows) |
| `ChillerCompressorType::Reciprocating` + `CoolingSystemType::Air` | remap index for gap in `ArrayRDataAir` (indices 8–16 are absent) |

Because the index starts at 0, none of these guards (`> 1`, `> 8`, `> 7`, `> 16`) ever
fire. As a result, `idx` is always `0` for every chiller, and the first row of every
lookup table is unconditionally used regardless of `ChillerInput::capacity`.

### TODO

Investigate the original VB source to recover the capacity-matching loop. The expected
logic should iterate over the relevant lookup table's capacity column (index `[row][0]`)
and find the row whose capacity tier is the closest match to `chillers[c].capacity`,
then assign that row index to `capacityIndex[c]` before the clamping guards are applied.

The fix would be inserted between the declaration of `capacityIndex` and the existing
clamping guards.

---

## 2. `capacityIndex` Size Should Be `numChillers`, Not a Magic Number

**File:** `src/processCooling/process_cooling.cpp`
**Function:** `ProcessCooling::annualChillerEfficiencyProfileARI()`

### Background

`capacityIndex` is a per-chiller vector used to track each chiller's row index into the
capacity-based lookup tables. It is currently declared with a hard-coded size:

```cpp
vector<int> capacityIndex(31, 0);
```

The magic number `31` is the row count of the largest lookup table in the function
(`ArraySDataAir`, 31 rows). This has no relationship to the number of chillers in the
system (`numChillers`) and creates an oversized, misleading allocation.

### Why It Should Change

The vector is indexed by chiller (`capacityIndex[c]` where `c < numChillers`), so its
size should be `numChillers`. Using `31` is a VB-era artifact — VB arrays were commonly
statically sized to the maximum anticipated value. In C++ the correct size is dynamic and
caller-driven.

### TODO

Change the declaration to:

```cpp
vector<int> capacityIndex(numChillers, 0);
```

This should be done in conjunction with resolving §1 (the missing capacity-matching loop),
since both issues stem from the same block of incompletely ported VB logic.

---
