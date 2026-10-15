import { assert } from 'chai';
import createModule, {
    type MeasurToolsSuite,
    type MotorShaftPowerInput,
    type MotorShaftPowerResult,
    type MotorShaftPowerModule,
} from 'measur-tools-suite';

describe('MotorShaftPower stateless WASM API', function () {
    let moduleInstance: MeasurToolsSuite;

    before(async function () {
        moduleInstance = await createModule({ locateFile: (filename: string) => '/base/bin/' + filename });
    });

    function input(): MotorShaftPowerInput {
        return {
            motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
            lineFrequency: moduleInstance.LineFrequency.FREQ60,
            efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT,
            specifiedEfficiency: 0.93, ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
            loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
        };
    }

    const keys: (keyof MotorShaftPowerResult)[] = [
        'shaftPower', 'current', 'powerFactor', 'efficiency', 'power', 'estimatedFLA', 'loadFactor',
    ];

    it('exposes a typed function and plain value objects without runtime constructors', function () {
        const calculator: MotorShaftPowerModule = moduleInstance;
        const data: MotorShaftPowerInput = input();
        const result: MotorShaftPowerResult = calculator.calculateMotorShaftPower(data);
        assert.isFunction(calculator.calculateMotorShaftPower);
        assert.deepEqual(Object.keys(result).sort(), [...keys].sort());
        assert.strictEqual(Object.getPrototypeOf(result), Object.prototype);
        for (const name of ['MotorShaftPower', 'MotorShaftPowerInput', 'MotorShaftPowerResult']) {
            assert.notProperty(moduleInstance, name);
        }
        assert.notProperty(data, 'delete');
        assert.notProperty(result, 'delete');
    });

    it('preserves all seven captured legacy results, including boundary and degenerate inputs', function () {
        // Captured from unchanged native MotorShaftPower.cpp with freshly built dependencies at ba430c6.
        // Threshold measurements include the exact model double and its immediate neighbors.
        const goldens: { label: string; input: MotorShaftPowerInput; expected: number[] }[] = [
            { label: 'model-0-0-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [74.644607922920201, 89.863398811275957, 0.8030943031685952, 0.92808129184164112, 60, 116.56258946300228, 0.74644642141526696] },
            { label: 'model-0-0-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.339144770383754, 90, 0.83649539013900343, 0.92757142430217854, 57.374559634308994, 116.56258946300228, 0.71338955600985521] },
            { label: 'model-0-1-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [76.493234440657758, 91.630818602681927, 0.78760382968564824, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842] },
            { label: 'model-0-1-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.339014714031478, 90, 0.81599448272544661, 0.95087383841616413, 55.968418549943777, 113.83426223054738, 0.71338955600985521] },
            { label: 'model-0-2-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [77.017698935465646, 92.132939790830818, 0.78331141731228637, 0.95758672343095619, 60, 113.15677524898257, 0.77017696785812872] },
            { label: 'model-0-2-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.338860763353495, 90, 0.80981175160887242, 0.95813147926442011, 55.544349894775415, 113.15677524898257, 0.71338955600981968] },
            { label: 'model-0-3-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [74.699243269373611, 89.915432895686962, 0.80262955228640176, 0.92876059131587863, 60, 116.48727331091592, 0.74699220976001868] },
            { label: 'model-0-3-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.338914372092688, 90, 0.83524808873403389, 0.92895359477917383, 57.289008213840923, 116.48727331091592, 0.71338955600985521] },
            { label: 'model-1-0-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [74.644607922920201, 89.863398811275957, 0.8030943031685952, 0.92808129184164112, 60, 116.56258946300228, 0.74644642141526696] },
            { label: 'model-1-0-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.STANDARD, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.339144770383754, 90, 0.83649539013900343, 0.92757142430217854, 57.374559634308994, 116.56258946300228, 0.71338955600985521] },
            { label: 'model-1-1-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [76.493234440657758, 91.630818602681927, 0.78760382968564824, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842] },
            { label: 'model-1-1-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.339014714031478, 90, 0.81599448272544661, 0.95087383841616413, 55.968418549943777, 113.83426223054738, 0.71338955600985521] },
            { label: 'model-1-2-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [77.017698935465646, 92.132939790830818, 0.78331141731228637, 0.95758672343095619, 60, 113.15677524898257, 0.77017696785812872] },
            { label: 'model-1-2-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.PREMIUM, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.338860763353495, 90, 0.80981175160887242, 0.95813147926442011, 55.544349894775415, 113.15677524898257, 0.71338955600981968] },
            { label: 'model-1-3-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 480,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [74.699243269373611, 89.915432895686962, 0.80262955228640176, 0.92876059131587863, 60, 116.48727331091592, 0.74699220976001868] },
            { label: 'model-1-3-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1480,
                lineFrequency: moduleInstance.LineFrequency.FREQ50, efficiencyClass: moduleInstance.MotorEfficiencyClass.SPECIFIED, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 440,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [71.338914372092688, 90, 0.83524808873403389, 0.92895359477917383, 57.289008213840923, 116.48727331091592, 0.71338955600985521] },
            { label: 'equal-voltage-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [76.493234440657758, 93.791604894800983, 0.80291361828477603, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601842] },
            { label: 'zero-measurement-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 0, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 0,
            }, expected: [0, NaN, 0, 0, 0, 113.83426223054738, 0] },
            { label: 'negative-measurement-0', input: {
                motorRatedPower: 100, motorMeasuredPower: -1, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: -1,
            }, expected: [0.2428199790902581, 35.298254168503597, -0.035557262261625915, -0.18114370440133254, -1, 113.83426223054738, -0.0049276767252961927] },
            { label: 'overload-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 200, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 400,
            }, expected: [227.91049396334964, 295.34526466035413, 0.84992680163020951, 0.85010614248329419, 200, 113.83426223054738, 2.3564301470947129] },
            { label: 'zero-fla-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 0, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [NaN, NaN, NaN, NaN, 60, 113.83426223054738, NaN] },
            { label: 'changed-fla-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 150, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [76.493234440657758, 117.23950611852244, 0.64233089462770454, 0.95106588154551153, 60, 113.83426223054738, 0.76493238593601853] },
            { label: 'equal-voltage-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [72.904840344592401, 90, 0.79758057323954124, 0.95095431838560962, 57.192033145604931, 113.83426223054738, 0.7290484497988714] },
            { label: 'zero-measurement-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 0, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 0,
            }, expected: [89445.593949695671, 0, -Infinity, -359.21278021572539, -185.75734706989095, 113.83426223054738, -2.465090266600408] },
            { label: 'negative-measurement-1', input: {
                motorRatedPower: 100, motorMeasuredPower: -1, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: -1,
            }, expected: [94627.324837368695, -1, 239.82665319246789, -369.43623031433799, -191.08029623573532, 113.83426223054738, -2.5352484812219203] },
            { label: 'overload-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 200, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 400,
            }, expected: [284.45778510815813, 400, 0.84762803303895107, 0.78554829408642524, 270.1368067223367, 113.83426223054738, 3.1196159947455349] },
            { label: 'zero-fla-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 0, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [NaN, 90, NaN, -Infinity, NaN, 113.83426223054738, Infinity] },
            { label: 'changed-fla-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 150, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 90,
            }, expected: [55.03145177691691, 90, 0.60392163347360273, 0.94799979184840477, 43.305350252803535, 113.83426223054738, 0.55031461669948045] },
            { label: 'threshold-0-0--1', input: {
                motorRatedPower: 100, motorMeasuredPower: 20.238309287096126, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [25.000000000000007, 45.056212548352967, 0.56376886511769575, 0.92151966527614926, 20.238309287096126, 113.83426223054738, 0.25] },
            { label: 'threshold-0-0-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 20.238309287096129, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [25.000000000000014, 45.056212548352967, 0.56376886511769586, 0.92151966527614926, 20.238309287096129, 113.83426223054738, 0.25000000000000006] },
            { label: 'threshold-0-0-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 20.238309287096133, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [25.000000000000018, 45.056212548352967, 0.56376886511769597, 0.92151966527614926, 20.238309287096133, 113.83426223054738, 0.25000000000000011] },
            { label: 'threshold-0-1--1', input: {
                motorRatedPower: 100, motorMeasuredPower: 2.0293539039736657, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [0.99999999999999956, 35.29825416850359, 0.072158268985246049, 0.36760468370709593, 2.0293539039736657, 113.83426223054738, 0.0099999999999999985] },
            { label: 'threshold-0-1-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 2.0293539039736661, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [1, 35.298254168503597, 0.072158268985246063, 0.36760468370709598, 2.0293539039736661, 113.83426223054738, 0.01] },
            { label: 'threshold-0-1-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 2.0293539039736666, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.POWER, fieldCurrent: 90,
            }, expected: [1.0000000000000004, 35.298254168503597, 0.072158268985246077, 0.36760468370709609, 2.0293539039736666, 113.83426223054738, 0.010000000000000005] },
            { label: 'threshold-1-0--1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 45.05621254835296,
            }, expected: [25.000000000000004, 45.05621254835296, 0.56376886511769575, 0.92151966527614926, 20.238309287096122, 113.83426223054738, 0.24999999999999994] },
            { label: 'threshold-1-0-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 45.056212548352967,
            }, expected: [25.000000000000014, 45.056212548352967, 0.56376886511769586, 0.92151966527614926, 20.238309287096129, 113.83426223054738, 0.25000000000000006] },
            { label: 'threshold-1-0-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 45.056212548352974,
            }, expected: [25.000000000000018, 45.056212548352974, 0.56376886511769597, 0.92151966527614926, 20.238309287096136, 113.83426223054738, 0.25000000000000017] },
            { label: 'threshold-1-1--1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 35.136160175954004,
            }, expected: [-1.234506643718559e-13, 35.136160175954004, 0.045389176668293313, -7.2478166224933955e-14, 1.2706474296768595, 113.83426223054738, -4.9786563760534364e-16] },
            { label: 'threshold-1-1-0', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 35.136160175954011,
            }, expected: [0, 35.136160175954011, 0.045389176668294652, 0, 1.2706474296768973, 113.83426223054738, 0] },
            { label: 'threshold-1-1-1', input: {
                motorRatedPower: 100, motorMeasuredPower: 60, motorRpm: 1780,
                lineFrequency: moduleInstance.LineFrequency.FREQ60, efficiencyClass: moduleInstance.MotorEfficiencyClass.ENERGY_EFFICIENT, specifiedEfficiency: 0.93000000000000005,
                ratedVoltage: 460, fullLoadAmps: 120, fieldVoltage: 460,
                loadEstimationMethod: moduleInstance.LoadEstimationMethod.CURRENT, fieldCurrent: 35.136160175954018,
            }, expected: [2.7446726534186946e-14, 35.136160175954018, 0.045389176668295832, 1.611403566110342e-14, 1.2706474296769306, 113.83426223054738, 4.3835229460631506e-16] },
        ];
        for (const golden of goldens) {
            const actual = moduleInstance.calculateMotorShaftPower(golden.input);
            keys.forEach((key, i) => {
                const expected = golden.expected[i];
                const message = `${golden.label}: ${key}`;
                if (Number.isNaN(expected)) {
                    assert.isNaN(actual[key], message);
                } else if (!Number.isFinite(expected)) {
                    assert.strictEqual(actual[key], expected, message);
                } else {
                    assert.closeTo(actual[key], expected, Math.max(1e-9, Math.abs(expected) * 1e-11), message);
                }
            });
        }
    });

    it('does not mutate inputs or retain state and ignores the inactive measurement', function () {
        for (const mode of [moduleInstance.LoadEstimationMethod.POWER, moduleInstance.LoadEstimationMethod.CURRENT]) {
            const data: MotorShaftPowerInput = Object.freeze({ ...input(), loadEstimationMethod: mode });
            const before = { ...data };
            const first = moduleInstance.calculateMotorShaftPower(data);
            moduleInstance.calculateMotorShaftPower({ ...data, fieldVoltage: 480, fullLoadAmps: 150 });
            assert.deepEqual(moduleInstance.calculateMotorShaftPower(data), first);
            const ignored = mode === moduleInstance.LoadEstimationMethod.POWER
                ? { ...data, fieldCurrent: NaN } : { ...data, motorMeasuredPower: NaN };
            assert.deepEqual(moduleInstance.calculateMotorShaftPower(ignored), first);
            assert.deepEqual(data, before);
        }
    });
});
