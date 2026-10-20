#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "${script_dir}/.." && pwd)"

cd "${repo_root}"

"${script_dir}/build-wasm.sh"
./node_modules/.bin/tsc --noEmit
npm run tests

echo "Verified staged WASM artifacts:"
ls -l bin/client.js bin/client.wasm
