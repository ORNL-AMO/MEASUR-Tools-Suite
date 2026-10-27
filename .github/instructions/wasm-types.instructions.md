---
applyTo: "{bindings-wasm,ts_def,tests/wasm-mocha}/**/*.{cpp,ts,js}"
---

# WebAssembly And TypeScript Review Focus

- Match embind runtime names and kinds exactly to declarations, module exports, and typed tests.
- Verify cleanup semantics for runtime classes, registered vectors, returned objects, and nested runtime values.
- Keep type-only interfaces out of runtime module properties.
- Require units or explicit dimensionless status for public numeric TypeScript fields, parameters, and returns.
- Confirm WASM-facing tests use a newly built and staged module rather than stale `bin/client.*` artifacts.
