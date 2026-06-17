# MEASUR Tools Suite

<img align="left" width="80" height="80" src="docs/assets/app-icon.png">

The MEASUR Tools Suite is a collection of industrial efficiency calculations written in C++ with WebAssembly bindings for browser and Node.js environments. The suite provides computational engines for the [MEASUR](https://github.com/ORNL-AMO/AMO-Tools-Desktop) (Manufacturing Energy Assessment Suite for Utility Reduction) application ecosystem.

## Features

- **Native C++ Library**: High-performance static library for desktop applications
- **WebAssembly Module**: Cross-platform execution in browsers and Node.js
- **Industrial Calculations**: Comprehensive tools for energy efficiency assessments including:
  - Compressed air systems
  - Motor-driven equipment (fans, pumps)
  - Process heating and cooling
  - Steam system modeling
  - Waste water treatment

Check out the [Master List of MEASUR Calculators](https://github.com/ORNL-AMO/AMO-Tools-Desktop/blob/develop/docs/calculator_list.md)

## Quick Start

### Using npm Package

```bash
npm install measur-tools-suite
```

**JavaScript**

```js
// Initialize module
const moduleFactory = (await import('/path/to/client.js')).default;
const toolsSuiteModule = await moduleFactory({
	locateFile: (filename) => '/path/to/client.wasm'
});

// Plain function call — returns a number directly
const totalHeatLoss = toolsSuiteModule.wallTotalHeatLoss(
	500, 80, 225, 10, 0.9, 1.394, 1
);
console.log('Wall total heat loss:', totalHeatLoss);

// Class-based API — always call delete() to free WASM memory
const doc = new toolsSuiteModule.DryerOperatingCost(1752, 50, 100, 24, 7, 52, 0.08, 0.2, 0.25);
const res = doc.calculate(toolsSuiteModule.DryerType.Heatless);
console.log('Water removed:', res.waterRemoved);
res.delete();
doc.delete();
```

**TypeScript** — named `import type` provides IDE autocompletion with zero runtime cost; enum values and constructors still come from the live module instance.

```ts
import type { DryerOperatingCostModule } from 'measur-tools-suite';

const moduleFactory = (await import('/path/to/client.js')).default;
const toolsSuiteModule = await moduleFactory({
	locateFile: (filename) => '/path/to/client.wasm'
});

// Narrow to the typed sub-module for full IDE assistance
const dryerModule = toolsSuiteModule as unknown as DryerOperatingCostModule;
const doc = new dryerModule.DryerOperatingCost(1752, 50, 100, 24, 7, 52, 0.08, 0.2, 0.25);
const res = doc.calculate(dryerModule.DryerType.Heatless);
console.log('Water removed:', res.waterRemoved);
res.delete();
doc.delete();
```

### Building from Source

```bash
# Native C++ build
cmake -S . -B build-cpp
cmake --build build-cpp

# WebAssembly build (requires Emscripten)
emcmake cmake -DBUILD_WASM=ON
emmake make

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
- Formatting standards ([contributing/formatting.md](contributing/formatting.md))
- Documentation standards ([contributing/documentation.md](contributing/documentation.md))
- Commit message conventions ([contributing/conventional-commits.md](contributing/conventional-commits.md))

## License

Copyright 2018, UT-Battelle, LLC. All rights reserved.

This project is licensed under an Open Source License (Permissive) by UT-Battelle, LLC. The license grants free, perpetual, worldwide, non-exclusive, royalty-free, irrevocable rights to use, copy, modify, merge, publish, distribute, and/or sublicense the software.

See [LICENSE.txt](LICENSE.txt) for complete terms and conditions.
