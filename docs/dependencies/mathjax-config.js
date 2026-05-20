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
            custom: './'
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
    // Define custom units for use with siunitx
    startup: {
        ready() {
            MathJax.startup.defaultReady();
            MathJax.tex2mml(String.raw`
                \DeclareSIUnit{\poundFuel}{lb_{fuel}}
                \DeclareSIUnit{\abs}{abs}
                \DeclareSIUnit{\dollar}{$}
                \DeclareSIUnit{\britishThermalUnit}{Btu}
                \DeclareSIUnit{\btu}{Btu}
                \DeclareSIUnit{\MMBtu}{MMBtu}

                \DeclareSIUnit{\degreeFahrenheit}{\degree F}
                \DeclareSIUnit{\degreeF}{\degree F}
                \DeclareSIUnit{\degreeKelvin}{\degree K}
                \DeclareSIUnit{\degreeK}{\degree K}
                \DeclareSIUnit{\degreeRankine}{\degree R}
                \DeclareSIUnit{\degreeR}{\degree R}

                \DeclareSIUnit{\inch}{in}
                \DeclareSIUnit{\in}{in}
                \DeclareSIUnit{\foot}{ft}
                \DeclareSIUnit{\ft}{ft}
                \DeclareSIUnit{\yard}{yd}
                \DeclareSIUnit{\yd}{yd}
                \DeclareSIUnit{\mile}{mi}
                \DeclareSIUnit{\mi}{mi}

                \DeclareSIUnit{\gallon}{gal}
                \DeclareSIUnit{\gal}{gal}
                \DeclareSIUnit{\gallonPerMinute}{gpm}
                \DeclareSIUnit{\gpm}{gpm}

                \DeclareSIUnit{\pound}{lb}
                \DeclareSIUnit{\lb}{lb}

                \DeclareSIUnit{\revolutionsPerMinute}{rpm}
                \DeclareSIUnit{\rpm}{rpm}

                \DeclareSIUnit{\percent}{\%}
                \DeclareSIUnit{\unitless}{-}

                \DeclareSIUnit{\standardCubicFeet}{scf}
                \DeclareSIUnit{\scf}{scf}
                \DeclareSIUnit{\standardCubicFeetPerMinute}{scfm}
                \DeclareSIUnit{\scfm}{scfm}
                \DeclareSIUnit{\cubicFoot}{ft^3}
                \DeclareSIUnit{\normalCubicMeter}{Nm^3}
                \DeclareSIUnit{\NmCubed}{Nm^3}
                \DeclareSIUnit{\cubicMeter}{m^3}
                \DeclareSIUnit{\squareMeter}{m^2}
                \DeclareSIUnit{\inchWaterColumn}{in\,WC}
                \DeclareSIUnit{\kilowatt}{kW}
                \DeclareSIUnit{\atm}{atm}
                \DeclareSIUnit{\lbmol}{lbmol}
                \DeclareSIUnit{\year}{yr}
                \DeclareSIUnit{\ton}{ton}
                \DeclareSIUnit{\squareInch}{in^2}
                \DeclareSIUnit{\squareFoot}{ft^2}
                \DeclareSIUnit{\inchMercury}{inHg}
                \DeclareSIUnit{\psi}{psi}
            `);
        }
    },
    options: {
        enableEnrichment: true,
        sre: {
            domain: 'clearspeak'
        }
    }
};