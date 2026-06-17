const path = require('path');

module.exports = function (config) {
    config.set({
        port: 3000,
        customLaunchers: {
            ChromeHeadlessNoSandbox: {
                base: 'ChromeHeadless',
                flags: ['--no-sandbox']
            }
        },
        frameworks: ['mocha'],
        files: [
            // All browser-based WASM Mocha tests
            { pattern: 'bin/client.js', included: false, served: true, watched: false },
            { pattern: 'bin/client.wasm', included: false, served: true, watched: false },
            'tests/wasm-mocha/**/*.test.js',
            'tests/wasm-mocha/**/*.test.ts',
            // Add any additional files or patterns as needed
        ],
        preprocessors: {
            'tests/wasm-mocha/**/*.test.js': ['webpack'],
            'tests/wasm-mocha/**/*.test.ts': ['webpack']
        },
        webpack: {
            mode: 'development',
            experiments: { asyncWebAssembly: true },
            resolve: {
                extensions: ['.ts', '.js', '.wasm'],
                alias: {
                    'measur-tools-suite': path.resolve(__dirname, 'bin/client.js')
                }
            },
            module: {
                rules: [
                    {
                        test: /\.wasm$/,
                        type: 'webassembly/async'
                    },
                    {
                        test: /\.ts$/,
                        use: 'ts-loader',
                        exclude: /node_modules/
                    }
                ]
            }
        },
        browsers: ['ChromeHeadless'],
        singleRun: true,
        reporters: ['progress', 'mocha'],
        client: {
            captureConsole: true
        },
        browserConsoleLogOptions: {
            level: "log",
            format: "%b %T: %m",
            terminal: true
        },
    });
};
