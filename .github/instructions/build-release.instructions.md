---
applyTo: "{CMakeLists.txt,cmake/**,package.json,package-lock.json,.github/workflows/**,scripts/**}"
---

# Build And Release Review Focus

- Preserve separate native and WASM build directories and verify changed targets are exercised.
- Ensure WASM artifacts are copied from the current build into `bin/` before browser tests or npm packaging.
- Check that `client.js`, `client.wasm`, declarations, and package metadata stay aligned.
- Treat changes to release channels, package versions, permissions, secrets, or deployment paths as high-impact and require explicit intent.
- Confirm ready Suite PRs still produce the beta package needed for Desktop validation.
