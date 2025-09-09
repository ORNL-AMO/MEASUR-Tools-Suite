# MEASUR Tools Suite  

## Update (08/25/2025)

The MEASUR Tools Suite is currently undergoing a major update to improve usability and maintainability. This includes a refactoring of the codebase to follow consistent practices, better organization, and enhanced documentation around the engineering aspects of the calculations. To follow the progress of this update, please refer to the [Roadmap](ROADMAP.md).

## About

The MEASUR Tools Suite is a collection of industrial efficiency calculations written in C++ and with bindings for compilation to WebAssembly. The tool suite web assembly module is used for calculations with the MEASUR application.

For more information about the MEASUR ecosystem visit [https://industrialresources.ornl.gov/measur](https://industrialresources.ornl.gov/measur)

Hosted documentation can be found at [https://industrialresources.ornl.gov/measur/suite/docs](https://industrialresources.ornl.gov/measur/suite/docs)

The npm packages can be downloaded and install from [registry](https://www.npmjs.com/package/measur-tools-suite)

### Dependencies

#### C++

- make
- CMake (cmake-curses to use the ccmake gui)
- GCC 4.8.5 or later
  - Windows: MinGW or Cygwin or Visual Studio Build Tools or with other C++ compiler
- Doxygen (only for building documentation)

#### Web Assembly Compilation SDK

- [Install Emscripten (emsdk)](https://emscripten.org/docs/getting_started/downloads.html)
- Navigate to the `emsdk` directory.
- Run the following commands in order:
  ```bash
  ./emsdk install latest
  ```
  ```bash
  ./emsdk activate latest
  ```
  ```bash
  source ./emsdk_env.sh
  ``` 
  > This sets up the current terminal session to use the Emscripten tools. On Windows use `emsdk_env.bat`.

  > [!NOTE]
  > This needs to be done each time a new terminal session is started, or add the command to your shell profile script (e.g. .bashrc, .zshrc, etc.)

#### Node

- Node LTS [https://nodejs.org/en/](https://nodejs.org/en/) 

### Build Web Assembly Module

- Ensure Emscripten environment is activated (see above).
- Naviagate to the root directory of the MEASUR Tools Suite repository.
- Run the following commands in order:
  ```bash
  emcmake cmake -DBUILD_WASM=ON
  ```
  > If multiple compilers are present and default environment is not used, use `-G "<XXX> Makefiles"`. On Windows using MinGW: `emcmake cmake -D BUILD_WASM=ON .. -G "MinGW Makefiles"`
  ```bash
  emmake make
  ```
  > This will create the build artifacts `client.js` and `client.wasm` in the `/bin` directory. `client.js` is the glue code for initializing the WASM module. Place the two files in the same directory within your project and execute the `client.js` script.

### WASM Initialization Example

MEASUR Tools Suite is distributed as a modularized WebAssembly Module. Below is an illustration of the WASM initialization and usage process:

<!-- TODO: Replace with updated code snippet -->
![WASM Initialization](assets/wasm-initialization.png)

### WASM Unit Tests

- Ensure Emscripten environment is activated (see above).
- Navigate to the root directory of the MEASUR Tools Suite repository.
- Run the following commands in order:
  ```bash
  npm install
  ``` 
  > This will install the node dependencies.
  ```bash
  npm run test:browser
  ```
  > All mocha tests found under `tests/wasm-mocha/` will be executed. Migration of unit tests to the mocha framework is a WIP.

### C++ Unit Tests

- Ensure the CMake flag `BUILD_TESTING` is set (which is default).
- Navigate to the root directory of the MEASUR Tools Suite repository.
- Run the following commands in order:
  ```bash
  mkdir build-cpp
  ```
  ```bash
  cd build-cpp
  ```
  ```bash
  cmake ..
  ```  
  > If multiple compilers are present and default environment is not used, use `-G "XXX Makefiles"`. For windows using MinGW => `cmake .. -G "MinGW Makefiles"`
  ```bash
  cmake --build .
  ```
  ```bash
  cd bin
  ```
  > On Windows, the executable can be found under either the `Debug` or `Release` directories, depending on CMake configuration
  ```bash
  ./cpp_tests
  ```
  

### Packaging

- Enable the `BUILD_PACKAGE` flag in the CMakeCache, then `cmake ./` then `make package`
- Or use this directly for Windows: `cmake -D BUILD_TESTING:BOOL=OFF ./` and `cmake --build . --config Release --target PACKAGE`
- To make package on Linux or Mac, run `ccmake.` and set `BUILD_TESTING OFF`, `BUILD_PACKAGE ON`, then configure and generate. Then `make package`.

### Generate Documentation Locally

- Ensure Doxygen (v 1.14.0 or later) is installed.
- Navigate to the root directory of the MEASUR Tools Suite repository.
- Run:
  ```
  doxygen Doxyfile
  ```
  > The documentation will be generated in the `/docs/html` directory.

### Dockerizing 

To make it easy for developers local building and testing, it is dockerized. To run it in docker follow these steps.

- Navigate to the root directory of the MEASUR Tools Suite repository.
- To build the docker image run:
  ```bash
  docker compose up -d
  ```
- To stop the container run:
  ```bash
  docker compose down
  ```
- To run the unit tests (both WASM and C++):
  - WASM: In a browser, launch [http://localhost:3000/](http://localhost:3000/)
  - C++: Run the following commands in order:
    ```bash
    docker exec -it measur-tools-suite-build /bin/bash
    ```
    ```bash
    cd /usr/src/app/build-cpp/bin
    ```
    ```bash
    ./cpp_tests
    ```

> [!NOTE]
> Every time the container is started it will rebuild the application. To check status run: `docker compose logs --tail 5`.
