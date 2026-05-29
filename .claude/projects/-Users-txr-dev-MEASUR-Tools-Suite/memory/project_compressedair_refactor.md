---
name: CompressedAir namespace refactoring progress
description: Tracks which compressedAir calculators have been refactored to namespace pattern with docs
type: project
---

Progress on refactoring compressedAir calculators to the namespace pattern (free functions, snake_case structs, full doxygen docs, value_object wasm bindings, dox documentation).

**Completed:**
- `bag_method` — done 2026-05-27
- `decibels_method` — done (pre-existing)
- `estimate_method` — done (pre-existing)
- `orifice_method` — done (pre-existing)
- `receiver_tank` — done (pre-existing)
- `compressed_air_leak_survey` — done 2026-05-29
  - New `include/compressedAir/compressed_air_leak_survey.h` (namespace + enums + full doxygen)
  - New `src/compressedAir/compressed_air_leak_survey.cpp`
  - `include/compressedAir/CompressedAirLeakSurvey.h` → backward-compat wrapper
  - New `bindings-wasm/compressedAir/compressed_air_leak_survey.cpp` (value_object pattern)
  - Old `bindings-wasm/compressedAir/compressedAirLeakSurvey.cpp` → deleted
  - New `tests/cpp/compressedAir/compressed_air_leak_survey.unit.cpp`
  - Old `tests/cpp/compressedAir/CompressedAirLeakSurvey.unit.cpp` → deleted
  - Updated `tests/wasm-mocha/compressedAir/wasm_compressed_air_leak_survey.test.js`
  - New `docs/dox-content/calculators/compressedAir/compressed_air_leak_survey_calculator.dox`

**Why:** Namespace pattern improves readability, enables auto-generated API docs, and makes the codebase consistent for the MEASUR Tools Suite.

**How to apply:** When continuing refactoring, check this list to avoid duplicating completed work.
