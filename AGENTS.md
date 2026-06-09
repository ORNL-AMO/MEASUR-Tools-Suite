# Project Memory

When generating code, always follow the coding standards and conventions in the [Style Guide](../contributing/style-guide.md). When documenting code, always follow the documentation standards in [Documentation](../contributing/documentation.md). If either linked file is not available in context, ask the user to provide it before proceeding.

When tasked to refactor code using namespaces, follow these phases in order. In all phases, maintain a **one file per logical module** rule: each .h/.cpp pair produces exactly one corresponding binding file, one C++ test file, and one wasm test file.

**Phase 1 — Headers and Source**
Update the .h and .cpp files to reflect the new structure.

**Phase 2 — WebAssembly Bindings**
For each .h/.cpp pair, create or update exactly one binding file in bindings-wasm/ (one binding file per logical module, matching its .h and .cpp filenames). If no existing binding file exists for a given pair, create one from scratch following the structure used in processHeat/bindings-wasm/.

**Phase 3 — C++ Unit Tests**
Update the .cpp unit tests in tests/cpp to reflect the new structure. Each .cpp file must have its own dedicated test file. If an existing test file covers multiple classes that are being split into separate .cpp files, split the test file accordingly.

**Phase 4 — WebAssembly Unit Tests**
Update or add a unit test in tests/wasm-mocha for each binding file (one test file per binding file). Move old unit tests from tests/wasm to tests/wasm-mocha and update them to reflect the new structure. Once a test has been successfully migrated, delete the original file from tests/wasm.

**Phase 5 — Documentation**
Update the documentation in the docs/dox-content directory. Organize the content logically following the pattern that has already been established.

**Reference example:** refer to processHeat/ as the canonical example of how to structure the code, WebAssembly bindings, unit tests, and documentation.

**Checklist (verify before finishing):**
- [ ] Phase 1: All .h and .cpp files updated
- [ ] Phase 2: One binding file per .h/.cpp pair; new files created where none existed
- [ ] Phase 3: One C++ test file per .cpp file; split if needed
- [ ] Phase 4: One wasm test file per binding file; old tests/wasm files migrated and deleted
- [ ] Phase 5: Documentation updated and organized

## Context

The MEASUR Tools Suite is a collection of industrial efficiency calculations written in C++ with WebAssembly bindings for browser and Node.js environments. The suite provides computational engines for the [MEASUR](https://github.com/ORNL-AMO/AMO-Tools-Desktop) (Manufacturing Energy Assessment Suite for Utility Reduction) application ecosystem.
