# Build Guide

This document centralizes all build, test, packaging, WebAssembly, and Docker workflows for the MEASUR Tools Suite.

---

## 1. Overview

The project provides:
- A C++ static library: `measur_tools_suite`
- A C++ CLI executable: `measur_tools_suite` (target `TOOLS_SUITE_main`)
- Optional C++ unit tests (Catch2 based)
- Optional WebAssembly build producing `client.js` + `client.wasm`
- Optional binary/package artifacts (via CPack)

All builds are driven by CMake (minimum 3.5). WebAssembly builds use Emscripten toolchain integration via `emcmake` / `emmake`.

---

## 2. Supported Platforms

| Platform | Status          | Notes                                                    |
| -------- | --------------- | -------------------------------------------------------- |
| Linux    | Fully supported | Primary development environment                          |
| macOS    | Supported       | Uses same CMake flow                                     |
| Windows  | Supported       | MinGW, MSYS2, or Visual Studio toolchain; WASM via emsdk |

---

## 3. Prerequisites

Install only what you need for the scenario you plan to use.

### Core (C++ build)

- GCC/Clang/MSVC with C++20 support
- CMake >= 3.5
- make or ninja (optional alternative generator)

### WebAssembly

- Emscripten SDK (emsdk) latest
	```bash
	./emsdk install latest
	./emsdk activate latest
	source ./emsdk_env.sh   # (emsdk_env.bat on Windows)
	```
	Repeat `source ./emsdk_env.sh` for every new shell or add it to your profile.

### Tests (WASM & JS harness)

- Node.js (LTS) + npm

### Documentation (optional)

- Doxygen >= 1.14.0

### Packaging (optional)

- CPack (bundled with CMake)

### Docker (optional convenience)

- Docker & Docker Compose

---

## 4. CMake Options

| Option                   | Default | Purpose                                                              |
| ------------------------ | ------- | -------------------------------------------------------------------- |
| `BUILD_TESTING`          | ON      | Build C++ unit tests (`cpp_tests`)                                   |
| `BUILD_WASM`             | OFF     | Build WebAssembly module (`client`)                                  |
| `BUILD_PACKAGE`          | OFF     | Enable install + packaging targets                                   |
| `STEAM_MODELER_LOGGING`  | 0       | Enable verbose SteamModeler debug output (see [§10](#10-steammodeler-debug-logging)) |

Mutually influential behavior:
- When `BUILD_WASM=ON` the build disables `BUILD_TESTING` & `BUILD_PACKAGE` internally (see `CMakeLists.txt`). Toggle intentionally—do not expect tests with WASM in a single configure.

> **Tip:** Use dedicated build directories (for example, `build-cpp` and `build-wasm`) instead of reconfiguring the same directory when you switch scenarios. This avoids stale cache entries and conflicting options.

---

## 5. Common Build Scenarios

| Scenario                     | Commands (summary)                                                                                                                            |
| ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| Standard C++ (library + CLI) | `cmake -S . -B build-cpp && cmake --build build-cpp` (Windows: add `--config Release` or desired configuration)                               |
| C++ Tests                    | (after standard build) run `./build-cpp/bin/cpp_tests` (Linux/macOS) or `./build-cpp/Debug/cpp_tests.exe` (Windows; use `Release/` as needed) |
| WASM Module                  | `emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON` then `emmake make -C build-wasm`                                                           |
| WASM Tests (browser)         | `npm install && npm run test:browser`                                                                                                         |
| Documentation                | `doxygen Doxyfile`                                                                                                                            |
| Package                      | `cmake -S . -B build-pkg -DBUILD_PACKAGE=ON -DBUILD_TESTING=OFF && cmake --build build-pkg --target package`                                  |

---

## 6. Native Build Instructions

### 6.1 Standard C++ Build

```bash
git clone <repo-url> MEASUR-Tools-Suite
cd MEASUR-Tools-Suite
cmake -S . -B build-cpp  # add -G "Ninja" or other generator if desired
cmake --build build-cpp  # builds library + CLI + tests (if enabled)
```
(On Windows multi-config generators (e.g., Visual Studio), specify a configuration: `cmake --build build-cpp --config Release` (or `Debug`).)

Artifacts appear under `build-cpp/bin/` or on Windows `build-cpp/Debug/` or `build-cpp/Release/`.

### 6.2 Running the CLI

```bash
./build-cpp/bin/measur_tools_suite --help
```
(Adjust path for Windows: `./build-cpp/Debug/measur_tools_suite.exe` or `./build-cpp/Release/measur_tools_suite.exe`.)

### 6.3 C++ Unit Tests

If `BUILD_TESTING=ON` (default in non-WASM builds):
```bash
./build-cpp/bin/cpp_tests
```
Windows (multi-config):
```bash
./build-cpp/Debug/cpp_tests.exe
# or
./build-cpp/Release/cpp_tests.exe
```

### 6.4 WebAssembly Build

#### Prerequisites: Emscripten SDK Setup

If you haven't installed Emscripten SDK yet:
```bash
# Clone emsdk repository
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate latest version
./emsdk install latest
./emsdk activate latest
```

#### Activate Emscripten Environment

Before building, activate emsdk in your current shell:
```bash
# Linux/macOS
source /path/to/emsdk/emsdk_env.sh

# Windows
emsdk_env.bat
```

To avoid running this every time, add it to your shell profile:
```bash
# Linux/macOS (add to ~/.bashrc or ~/.zshrc)
echo 'source /path/to/emsdk/emsdk_env.sh' >> ~/.bashrc

# Then reload
source ~/.bashrc
```

Verify activation:
```bash
emcc --version  # should show Emscripten version
```

#### Build WebAssembly Module

With emsdk activated, configure and build:
```bash
emcmake cmake -DBUILD_WASM=ON
emmake make
```
Artifacts appear under `bin/`

### 6.5 WebAssembly Usage Example

```js
// Initialize module
const moduleFactory = (await import('/path/to/client.js')).default;
const toolsSuiteModule = await moduleFactory({
	locateFile: (filename) => '/path/to/client.wasm'
});

// Example call
const totalHeatLoss = toolsSuiteModule.wallTotalHeatLoss(
	500, 80, 225, 10, 0.9, 1.394, 1
);
```

### 6.6 WebAssembly Tests (Browser)

Run from repository root (uses mocha):
```bash
npm install
npm run test:browser
```
Mocha tests reside in `tests/wasm-mocha/`. Re-running tests after editing JS/WASM test files does not require a rebuild unless C++ sources changed. Rerun `npm install` only when dependencies change or the lockfile updates.

### 6.7 Documentation Generation

```bash
doxygen Doxyfile
```
Output: `docs/html/index.html`.

### 6.8 Packaging

Single-config (Linux/macOS):
```bash
cmake -S . -B build-pkg -DBUILD_PACKAGE=ON -DBUILD_TESTING=OFF
cmake --build build-pkg --target package
```
Windows (multi-config):
```bash
cmake -S . -B build-pkg -DBUILD_PACKAGE=ON -DBUILD_TESTING=OFF
cmake --build build-pkg --config Release --target package
```
Resulting archives appear in the build directory (`.tar.gz` / `.zip`).

---

## 7. Docker Workflow

Docker provides an automated, containerized build environment that handles all dependencies and produces both native (C++) and WebAssembly artifacts without manual setup.

### 7.1 Prerequisites

- Docker Engine
- Docker Compose

Installation varies by platform:
```bash
# Ubuntu/Debian
sudo apt-get update && sudo apt-get install -y docker.io docker-compose-plugin
sudo systemctl enable --now docker
sudo usermod -aG docker $USER
newgrp docker  # activate group immediately

# macOS / Windows
# Install Docker Desktop from https://docker.com
```

### 7.2 Building with Docker

From repository root:
```bash
docker compose up -d
```

This command:
- Builds a Docker image with CMake, Emscripten SDK, Node.js, and Chrome
- Starts a container named `measur-tools-suite-build`
- Executes a full clean build of both native C++ and WebAssembly targets
- Keeps the container running for inspection

### 7.3 Monitoring Build Progress

View real-time logs:
```bash
docker compose logs -f
```

View last N lines:
```bash
docker compose logs --tail 20
```

### 7.4 Accessing Build Artifacts

Build outputs appear in host directories (via volume mounts):
- `build-cpp/bin/cpp_tests` - Native C++ test executable
- `build-cpp/bin/measur_tools_suite` - Native CLI executable
- `build-cpp/lib/libmeasur_tools_suite.a` - Static library
- `bin/client.js` + `client.wasm` - WebAssembly module

Run C++ tests on host:
```bash
./build-cpp/bin/cpp_tests
```

Run WASM tests on host:
```bash
npm install
npm run test:browser
```

### 7.5 Working Inside the Container

Exec into running container:
```bash
docker exec -it measur-tools-suite-build /bin/bash
```

Inside container, source tree is at `/home/MEASUR-Tools-Suite/`:
```bash
# Run C++ tests
./build-cpp/bin/cpp_tests
# Windows: ./build-cpp/Debug/cpp_tests.exe (or Release)

# Run WASM tests
npm run tests

# Exit container
exit
```

### 7.6 Stopping and Cleaning Up

Stop container (preserves build artifacts on host):
```bash
docker compose down
```

Remove all build artifacts and start fresh:
```bash
rm -rf build-cpp build-wasm bin
docker compose up -d
```

Rebuild Docker image (if Dockerfile changed):
```bash
docker compose build --no-cache
docker compose up -d
```

### 7.7 Volume Mount Behavior

The `docker-compose.yml` mounts host directories into the container:
- `../MEASUR-Tools-Suite:/home/MEASUR-Tools-Suite` - Source code (editable from host)
- `./bin:/home/MEASUR-Tools-Suite/bin` - WASM build outputs
- `./build-cpp:/home/MEASUR-Tools-Suite/build-cpp` - Native build outputs
- `./build-wasm:/home/MEASUR-Tools-Suite/build-wasm` - WASM build outputs

Changes to source files on the host are immediately visible inside the container, enabling iterative development.

### 7.8 Docker Build Process Details

The container executes the following sequence:
1. Cleans prior `bin/`, `build-cpp/`, and `build-wasm/` contents
2. Configures native build: `cd build-cpp && cmake ..`
3. Builds native targets: `cmake --build . -j 8`
4. Configures WASM build: `cd build-wasm && emcmake cmake -DBUILD_WASM=ON ..`
5. Builds WASM targets: `emmake make -j 8`
6. Copies WASM artifacts to mounted `bin/` directory
7. Installs Node dependencies: `npm install`
8. Runs browser-based WASM tests using headless Chrome: `npm run tests`
9. Sleeps indefinitely to keep container accessible

### 7.9 Docker Troubleshooting

**Permission denied on `/var/run/docker.sock`:**
```bash
sudo usermod -aG docker $USER
newgrp docker  # or log out/in
```

**Container exits immediately:**
```bash
docker compose logs  # check for build errors
```

**Stale build artifacts:**
```bash
rm -rf build-cpp build-wasm bin
docker compose up -d
```

**Emscripten errors inside container:**
```bash
docker exec -it measur-tools-suite-build /bin/bash
source /home/emsdk/emsdk_env.sh
emcc --version  # verify Emscripten is active
```

---

## 8. Troubleshooting (Native Builds)

- Multiple compilers: specify generator `-G "Ninja"` or `-G "Unix Makefiles"`; on MinGW use `-G "MinGW Makefiles"`.
- Switching between WASM and native builds: create separate build directories (`build-cpp`, `build-wasm`). Re-configuring in-place can leave incompatible flags.
- WASM link failures for undefined symbols: build excludes tests and packaging; confirm `BUILD_WASM=ON` only.
- Windows binary paths: look under `Debug/` or `Release/` if using multi-config IDE/toolchain.
- Emscripten environment not active: rerun `source ./emsdk_env.sh`.
- Stale cache: remove build directory (`rm -rf build-*`) instead of editing `CMakeCache.txt` manually.

---

## 9. Quick Reference

### Native Builds

```bash
# Native build (library + CLI + tests)
cmake -S . -B build-cpp && cmake --build build-cpp
# Windows multi-config generators: cmake --build build-cpp --config Release

# Run C++ tests
./build-cpp/bin/cpp_tests

# WASM build
emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON && emmake make -C build-wasm

# WASM browser tests
npm install && npm run test:browser  # install needed only on first run

# Docs
doxygen Doxyfile

# Package
cmake -S . -B build-pkg -DBUILD_PACKAGE=ON -DBUILD_TESTING=OFF && cmake --build build-pkg --target package
# Windows multi-config generators: cmake --build build-pkg --config Release --target package
```

### Docker Builds

```bash
# Start automated build
docker compose up -d

# Monitor progress
docker compose logs -f

# Run tests on host
./build-cpp/bin/cpp_tests
npm run test:browser

# Access container
docker exec -it measur-tools-suite-build /bin/bash

# Stop container
docker compose down
```

---

## 10. SteamModeler Debug Logging

The SteamModeler and all of its supporting classes include verbose debug logging that is **disabled by default** so it never appears in production or WebAssembly builds.

The toggle lives in a single header: `include/steamModeler/util/SteamModelerLogger.h`

```cpp
#ifndef STEAM_MODELER_LOGGING
#define STEAM_MODELER_LOGGING 0   // 0 = silent (default), 1 = verbose
#endif
```

### Enabling logging

**Option A — Edit the header (local debug session)**

Change the define to `1` and rebuild:

```cpp
#define STEAM_MODELER_LOGGING 1
```

**Option B — Compiler flag (no source changes required)**

Pass the flag at configure time:

```bash
cmake -S . -B build-cpp -DSTEAM_MODELER_LOGGING=1
cmake --build build-cpp
```

Or directly via the compiler (without CMake):

```bash
make CXXFLAGS="-DSTEAM_MODELER_LOGGING=1"
```

> **Note:** Always revert to `0` (or remove the flag) before building the WASM module for production. Debug output through `std::cout` is visible in the browser DevTools console when `STEAM_MODELER_LOGGING=1` is set in a WASM build.

---

If any scenario you need is missing here, open an issue or submit a PR to extend this guide.
