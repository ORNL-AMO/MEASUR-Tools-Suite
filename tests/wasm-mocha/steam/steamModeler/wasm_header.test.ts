import { assert } from 'chai';
import createModule, {
    type Header,
    type Inlet,
    type InletVector,
    type MeasurToolsSuite,
    type SteamPropertiesOutput,
} from 'measur-tools-suite';

describe('Steam Header', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('constructs and returns registered inlet vectors', function () {
        const inletVector: InletVector = new moduleInstance.InletVector();
        let header: Header | undefined;
        let headerProperties: SteamPropertiesOutput | undefined;
        let returnedInlets: InletVector | undefined;

        const inletInputs: Array<[number, number, number, number]> = [
            [1.9332, moduleInstance.ThermodynamicQuantity.TEMPERATURE, 579.8, 0.686],
            [2.8682, moduleInstance.ThermodynamicQuantity.TEMPERATURE, 308.5, 0.5019],
            [1.0348, moduleInstance.ThermodynamicQuantity.TEMPERATURE, 458, 0.5633],
            [1.8438, moduleInstance.ThermodynamicQuantity.TEMPERATURE, 475.8, 0.3082],
        ];

        try {
            for (const [pressure, quantityType, quantityValue, massFlow] of inletInputs) {
                const inlet: Inlet = new moduleInstance.Inlet(pressure, quantityType, quantityValue, massFlow);
                try {
                    inletVector.push_back(inlet);
                } finally {
                    inlet.delete();
                }
            }

            header = new moduleInstance.Header(0.173, inletVector);
            headerProperties = header.getHeaderProperties();
            returnedInlets = header.getInlets();

            assert.approximately(headerProperties.pressure, 0.173, 0.001);
            assert.approximately(header.getInletMassFlow(), 2.0594, 0.001);
            assert.equal(returnedInlets.size(), 4);

            const firstInlet: Inlet = returnedInlets.get(0);
            try {
                assert.approximately(firstInlet.getMassFlow(), 0.686, 0.001);
            } finally {
                firstInlet.delete();
            }
        } finally {
            returnedInlets?.delete();
            headerProperties?.delete();
            header?.delete();
            inletVector.delete();
        }
    });
});
