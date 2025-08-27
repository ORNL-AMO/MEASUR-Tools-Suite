module.exports = function (config) {
    config.set({
        frameworks: ['mocha'],
        files: [
            // All browser-based WASM Mocha tests
            { pattern: 'bin/client.js', included: false, served: true, watched: false },
            { pattern: 'bin/client.wasm', included: false, served: true, watched: false },
            'tests/wasm-mocha/**/*.test.js',
            // Add any additional files or patterns as needed
        ],
        preprocessors: {
            'tests/wasm-mocha/**/*.test.js': ['webpack']
        },
        webpack: {
            mode: 'development',
            experiments: { asyncWebAssembly: true },
            resolve: {
                extensions: ['.js', '.wasm']
            },
            module: {
                rules: [
                    {
                        test: /\.wasm$/,
                        type: 'webassembly/async'
                    }
                ]
            }
        },
        browsers: ['ChromeHeadless'],
        singleRun: true,
        reporters: ['progress']
    });
};
