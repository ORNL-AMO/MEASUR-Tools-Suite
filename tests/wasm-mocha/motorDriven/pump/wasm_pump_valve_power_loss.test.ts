import { assert } from 'chai';
import createModule, { type MeasurToolsSuite, type PumpValvePowerLossOutput } from 'measur-tools-suite';

type PumpValvePowerLossInput = [
    operatingHours: number,
    pumpEfficiency: number,
    motorEfficiency: number,
    specificGravity: number,
    flowRate: number,
    upstreamPressure: number,
    upstreamGaugeElevation: number,
    downstreamPressure: number,
    downstreamGaugeElevation: number
];

type PumpValvePowerLossExpected = [
    pressureDrop: number,
    headLoss: number,
    powerLossFrictional: number,
    powerLossElectrical: number,
    annualEnergyLoss: number
];

describe('Calculate Pump valve power loss and Annual Energy usage', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('Calculate Head Friction Electrical Losses', function () {
        function roundToHundredths(value: number): number {
            return Math.round(value * 100) / 100;
        }

        function validate(results: PumpValvePowerLossOutput, expected: PumpValvePowerLossExpected): void {
            assert.equal(roundToHundredths(results.pressure_drop), roundToHundredths(expected[0]), "pressure_drop");
            assert.equal(roundToHundredths(results.head_loss), roundToHundredths(expected[1]), "head_loss");
            assert.equal(
                roundToHundredths(results.power_loss_frictional),
                roundToHundredths(expected[2]),
                "power_loss_frictional"
            );
            assert.equal(
                roundToHundredths(results.power_loss_electrical),
                roundToHundredths(expected[3]),
                "power_loss_electrical"
            );
            assert.equal(
                roundToHundredths(results.annual_energy_loss),
                roundToHundredths(expected[4]),
                "annual_energy_loss"
            );
        }

        const testCases: Array<{ input: PumpValvePowerLossInput; expected: PumpValvePowerLossExpected }> = [
            {
                input: [8760, 0.85, 0.95, 1, 5000, 50, 5, 45, 2],
                expected: [6.300249778, 14.536245, 18.3763150298, 16.97, 148656.58]
            },
            {
                input: [6140, 0.87, 0.96, 1, 4000, 60, 5, 45, 2],
                expected: [16.300249778, 37.608735, 38.0351301032, 33.9592870186, 208510.0222943327]
            },
            {
                input: [7000, 0.85, 0.95, 1, 5000, 50, 5, 45, 2],
                expected: [6.300249778, 14.536245, 18.3763150298, 16.97, 118789.5069030884]
            },
            {
                input: [8760, 0.89, 0.95, 1, 5000, 50, 5, 45, 2],
                expected: [6.300249778, 14.536245, 18.3763150298, 16.2072360943, 141975.3881862594]
            },
            {
                input: [8760, 0.85, 0.97, 1, 5000, 50, 5, 45, 2],
                expected: [6.300249778, 14.536245, 18.3763150298, 16.62, 145591.4987404273]
            },
            {
                input: [8760, 0.85, 0.95, 2, 5000, 50, 5, 45, 2],
                expected: [7.600499556, 17.536245, 22.1688312601, 20.4721950101, 179336.4282884425]
            },
            {
                input: [8760, 0.85, 0.95, 1, 5000, 60, 5, 40, 2],
                expected: [21.300249778, 49.14498, 62.1277114286, 57.3729218728, 502586.7956057265]
            },
            {
                input: [8760, 0.85, 0.95, 1, 5000, 50, 15, 45, 2],
                expected: [10.6344157046, 24.536245, 31.0180357974, 28.6441477326, 250922.7341377905]
            }
        ];
        const pumpValvePowerLoss = new moduleInstance.PumpValvePowerLoss();

        try {
            for (const { input, expected } of testCases) {
                const results: PumpValvePowerLossOutput = pumpValvePowerLoss.calculate(...input);

                try {
                    validate(results, expected);
                } finally {
                    results.delete();
                }
            }
        } finally {
            pumpValvePowerLoss.delete();
        }
    });
});
