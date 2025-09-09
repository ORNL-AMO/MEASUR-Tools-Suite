import { assert } from 'chai';

describe('Calculate Pump valve power loss and Annual Energy usage', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('Calculate Head Friction Electrical Losses', function () {
        function rnd(value) {
            return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
        }

        let validate = function(results, expected) {
            assert.equal(rnd(results.pressure_drop), rnd(expected[0]), "pressure_drop");
            assert.equal(rnd(results.head_loss), rnd(expected[1]), "head_loss");
            assert.equal(rnd(results.power_loss_frictional), rnd(expected[2]), "power_loss_frictional");
            assert.equal(rnd(results.power_loss_electrical), rnd(expected[3]), "power_loss_electrical");
            assert.equal(rnd(results.annual_energy_loss), rnd(expected[4]), "annual_energy_loss");
        };

        let pumpValvePowerLoss = new moduleInstance.PumpValvePowerLoss();

        /* PumpValvePowerLoss calculate input parameters
            operating_hours: number
            pump_efficiency: number
            motor_efficiency: number
            specific_gravity: number
            flow_rate: number
            upstream_pressure: number
            upstream_gauge_elevation: number
            downstream_pressure: number
            downstream_gauge_elevation: number
        */
        
        validate(pumpValvePowerLoss.calculate(8760, 0.85, 0.95, 1, 5000, 50, 5, 45, 2),
            [6.300249778,  14.536245, 18.3763150298, 16.97, 148656.58]);

        validate(pumpValvePowerLoss.calculate(6140, 0.87, 0.96, 1, 4000, 60, 5, 45, 2),
            [16.300249778,  37.608735, 38.0351301032, 33.9592870186, 208510.0222943327]);

        validate(pumpValvePowerLoss.calculate(7000, 0.85, 0.95, 1, 5000, 50, 5, 45, 2),
            [6.300249778,  14.536245, 18.3763150298, 16.97, 118789.5069030884]);

        validate(pumpValvePowerLoss.calculate(8760, 0.89, 0.95, 1, 5000, 50, 5, 45, 2),
            [6.300249778,  14.536245, 18.3763150298, 16.2072360943, 141975.3881862594]);

        validate(pumpValvePowerLoss.calculate(8760, 0.85, 0.97, 1, 5000, 50, 5, 45, 2),
            [6.300249778,  14.536245, 18.3763150298, 16.62, 145591.4987404273]);

        validate(pumpValvePowerLoss.calculate(8760, 0.85, 0.95, 2, 5000, 50, 5, 45, 2),
            [7.600499556, 17.536245, 22.1688312601, 20.4721950101, 179336.4282884425]);

        validate(pumpValvePowerLoss.calculate(8760, 0.85, 0.95, 1, 5000, 60, 5, 40, 2),
            [21.300249778, 49.14498, 62.1277114286, 57.3729218728, 502586.7956057265]);

        validate(pumpValvePowerLoss.calculate(8760, 0.85, 0.95, 1, 5000, 50, 15, 45, 2),
            [10.6344157046, 24.536245, 31.0180357974, 28.6441477326, 250922.7341377905]);

        pumpValvePowerLoss.delete();
    });
});