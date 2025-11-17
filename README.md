# MEASUR Tools Suite

<img align="left" width="80" height="80" src="docs/assets/app-icon.png">

The MEASUR Tools Suite is a collection of industrial efficiency calculations written in C++ with WebAssembly bindings for browser and Node.js environments. The suite provides computational engines for the MEASUR (Manufacturing Energy Assessment Tool for Uniform Reporting) application ecosystem.

## Features

- **Native C++ Library**: High-performance static library for desktop applications
- **WebAssembly Module**: Cross-platform execution in browsers and Node.js
- **Industrial Calculations**: Comprehensive tools for energy efficiency assessments including:
  - Compressed air systems
  - Motor-driven equipment (fans, pumps)
  - Process heating and cooling
  - Steam system modeling
  - Waste water treatment

## Quick Start

### Using npm Package

```bash
npm install measur-tools-suite
```

```javascript
const measurTools = require('measur-tools-suite');
// Use calculation functions
```

### Building from Source

```bash
# Native C++ build
cmake -S . -B build-cpp
cmake --build build-cpp

# WebAssembly build (requires Emscripten)
emcmake cmake -S . -B build-wasm -DBUILD_WASM=ON
emmake make -C build-wasm

# Packaging
cmake -S . -B build-pkg -DBUILD_PACKAGE=ON -DBUILD_TESTING=OFF
cmake --build build-pkg --target package
```

See [BUILD.md](BUILD.md) for detailed build instructions, testing, and Docker workflows.

## Documentation

- **API Documentation**: [https://industrialresources.ornl.gov/measur/suite/docs](https://industrialresources.ornl.gov/measur/suite/docs)
- **MEASUR Ecosystem**: [https://industrialresources.ornl.gov/measur](https://industrialresources.ornl.gov/measur)
- **npm Registry**: [https://www.npmjs.com/package/measur-tools-suite](https://www.npmjs.com/package/measur-tools-suite)

## Project Documentation

- [BUILD.md](BUILD.md) - Complete build, test, and deployment guide
  - Native C++ builds (Linux, macOS, Windows)
  - WebAssembly compilation and usage
  - Docker containerized builds
  - Testing and packaging
- [ARCHITECTURE.md](ARCHITECTURE.md) - System architecture, design decisions, and module organization
- [CONTRIBUTING.md](CONTRIBUTING.md) - Contribution guidelines, code style, and documentation standards

## How to Contribute

Contributions are welcome! Please refer to [CONTRIBUTING.md](CONTRIBUTING.md) for:
- Code style guidelines ([contributing/style-guide.md](contributing/style-guide.md))
- Documentation standards ([contributing/documentation.md](contributing/documentation.md))
- Commit message conventions ([contributing/conventional-commits.md](contributing/conventional-commits.md))

## License

Copyright 2018, UT-Battelle, LLC. All rights reserved.

This project is licensed under an Open Source License (Permissive) by UT-Battelle, LLC. The license grants free, perpetual, worldwide, non-exclusive, royalty-free, irrevocable rights to use, copy, modify, merge, publish, distribute, and/or sublicense the software.

See [LICENSE.txt](LICENSE.txt) for complete terms and conditions.
