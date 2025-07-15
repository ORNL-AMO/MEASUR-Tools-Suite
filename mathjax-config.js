window.MathJax = {
    loader: {
        load: ['[custom]/siunitx.js', '[tex]/html', '[tex]/gensymb', '[tex]/color', '[tex]/cancel', '[tex]/ams'],
        paths: {
            custom: '../../../siunitx-pcc-imperial-support'
        }
    },
    tex: {
        packages: {
            '[+]': ['siunitx', 'html', 'gensymb', 'color', 'cancel', 'ams'],
        },
        siunitx: {
            'per-mode': 'symbol',
            'qualifier-mode': 'combine',
            'inter-unit-product': '', //'\\cdot\\!',
            'bracket-unit-denominator': false,
            'unit-font-command': '\\mathrm',
            'unit-color': 'LightBlue',
            'free-standing-units': true,
            'overwrite-commands': true,
        },
        tags: 'ams', // Enables automatic equation numbering
    },
    options: {
        enableEnrichment: true,
        sre: {
            domain: 'clearspeak'
        }
    }
};