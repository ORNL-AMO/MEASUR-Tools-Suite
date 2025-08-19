// MathJax configuration for Doxygen documentation

window.MathJax = {
    loader: {
        // Load custom and core MathJax extensions
        load: [
            '[custom]/siunitx.js', 
            '[tex]/html', 
            '[tex]/gensymb', 
            '[tex]/color', 
            '[tex]/cancel', 
            '[tex]/ams'
        ],
        // Path to custom extensions (relative to HTML root)
        paths: {
            custom: '/docs/dependencies'
        }
    },
    tex: {
        // Enable required packages
        packages: {
            '[+]': [
                'siunitx', 
                'html', 
                'gensymb', 
                'color', 
                'cancel', 
                'ams'
            ]
        },
        // siunitx configuration for unit rendering
        siunitx: {
            'free-standing-units': true,
            'overwrite-commands': true,
            'unit-font-command': '\\mathrm',      // Use \mathrm for unit text
            'unit-color': 'LightBlue',            // Color for units
            'bracket-unit-denominator': false,    // Do not use brackets for unit denominators
            'inter-unit-product': '\\!\\cdot\\!', // Use a centered dot for multiplication
            'per-mode': 'power',                  // Use negative exponents for division
            'sticky-per': true,                   // Apply 'per' to all subsequent units
            'qualifier-mode': 'combine'
        },
        // Enable automatic equation numbering
        tags: 'ams'
    },
    options: {
        enableEnrichment: true,
        sre: {
            domain: 'clearspeak'
        }
    }
};