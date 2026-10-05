## Plan: Rename fixture_losses to fixture_heat_loss

Rename all `fixture_losses` files to `fixture_heat_loss` and update their include statements across the codebase.

### Steps

1. **Rename header file** from [fixture_losses.h](include/processHeat/losses/fixture_losses.h) to `include/processHeat/losses/fixture_heat_loss.h` and update its header guard from `TOOLS_SUITE_FIXTURELOSSES_H` to `TOOLS_SUITE_FIXTUREHEATLOSS_H`.

2. **Rename source file** from [fixture_losses.cpp](src/processHeat/losses/fixture_losses.cpp) to `src/processHeat/losses/fixture_heat_loss.cpp` and update its `#include` directive.

3. **Rename C++ unit test** from [fixture_losses.unit.cpp](tests/cpp/processHeat/losses/fixture_losses.unit.cpp) to `tests/cpp/processHeat/losses/fixture_heat_loss.unit.cpp` and update its `#include` directive.

4. **Rename JavaScript WASM test** from [wasm_fixture_losses.test.js](tests/wasm-mocha/processHeat/losses/wasm_fixture_losses.test.js) to `tests/wasm-mocha/processHeat/losses/wasm_fixture_heat_loss.test.js`.

5. **Update include statement** in [losses.cpp](bindings-wasm/processHeat/losses/losses.cpp) from `#include "processHeat/losses/fixture_losses.h"` to `#include "processHeat/losses/fixture_heat_loss.h"`.

### Further Considerations

1. **CMakeLists.txt requires no changes** — build system uses glob patterns that automatically pick up renamed files.

2. **Class name FixtureLosses unchanged** — only filenames are being renamed, not the C++ class/symbol names.
