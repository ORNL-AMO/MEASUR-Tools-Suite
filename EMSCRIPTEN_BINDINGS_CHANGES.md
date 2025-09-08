# Emscripten Bindings Changes

The following table summarizes the changes made to the Emscripten bindings in the MEASUR Tools Suite. These changes are part of an ongoing effort to improve the usability and maintainability of the codebase.

## Wall Heat Loss Calculator

The `WallLosses` class has been refactored into a namespace called `wall_heat_loss` with many methoids being removed or renamed. The following table outlines the updated emscripten bindings:

| Current Signature                | Previous Signature | Notes                                                                 |
| -------------------------------- | ------------------ | --------------------------------------------------------------------- |
| totalHeatLoss                    | getHeatLoss        | Renamed                                                               |
| convectiveHeatLoss               | ---                | New standalone method to calculate convective heat loss.              |
| radiativeHeatLoss                | ---                | New standalone method to calculate radiative heat loss.               |
| ShapeFactor                      | ---                | New Struct that holds shape factor data (description & factor value). |
| ShapeFactor.surfaceConfiguration | surfaceDescription | New field in ShapeFactor struct that holds the description.           |
| ShapeFactor.value                | shapeFactor        | New field in ShapeFactor struct that holds the factor value.          |
| shapeFactors                     | ---                | New method that returns a vector of ShapeFactor structs.              |

See `wasm_wall_heat_loss.test.js` for usage examples.

## Atmosphere Heat Loss Calculator

The `Atmosphere` class has been removed and its functionality has been integrated into the `atmosphere_heat_loss` namespace. The following table outlines the updated emscripten bindings:

| Current Signature                | Previous Signature | Notes                                                                               |
| -------------------------------- | ------------------ | ----------------------------------------------------------------------------------- |
| atmosphereTotalHeatLoss          | getTotalHeatLoss   | Renamed                                                                             |
| AtmosphereGasType                | ---                | New Struct that holds atmosphere gas type data (description & specific heat value). |
| AtmosphereGasType.gasDescription | getSubstance       | New field in AtmosphereGasType struct that holds the description of the gas.        |
| AtmosphereGasType.specificHeat   | getSpecificHeat    | New field in AtmosphereGasType struct that holds the specific heat of the gas       |
| atmosphereGasTypes               | ---                | New method that returns a vector of AtmosphereGasType structs.                      |

See `wasm_atmosphere_heat_loss.test.js` for usage examples.