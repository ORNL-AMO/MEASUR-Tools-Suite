#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "${script_dir}/.." && pwd)"
build_dir="${MEASUR_WASM_BUILD_DIR:-build-wasm}"
build_jobs="${MEASUR_WASM_BUILD_JOBS:-4}"

cd "${repo_root}"

for command_name in emcmake emmake cmake; do
    if ! command -v "${command_name}" >/dev/null 2>&1; then
        echo "Required command not found: ${command_name}" >&2
        exit 1
    fi
done

emcmake cmake -S . -B "${build_dir}" -DBUILD_WASM=ON
emmake make -C "${build_dir}" -j "${build_jobs}"

for artifact in client.js client.wasm; do
    source_path="${build_dir}/bin/${artifact}"
    if [[ ! -f "${source_path}" ]]; then
        echo "Expected WASM artifact was not produced: ${source_path}" >&2
        exit 1
    fi
done

mkdir -p bin
rm -f bin/measur_tools_suite.js bin/measur_tools_suite.wasm
cp "${build_dir}/bin/client.js" bin/client.js
cp "${build_dir}/bin/client.wasm" bin/client.wasm

echo "Staged current WASM artifacts:"
ls -l bin/client.js bin/client.wasm
