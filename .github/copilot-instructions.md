When generating code, always follow the coding standards and conventions in the [Style Guide](../contributing/style-guide.md).

When documenting code, always follow the documentation standards in [Documentation](../contributing/documentation.md).


When tasked to refactor code:
- First update the .h and .cpp files to reflect the new structure.
- Then find the corresponding web assembly bindings in bindings-wasm/ and update them by creating a new file so that there is a web assembly binding file for each .h and .cpp file.
- Then update the .cpp unit tests in tests/cpp to reflect the new structure. Again make sure there is an individual test file for each .cpp file.
- Then update or add a unit test in tests/wasm-mocha to test the web assembly bindings. Again make sure there is an individual test file for each web assembly binding file. Old unit tests may be in the tests/wasm directory, the can be moved to tests/wasm-mocha and updated to reflect the new structure. Old tests can be deleted as they are no longer used.
- Finally, update the documentation in the docs/dox-content directory. Organize the content logically following the pattern that has already been established.
- During refactoring, refer to processHeat/ as an example of how to structure the code, web assembly bindings, unit tests, and documentation.