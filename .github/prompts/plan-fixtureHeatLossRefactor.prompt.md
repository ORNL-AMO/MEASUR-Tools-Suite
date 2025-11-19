## Plan: Refactor fixture heat loss calculator to namespace pattern

Refactor the class-based `FixtureLosses` implementation into a namespace-based function matching the pattern established by `wall_heat_loss` and `atmosphere_heat_loss`. This includes converting the class to `namespace fixture_heat_loss`, implementing a `totalHeatLoss()` function, and creating comprehensive Doxygen documentation in the `.dox` file.

### Steps

1. **Refactor [fixture_heat_loss.h](include/processHeat/losses/fixture_heat_loss.h)** to replace the `FixtureLosses` class with `namespace fixture_heat_loss` containing a `totalHeatLoss()` function signature matching the atmosphere pattern (5 double parameters: `specific_heat`, `feed_rate`, `initial_temperature`, `final_temperature`, `correction_factor`).

2. **Refactor [fixture_heat_loss.cpp](src/processHeat/losses/fixture_heat_loss.cpp)** to implement the `totalHeatLoss()` function within the namespace, containing the same calculation: `feed_rate * specific_heat * (final_temperature - initial_temperature) * correction_factor`.

3. **Create comprehensive documentation** in `docs/calculators/fixture_heat_loss_calculator.dox` with three `@defgroup` sections: main calculator description, formula derivation with symbol tables, and optionally fixture material data (similar to `atmosphere_heat_loss_calculator.dox` structure).

4. **Update bindings** in [bindings-wasm/processHeat/losses/losses.cpp](bindings-wasm/processHeat/losses/losses.cpp) to expose the new namespace function instead of the class-based interface.

5. **Update or create unit tests** in `tests/cpp/processHeat/losses/` to test the new `fixture_heat_loss::totalHeatLoss()` function instead of the `FixtureLosses` class methods.

### Further Considerations

1. **Should fixture material data be included?** If there are common fixture types with known specific heat values (like atmosphere gas data or wall materials), add a `@defgroup fixture_materials` section with a `FixtureMaterial` struct and `fixtureLibrary()` accessor function.

2. **Breaking change handling?** The class-based API will be removed—confirm if any external code depends on `FixtureLosses` class, or if version migration/deprecation steps are needed.
