# Emscripten Bindings Changes

The following summarizes the changes made to the Emscripten bindings in the MEASUR Tools Suite. These changes are part of an ongoing effort to improve the usability and maintainability of the codebase.

## Wall Heat Loss Calculator

The `WallLosses` class has been removed and its functionality has been integrated into the `wall_heat_loss` namespace. See `wasm_wall_heat_loss.test.js` for usage examples.

## Atmosphere Heat Loss Calculator

The `Atmosphere` class has been removed and its functionality has been integrated into the `atmosphere_heat_loss` namespace. See `wasm_atmosphere_heat_loss.test.js` for usage examples.