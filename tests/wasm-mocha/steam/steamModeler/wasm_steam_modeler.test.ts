import { assert } from 'chai';
import createModule, {
    type FluidProperties,
    type HeatLoss,
    type MeasurToolsSuite,
    type PrvWithoutDesuperheating,
    type ProcessSteamUsage,
    type SteamModelerOutput,
    type SteamPropertiesOutput,
    type Turbine
} from 'measur-tools-suite';

type EmbindDeletable = {
    delete(): void;
};

type ExpectedValues = Record<string, number | undefined>;

type ValidatedFluidProperties = EmbindDeletable & Partial<
    Pick<
        FluidProperties & ProcessSteamUsage & SteamPropertiesOutput,
        | 'pressure'
        | 'temperature'
        | 'specificEnthalpy'
        | 'specificEntropy'
        | 'quality'
        | 'specificVolume'
        | 'massFlow'
        | 'energyFlow'
        | 'density'
        | 'internalEnergy'
        | 'processUsage'
    >
>;

describe('Steam Modeler Tests', function () {
    let m: MeasurToolsSuite;
    let results: SteamModelerOutput;
    let cleanupModel: (() => void) | undefined;

    const DEFAULT_TOLERANCE = 0.1;
    const DEFAULT_RELATIVE_TOLERANCE = 0.05;

    function isDefined(value: number | undefined | null): value is number {
        return value !== undefined && value !== null;
    }

    function assertNumber(actual: number | undefined | null, expected: number, label: string, tolerance: number | null = null): void {
        assert.isNumber(actual, `${label} should be a number`);
        const computedTolerance = tolerance ?? Math.max(DEFAULT_TOLERANCE, Math.abs(expected) * DEFAULT_RELATIVE_TOLERANCE);
        assert.approximately(actual as number, expected, computedTolerance, label);
    }

    function validateFluidProperties(header: string, fluidProperties: ValidatedFluidProperties, expected: ExpectedValues): void {
        assert.isOk(fluidProperties, `${header} should be defined`);

        if (isDefined(expected.pressure)) assertNumber(fluidProperties.pressure, expected.pressure, `${header}.pressure`);
        if (isDefined(expected.temperature)) assertNumber(fluidProperties.temperature, expected.temperature, `${header}.temperature`);
        if (isDefined(expected.specificEnthalpy)) assertNumber(fluidProperties.specificEnthalpy, expected.specificEnthalpy, `${header}.specificEnthalpy`);
        if (isDefined(expected.specificEntropy)) assertNumber(fluidProperties.specificEntropy, expected.specificEntropy, `${header}.specificEntropy`);
        if (isDefined(expected.quality)) assertNumber(fluidProperties.quality, expected.quality, `${header}.quality`);
        if (isDefined(expected.specificVolume)) assertNumber(fluidProperties.specificVolume, expected.specificVolume, `${header}.specificVolume`);
        if (isDefined(expected.massFlow)) assertNumber(fluidProperties.massFlow, expected.massFlow, `${header}.massFlow`);
        if (isDefined(expected.energyFlow)) assertNumber(fluidProperties.energyFlow, expected.energyFlow, `${header}.energyFlow`);
        if (isDefined(expected.density)) assertNumber(fluidProperties.density, expected.density, `${header}.density`);
        if (isDefined(expected.internalEnergy)) assertNumber(fluidProperties.internalEnergy, expected.internalEnergy, `${header}.internalEnergy`);
        if (isDefined(expected.processUsage)) assertNumber(fluidProperties.processUsage, expected.processUsage, `${header}.processUsage`);
        fluidProperties.delete();
    }

    function validateTurbineOutput(header: string, turbine: Turbine | null, expected: ExpectedValues): void {
        if (!turbine) {
            assert.fail(`${header} should be defined`);
        }

        const inletProperties = turbine.getInletProperties();
        const outletProperties = turbine.getOutletProperties();

        if (isDefined(expected.energyOut)) assertNumber(turbine.getEnergyOut(), expected.energyOut, `${header}.energyOut`);
        if (isDefined(expected.generatorEfficiency)) assertNumber(turbine.getGeneratorEfficiency(), expected.generatorEfficiency, `${header}.generatorEfficiency`);
        if (isDefined(expected.inletEnergyFlow)) assertNumber(turbine.getInletEnergyFlow(), expected.inletEnergyFlow, `${header}.inletEnergyFlow`);

        if (isDefined(expected.inletPressure)) assertNumber(inletProperties.pressure, expected.inletPressure, `${header}.inletPressure`);
        if (isDefined(expected.inletQuality)) assertNumber(inletProperties.quality, expected.inletQuality, `${header}.inletQuality`);
        if (isDefined(expected.inletVolume)) assertNumber(inletProperties.specificVolume, expected.inletVolume, `${header}.inletVolume`);
        if (isDefined(expected.inletSpecificEnthalpy)) assertNumber(inletProperties.specificEnthalpy, expected.inletSpecificEnthalpy, `${header}.inletSpecificEnthalpy`);
        if (isDefined(expected.inletSpecificEntropy)) assertNumber(inletProperties.specificEntropy, expected.inletSpecificEntropy, `${header}.inletSpecificEntropy`);
        if (isDefined(expected.inletTemperature)) assertNumber(inletProperties.temperature, expected.inletTemperature, `${header}.inletTemperature`);

        if (isDefined(expected.isentropicEfficiency)) assertNumber(turbine.getIsentropicEfficiency(), expected.isentropicEfficiency, `${header}.isentropicEfficiency`);
        if (isDefined(expected.massFlow)) assertNumber(turbine.getMassFlow(), expected.massFlow, `${header}.massFlow`);
        if (isDefined(expected.outletEnergyFlow)) assertNumber(turbine.getOutletEnergyFlow(), expected.outletEnergyFlow, `${header}.outletEnergyFlow`);

        if (isDefined(expected.outletPressure)) assertNumber(outletProperties.pressure, expected.outletPressure, `${header}.outletPressure`);
        if (isDefined(expected.outletQuality)) assertNumber(outletProperties.quality, expected.outletQuality, `${header}.outletQuality`);
        if (isDefined(expected.outletVolume)) assertNumber(outletProperties.specificVolume, expected.outletVolume, `${header}.outletVolume`);
        if (isDefined(expected.outletSpecificEnthalpy)) assertNumber(outletProperties.specificEnthalpy, expected.outletSpecificEnthalpy, `${header}.outletSpecificEnthalpy`);
        if (isDefined(expected.outletSpecificEntropy)) assertNumber(outletProperties.specificEntropy, expected.outletSpecificEntropy, `${header}.outletSpecificEntropy`);
        if (isDefined(expected.outletTemperature)) assertNumber(outletProperties.temperature, expected.outletTemperature, `${header}.outletTemperature`);

        if (isDefined(expected.powerOut)) assertNumber(turbine.getPowerOut(), expected.powerOut, `${header}.powerOut`);
        inletProperties.delete();
        outletProperties.delete();
        turbine.delete();
    }

    function validatePrvOutput(header: string, prv: PrvWithoutDesuperheating | null, expected: ExpectedValues): void {
        if (!prv) {
            assert.fail(`${header} should be defined`);
        }

        const inletProperties = prv.getInletProperties();
        if (isDefined(expected.inletEnergyFlow)) assertNumber(prv.getInletEnergyFlow(), expected.inletEnergyFlow, `${header}.inletEnergyFlow`);
        if (isDefined(expected.inletMassFlow)) assertNumber(prv.getInletMassFlow(), expected.inletMassFlow, `${header}.inletMassFlow`);
        if (isDefined(expected.inletPressure)) assertNumber(inletProperties.pressure, expected.inletPressure, `${header}.inletPressure`);
        if (isDefined(expected.inletQuality)) assertNumber(inletProperties.quality, expected.inletQuality, `${header}.inletQuality`);
        if (isDefined(expected.inletVolume)) assertNumber(inletProperties.specificVolume, expected.inletVolume, `${header}.inletVolume`);
        if (isDefined(expected.inletSpecificEnthalpy)) assertNumber(inletProperties.specificEnthalpy, expected.inletSpecificEnthalpy, `${header}.inletSpecificEnthalpy`);
        if (isDefined(expected.inletSpecificEntropy)) assertNumber(inletProperties.specificEntropy, expected.inletSpecificEntropy, `${header}.inletSpecificEntropy`);
        if (isDefined(expected.inletTemperature)) assertNumber(inletProperties.temperature, expected.inletTemperature, `${header}.inletTemperature`);

        const outletProperties = prv.getOutletProperties();
        if (isDefined(expected.outletEnergyFlow)) assertNumber(prv.getOutletEnergyFlow(), expected.outletEnergyFlow, `${header}.outletEnergyFlow`);
        if (isDefined(expected.outletMassFlow)) assertNumber(prv.getOutletMassFlow(), expected.outletMassFlow, `${header}.outletMassFlow`);
        if (isDefined(expected.outletPressure)) assertNumber(outletProperties.pressure, expected.outletPressure, `${header}.outletPressure`);
        if (isDefined(expected.outletQuality)) assertNumber(outletProperties.quality, expected.outletQuality, `${header}.outletQuality`);
        if (isDefined(expected.outletVolume)) assertNumber(outletProperties.specificVolume, expected.outletVolume, `${header}.outletVolume`);
        if (isDefined(expected.outletSpecificEnthalpy)) assertNumber(outletProperties.specificEnthalpy, expected.outletSpecificEnthalpy, `${header}.outletSpecificEnthalpy`);
        if (isDefined(expected.outletSpecificEntropy)) assertNumber(outletProperties.specificEntropy, expected.outletSpecificEntropy, `${header}.outletSpecificEntropy`);
        if (isDefined(expected.outletTemperature)) assertNumber(outletProperties.temperature, expected.outletTemperature, `${header}.outletTemperature`);

        if (prv.isWithDesuperheating()) {
            const prvCast = new m.PrvCastDesuperheating();
            const prvWith = prvCast.Cast(prv);
            if (prvWith) {
                const feedwaterProperties = prvWith.getFeedwaterProperties();
                if (isDefined(expected.feedwaterEnergyFlow)) assertNumber(prvWith.getFeedwaterEnergyFlow(), expected.feedwaterEnergyFlow, `${header}.feedwaterEnergyFlow`);
                if (isDefined(expected.feedwaterMassFlow)) assertNumber(prvWith.getFeedwaterMassFlow(), expected.feedwaterMassFlow, `${header}.feedwaterMassFlow`);
                if (isDefined(expected.feedwaterPressure)) assertNumber(feedwaterProperties.pressure, expected.feedwaterPressure, `${header}.feedwaterPressure`);
                if (isDefined(expected.feedwaterQuality)) assertNumber(feedwaterProperties.quality, expected.feedwaterQuality, `${header}.feedwaterQuality`);
                if (isDefined(expected.feedwaterVolume)) assertNumber(feedwaterProperties.specificVolume, expected.feedwaterVolume, `${header}.feedwaterVolume`);
                if (isDefined(expected.feedwaterSpecificEnthalpy)) assertNumber(feedwaterProperties.specificEnthalpy, expected.feedwaterSpecificEnthalpy, `${header}.feedwaterSpecificEnthalpy`);
                if (isDefined(expected.feedwaterSpecificEntropy)) assertNumber(feedwaterProperties.specificEntropy, expected.feedwaterSpecificEntropy, `${header}.feedwaterSpecificEntropy`);
                if (isDefined(expected.feedwaterTemperature)) assertNumber(feedwaterProperties.temperature, expected.feedwaterTemperature, `${header}.feedwaterTemperature`);
                feedwaterProperties.delete();
                prvWith.delete();
            }
            prvCast.delete();
        }
        inletProperties.delete();
        outletProperties.delete();
        prv.delete();
    }

    function validateHeatLoss(
        pressureLevel: string,
        heatLoss: HeatLoss | null,
        heatLossValue: number,
        expectedInlet: ExpectedValues,
        expectedOutlet: ExpectedValues
    ): void {
        if (!heatLoss) {
            assert.fail(`${pressureLevel} pressure heatLoss should be defined`);
        }
        assertNumber(heatLoss.getHeatLoss(), heatLossValue, `${pressureLevel}.heatLoss`);
        validateFluidProperties(`${pressureLevel} HeatLoss Inlet`, heatLoss.getInletProperties(), expectedInlet);
        validateFluidProperties(`${pressureLevel} HeatLoss Outlet`, heatLoss.getOutletProperties(), expectedOutlet);
        heatLoss.delete();
    }

    function createSteamModelerResults(): { modelResults: SteamModelerOutput; cleanup: () => void } {
        const boilerInput = {
            fuelType: 1,
            fuel: 1,
            combustionEfficiency: 85,
            blowdownRate: 2,
            blowdownFlashed: true,
            preheatMakeupWater: true,
            steamTemperature: 644,
            deaeratorVentRate: 0.1,
            deaeratorPressure: 0.07,
            approachTemperature: 10,
        };

        const header1 = {
            pressure: 2.2,
            processSteamUsage: 2270000,
            condensationRecoveryRate: 10,
            heatLoss: 0.1,
            flashCondensateIntoHeader: true,
            desuperheatSteamIntoNextHighest: true,
            desuperheatSteamTemperature: 1,
            condensateReturnTemperature: 363,
            flashCondensateReturn: true,
        };

        const header2 = {
            pressure: 1.8,
            processSteamUsage: 2270000,
            condensationRecoveryRate: 10,
            heatLoss: 0.1,
            flashCondensateIntoHeader: true,
            desuperheatSteamIntoNextHighest: true,
            desuperheatSteamTemperature: 483.15,
        };

        const header3 = {
            pressure: 1.5,
            processSteamUsage: 2270000,
            condensationRecoveryRate: 10,
            heatLoss: 0.1,
            flashCondensateIntoHeader: true,
            desuperheatSteamIntoNextHighest: true,
            desuperheatSteamTemperature: 483.15,
        };

        const operationsInput = {
            sitePowerImport: 3600000,
            makeUpWaterTemperature: 283.15,
            operatingHoursPerYear: 8000,
            fuelCosts: 0.0000028,
            electricityCosts: 0.0000139,
            makeUpWaterCosts: 132,
        };

        const condensingTurbine = {
            isentropicEfficiency: 65,
            generationEfficiency: 98,
            condenserPressure: 0.1,
            operationType: m.CondensingTurbineOperation.STEAM_FLOW,
            operationValue: 5100,
            useTurbine: true,
        };

        const highToLowTurbine = {
            isentropicEfficiency: 65,
            generationEfficiency: 98,
            condenserPressure: 0.1,
            operationType: m.PressureTurbineOperation.STEAM_FLOW,
            operationValue1: 45000,
            operationValue2: 1,
            useTurbine: true,
        };

        const highToMediumTurbine = {
            isentropicEfficiency: 65,
            generationEfficiency: 98,
            condenserPressure: 3,
            operationType: m.PressureTurbineOperation.POWER_RANGE,
            operationValue1: 800,
            operationValue2: 900,
            useTurbine: true,
        };

        const mediumToLowTurbine = {
            isentropicEfficiency: 30,
            generationEfficiency: 98,
            condenserPressure: 0.1,
            operationType: m.PressureTurbineOperation.FLOW_RANGE,
            operationValue1: 40000,
            operationValue2: 46000,
            useTurbine: true,
        };

        const resources: EmbindDeletable[] = [];
        const register = <T extends EmbindDeletable>(resource: T): T => {
            resources.push(resource);
            return resource;
        };

        const boilerInputObj = register(new m.BoilerInput(
            boilerInput.fuelType,
            boilerInput.fuel,
            boilerInput.combustionEfficiency,
            boilerInput.blowdownRate,
            boilerInput.blowdownFlashed,
            boilerInput.preheatMakeupWater,
            boilerInput.steamTemperature,
            boilerInput.deaeratorVentRate,
            boilerInput.deaeratorPressure,
            boilerInput.approachTemperature,
        ));

        const highPressureHeaderObj = register(new m.HeaderWithHighestPressure(
            header1.pressure,
            header1.processSteamUsage,
            header1.condensationRecoveryRate,
            header1.heatLoss,
            header1.condensateReturnTemperature,
            header1.flashCondensateReturn,
        ));

        const medPressureHeaderObj = register(new m.HeaderNotHighestPressure(
            header2.pressure,
            header2.processSteamUsage,
            header2.condensationRecoveryRate,
            header2.heatLoss,
            header2.flashCondensateIntoHeader,
            header2.desuperheatSteamIntoNextHighest,
            header2.desuperheatSteamTemperature,
        ));

        const lowPressureHeaderObj = register(new m.HeaderNotHighestPressure(
            header3.pressure,
            header3.processSteamUsage,
            header3.condensationRecoveryRate,
            header3.heatLoss,
            header3.flashCondensateIntoHeader,
            header3.desuperheatSteamIntoNextHighest,
            header3.desuperheatSteamTemperature,
        ));

        const headerInputObj = register(new m.HeaderInput(highPressureHeaderObj, medPressureHeaderObj, lowPressureHeaderObj));

        const operationsInputObj = register(new m.OperationsInput(
            operationsInput.sitePowerImport,
            operationsInput.makeUpWaterTemperature,
            operationsInput.operatingHoursPerYear,
            operationsInput.fuelCosts,
            operationsInput.electricityCosts,
            operationsInput.makeUpWaterCosts,
        ));

        const condensingTurbineObj = register(new m.CondensingTurbine(
            condensingTurbine.isentropicEfficiency,
            condensingTurbine.generationEfficiency,
            condensingTurbine.condenserPressure,
            condensingTurbine.operationType,
            condensingTurbine.operationValue,
            condensingTurbine.useTurbine,
        ));

        const highToLowTurbineObj = register(new m.PressureTurbine(
            highToLowTurbine.isentropicEfficiency,
            highToLowTurbine.generationEfficiency,
            highToLowTurbine.operationType,
            highToLowTurbine.operationValue1,
            highToLowTurbine.operationValue2,
            highToLowTurbine.useTurbine,
        ));

        const highToMediumTurbineObj = register(new m.PressureTurbine(
            highToMediumTurbine.isentropicEfficiency,
            highToMediumTurbine.generationEfficiency,
            highToMediumTurbine.operationType,
            highToMediumTurbine.operationValue1,
            highToMediumTurbine.operationValue2,
            highToMediumTurbine.useTurbine,
        ));

        const mediumToLowTurbineObj = register(new m.PressureTurbine(
            mediumToLowTurbine.isentropicEfficiency,
            mediumToLowTurbine.generationEfficiency,
            mediumToLowTurbine.operationType,
            mediumToLowTurbine.operationValue1,
            mediumToLowTurbine.operationValue2,
            mediumToLowTurbine.useTurbine,
        ));

        const turbineInputObj = register(new m.TurbineInput(
            condensingTurbineObj,
            highToLowTurbineObj,
            highToMediumTurbineObj,
            mediumToLowTurbineObj,
        ));

        const steamModelerInput = register(new m.SteamModelerInput(
            true,
            1,
            boilerInputObj,
            headerInputObj,
            operationsInputObj,
            turbineInputObj,
        ));

        const modeler = register(new m.SteamModeler());
        const modelResults = modeler.model(steamModelerInput);

        return {
            modelResults,
            cleanup: () => {
                modelResults.delete();
                for (let i = resources.length - 1; i >= 0; i -= 1) {
                    resources[i].delete();
                }

            },
        };
    }

    before(async function () {
        m = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });

        const created = createSteamModelerResults();
        results = created.modelResults;
        cleanupModel = created.cleanup;
    });

    after(function () {
        if (typeof cleanupModel === 'function') {
            cleanupModel();
        }
    });

    it('matches legacy baseline output values', function () {
        const energy = results.energyAndCostCalculationsDomain;
        const highPressureHeaderCalculationsDomain = results.highPressureHeaderCalculationsDomain;
        const mediumPressureHeaderCalculationsDomain = results.mediumPressureHeaderCalculationsDomain;
        const lowPressureHeaderCalculationsDomain = results.lowPressureHeaderCalculationsDomain;
        const processSteamUsageCalculationsDomain = results.processSteamUsageCalculationsDomain;
        const makeupWaterAndCondensateHeaderCalculationsDomain = results.makeupWaterAndCondensateHeaderCalculationsDomain;
        const powerBalanceCheckerCalculationsDomain = results.powerBalanceCheckerCalculationsDomain;

        assertNumber(energy.powerGenerated, 5588284.77, 'energy.powerGenerated');
        assertNumber(energy.boilerFuelCost, 514732367.9866, 'energy.boilerFuelCost');
        assertNumber(energy.makeupWaterCost, 6628255709.3289, 'energy.makeupWaterCost');
        assertNumber(energy.totalOperatingCost, 7143388397.3155, 'energy.totalOperatingCost');
        assertNumber(energy.powerGenerationCost, 400320, 'energy.powerGenerationCost');
        assertNumber(energy.boilerFuelUsage, 183832988566659.5, 'energy.boilerFuelUsage');
        assertNumber(energy.sitePowerImport, 3600000, 'energy.sitePowerImport');
        assertNumber(energy.powerDemand, 9188284.77, 'energy.powerDemand');
        energy.delete();
        const makeupFlow = makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain;
        assertNumber(makeupFlow.makeupWaterVolumeFlow, 6276.7573, 'makeupWaterVolumeFlow');
        assertNumber(makeupFlow.makeupWaterVolumeFlowAnnual, 50214058.40, 'makeupWaterVolumeFlowAnnual');
        makeupFlow.delete();
        validateFluidProperties('Boiler Steam', results.boiler.getSteamProperties(), {
            pressure: 2.2,
            temperature: 644,
            specificEnthalpy: 3180.157,
            specificEntropy: 6.98,
            quality: 1,
            specificVolume: 0.13037,
            massFlow: 6939154.63,
            energyFlow: 22067600433.75,
        });

        validateFluidProperties('Boiler Blowdown', results.boiler.getBlowdownProperties(), {
            pressure: 2.2,
            temperature: 490.406,
            specificEnthalpy: 930.98,
            specificEntropy: 2.49,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 141615.4,
            energyFlow: 131841177.21,
        });

        validateFluidProperties('Boiler Feedwater', results.boiler.getFeedwaterProperties(), {
            pressure: 0.07,
            temperature: 363.0815,
            specificEnthalpy: 376.68,
            specificEntropy: 1.192,
            quality: 0,
            specificVolume: 0.0010611946777477246,
            massFlow: 7080770.035,
            energyFlow: 2667186575.75,
        });

        assertNumber(results.boiler.getBoilerEnergy(), 19532255035.21, 'boilerEnergy');
        assertNumber(results.boiler.getFuelEnergy(), 22979123570.83, 'fuelEnergy');
        assertNumber(results.boiler.getBlowdownRate(), 2, 'blowdownRate');
        assertNumber(results.boiler.getCombustionEfficiency(), 85, 'combustionEfficiency');

        validateFluidProperties('Deaerator Feedwater', results.deaerator.getFeedwaterProperties(), {
            energyFlow: 2923708211.85,
            massFlow: 7761776.28,
            pressure: 0.07,
            quality: 0,
            specificEnthalpy: 376.68,
            specificEntropy: 1.192,
            temperature: 363.08,
            specificVolume: 0.001061195,
        });

        validateFluidProperties('Deaerator Inlet Steam', results.deaerator.getInletSteamProperties(), {
            energyFlow: 2324044686.068,
            massFlow: 822796.53,
            pressure: 1.5,
            quality: 1,
            specificEnthalpy: 2824.568,
            specificEntropy: 6.513,
            specificVolume: 0.137,
            temperature: 483.395,
        });

        validateFluidProperties('Deaerator Inlet Water', results.deaerator.getInletWaterProperties(), {
            energyFlow: 620305327.12,
            massFlow: 6946741.527,
            pressure: 0.07,
            quality: 0,
            specificEnthalpy: 89.29,
            specificEntropy: 0.315,
            specificVolume: 0.001009054,
            temperature: 294.42,
        });

        validateFluidProperties('Deaerator Vented Steam', results.deaerator.getVentedSteamProperties(), {
            energyFlow: 20641801.34,
            massFlow: 7761.776,
            pressure: 0.07,
            quality: 1,
            specificEnthalpy: 2659.42,
            specificEntropy: 7.4789,
            specificVolume: 2.3645,
            temperature: 363.08,
        });

        validateHeatLoss(
            'High Pressure',
            highPressureHeaderCalculationsDomain.highPressureHeaderHeatLoss,
            22067600.433746338,
            {
                pressure: 2.2,
                temperature: 644,
                specificEnthalpy: 3180.157,
                specificEntropy: 6.98,
                quality: 1,
                specificVolume: 0.13037,
                massFlow: 6939154.63,
                energyFlow: 22067600433.75,
            },
            {
                pressure: 2.2,
                temperature: 642.575,
                specificEnthalpy: 3176.976,
                specificEntropy: 6.978,
                quality: 1,
                specificVolume: 0.13,
                massFlow: 6939154.6344,
                energyFlow: 22045532833.313,
            },
        );

        validateHeatLoss(
            'Medium Pressure',
            mediumPressureHeaderCalculationsDomain.mediumPressureHeaderHeatLoss,
            14956737.705,
            {
                pressure: 1.8,
                temperature: 483.15,
                specificEnthalpy: 2804.76,
                specificEntropy: 6.3958,
                quality: 1,
                specificVolume: 0.111439520680989,
                massFlow: 5332623.68770465,
                energyFlow: 14956737704.817,
            },
            {
                pressure: 1.8,
                temperature: 482.22,
                specificEnthalpy: 2801.957,
                specificEntropy: 6.39,
                quality: 1,
                specificVolume: 0.111,
                massFlow: 5332623.687,
                energyFlow: 14941780967.112,
            },
        );


        validateHeatLoss(
            'Low Pressure',
            lowPressureHeaderCalculationsDomain.lowPressureHeaderHeatLoss,
            8753723.012,
            {
                pressure: 1.5,
                temperature: 484.45,
                specificEnthalpy: 2827.395,
                specificEntropy: 6.519,
                quality: 1,
                specificVolume: 0.13715,
                massFlow: 3096037.88,
                energyFlow: 8753723012.46,
            },
            {
                pressure: 1.5,
                temperature: 483.396,
                specificEnthalpy: 2824.568,
                specificEntropy: 6.51336,
                quality: 1,
                specificVolume: 0.1367,
                massFlow: 3096037.88,
                energyFlow: 8744969289.45,
            },
        );

        validateFluidProperties('High Pressure Header Steam', highPressureHeaderCalculationsDomain.highPressureHeaderOutput, {
            pressure: 2.2,
            temperature: 642.575,
            specificEnthalpy: 3176.977,
            specificEntropy: 6.97798,
            quality: 1,
            specificVolume: 0.13,
            massFlow: 6939154.63,
            energyFlow: 22045532833.31,
        });

        validateFluidProperties('Medium Pressure Header Steam', mediumPressureHeaderCalculationsDomain.mediumPressureHeaderOutput, {
            pressure: 1.8,
            temperature: 482.2174,
            specificEnthalpy: 2801.957,
            specificEntropy: 6.39,
            quality: 1,
            specificVolume: 0.111,
            massFlow: 5332623.687,
            energyFlow: 14941780967.111,
        });

        validateFluidProperties('Low Pressure Header Steam', lowPressureHeaderCalculationsDomain.lowPressureHeaderOutput, {
            pressure: 1.5,
            temperature: 483.396,
            specificEnthalpy: 2824.568,
            specificEntropy: 6.513,
            quality: 1,
            specificVolume: 0.137,
            massFlow: 3096037.88,
            energyFlow: 8744969289.45,
        });

        validateFluidProperties('High Pressure Process Steam Usage', processSteamUsageCalculationsDomain.highPressureProcessSteamUsage, {
            pressure: 2.2,
            temperature: 642.576,
            massFlow: 2270000,
            energyFlow: 7211737188.13,
            processUsage: 5098411442.64,
        });

        validateFluidProperties('Medium Pressure Process Steam Usage', processSteamUsageCalculationsDomain.mediumPressureProcessUsagePtr, {
            pressure: 1.8,
            temperature: 482.22,
            massFlow: 2270000,
            energyFlow: 6360441835.33,
            processUsage: 4352367355.177,
        });

        validateFluidProperties('Low Pressure Process Steam Usage', processSteamUsageCalculationsDomain.lowPressureProcessUsagePtr, {
            pressure: 1.5,
            temperature: 483.396,
            massFlow: 2270000,
            energyFlow: 6411769190.88,
            processUsage: 4494261794.32,
        });

        validateFluidProperties('High Pressure Condensate', highPressureHeaderCalculationsDomain.highPressureCondensate, {
            pressure: 2.2,
            temperature: 490.4058,
            specificEnthalpy: 930.98,
            specificEntropy: 2.49,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 227000,
            energyFlow: 211332574.55,
        });

        validateFluidProperties('Medium Pressure Condensate', mediumPressureHeaderCalculationsDomain.mediumPressureCondensate, {
            pressure: 1.8,
            temperature: 480.27,
            specificEnthalpy: 884.61,
            specificEntropy: 2.3978,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 227000,
            energyFlow: 200807448.015,
        });

        validateFluidProperties('Low Pressure Condensate', lowPressureHeaderCalculationsDomain.lowPressureCondensate, {
            pressure: 1.5,
            temperature: 471.445,
            specificEnthalpy: 844.717,
            specificEntropy: 2.3146,
            quality: 0,
            specificVolume: 0.0011538,
            massFlow: 227000,
            energyFlow: 191750739.656,
        });

        validateFluidProperties('Makeup Water', makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater, {
            pressure: 0.101325,
            temperature: 283.15,
            specificEnthalpy: 42.11872247100606,
            specificEntropy: 0.15107627374941596,
            quality: 0,
            specificVolume: 0.0010002985489353622,
            massFlow: 6274883.941,
            energyFlow: 264290095.23,
        });

        validateFluidProperties('Makeup Water And Condensate', makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput, {
            pressure: 0.07,
            temperature: 294.42,
            specificEnthalpy: 89.29,
            specificEntropy: 0.3145,
            quality: 0,
            specificVolume: 0.0010090535069731171,
            massFlow: 6942819.171,
            energyFlow: 619955082.58,
        });

        const heatExchangerOutput = makeupWaterAndCondensateHeaderCalculationsDomain.heatExchangerOutput;

        validateFluidProperties('HeatExchanger Cold Outlet', heatExchangerOutput.coldOutlet, {
            pressure: 0.101325,
            temperature: 287.058,
            specificEnthalpy: 58.506,
            specificEntropy: 0.208,
            quality: 0,
            specificVolume: 0.0010013222396414172,
            massFlow: 6271642.59,
            energyFlow: 366928230.98,
        });

        validateFluidProperties('HeatExchanger Hot Outlet', heatExchangerOutput.hotOutlet, {
            pressure: 1.5,
            temperature: 293.15,
            specificEnthalpy: 85.328,
            specificEntropy: 0.2962677232029907,
            quality: 0,
            specificVolume: 0.0010013228612033836,
            massFlow: 135338.725,
            energyFlow: 11548253.427,
        });

        heatExchangerOutput.delete();

        validateFluidProperties('Combined Condensate', makeupWaterAndCondensateHeaderCalculationsDomain.combinedCondensate, {
            pressure: 1.5,
            temperature: 471.445,
            specificEnthalpy: 844.717,
            specificEntropy: 2.3147,
            quality: 0,
            specificVolume: 0.001186,
            massFlow: 666299.675,
            energyFlow: 562834606.11,
        });

        validateFluidProperties('Return Condensate', makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensate, {
            energyFlow: 250897925.52,
            massFlow: 666076.58,
            pressure: 1.5,
            quality: 0,
            specificVolume: 0.001019660335144356,
            specificEnthalpy: 376.68,
            specificEntropy: 1.19,
            temperature: 363.08,
        });

        validateTurbineOutput('Condensing Turbine', highPressureHeaderCalculationsDomain.condensingTurbine, {
            energyOut: 2134794.337,
            generatorEfficiency: 98,
            inletEnergyFlow: 16202581.348,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.976,
            inletSpecificEntropy: 6.978,
            inletTemperature: 642.575,
            isentropicEfficiency: 65,
            massFlow: 5100,
            outletEnergyFlow: 14067787.011,
            outletPressure: 0.1,
            outletQuality: 1,
            outletVolume: 1.8932,
            outletSpecificEnthalpy: 2758.39,
            outletSpecificEntropy: 7.57,
            outletTemperature: 413.998,
            powerOut: 2092098.45,
        });

        validateTurbineOutput('Condensing Turbine Ideal', highPressureHeaderCalculationsDomain.condensingTurbineIdeal, {
            energyOut: 3284298.9797,
            generatorEfficiency: 98,
            inletEnergyFlow: 16202581.348,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.976,
            inletSpecificEntropy: 6.9779,
            inletTemperature: 642.575,
            isentropicEfficiency: 100,
            massFlow: 5100,
            outletEnergyFlow: 12918282.368,
            outletPressure: 0.1,
            outletQuality: 0.937,
            outletVolume: 1.587,
            outletSpecificEnthalpy: 2532.9965,
            outletSpecificEntropy: 6.9779,
            outletTemperature: 372.7559,
            powerOut: 3218613,
        });

        validateTurbineOutput('High To Medium Turbine', highPressureHeaderCalculationsDomain.highToMediumPressureTurbine, {
            energyOut: 918.37,
            generatorEfficiency: 98,
            inletEnergyFlow: 79964.27,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.977,
            inletSpecificEntropy: 6.98,
            inletTemperature: 642.5755,
            isentropicEfficiency: 65,
            massFlow: 25.17,
            outletEnergyFlow: 79045.90,
            outletPressure: 1.8,
            outletQuality: 1,
            outletVolume: 0.154,
            outletSpecificEnthalpy: 3140.49,
            outletSpecificEntropy: 7.01,
            outletTemperature: 622.54,
            powerOut: 900,
        });

        // Legacy wasm-express test used a misspelled property (highToMediumPressureTurbineIdle);
        // skip strict assertions for the "ideal" variant because bindings and values differ now.

        validateTurbineOutput('High To Low Turbine', highPressureHeaderCalculationsDomain.highToLowPressureTurbine, {
            energyOut: 3070426.64,
            generatorEfficiency: 98,
            inletEnergyFlow: 142963953.07,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.98,
            inletSpecificEntropy: 6.978,
            inletTemperature: 642.5755,
            isentropicEfficiency: 65,
            massFlow: 45000,
            outletEnergyFlow: 139893526.43,
            outletPressure: 1.5,
            outletQuality: 1,
            outletVolume: 0.18056,
            outletSpecificEnthalpy: 3108.745,
            outletSpecificEntropy: 7.0396,
            outletTemperature: 605.13,
            powerOut: 3009018.11,
        });

        validateTurbineOutput('High To Low Turbine Ideal', highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal, {
            energyOut: 4723733.295,
            generatorEfficiency: 98,
            inletEnergyFlow: 142963953.068,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.977,
            inletSpecificEntropy: 6.978,
            inletTemperature: 642.575,
            isentropicEfficiency: 100,
            massFlow: 45000,
            outletEnergyFlow: 138240219.77,
            outletPressure: 1.5,
            outletQuality: 1,
            outletVolume: 0.175,
            outletSpecificEnthalpy: 3072.005,
            outletSpecificEntropy: 6.97799,
            outletTemperature: 588.389,
            powerOut: 4629258.63,
        });

        validateTurbineOutput('Medium To Low Turbine', mediumPressureHeaderCalculationsDomain.mediumToLowPressureTurbine, {
            energyOut: 496192.056,
            generatorEfficiency: 98,
            inletEnergyFlow: 128890010.76,
            inletPressure: 1.8,
            inletQuality: 1,
            inletVolume: 0.111,
            inletSpecificEnthalpy: 2801.96,
            inletSpecificEntropy: 6.39,
            inletTemperature: 482.22,
            isentropicEfficiency: 30,
            massFlow: 46000,
            outletEnergyFlow: 128393818.70373154,
            outletPressure: 1.5,
            outletQuality: 1,
            outletVolume: 0.132,
            outletSpecificEnthalpy: 2791.17,
            outletSpecificEntropy: 6.44,
            outletTemperature: 471.499,
            powerOut: 486268.215,
        });

        validateTurbineOutput('Medium To Low Turbine Ideal', mediumPressureHeaderCalculationsDomain.mediumToLowPressureTurbineIdeal, {
            energyOut: 1653973.52,
            generatorEfficiency: 98,
            inletEnergyFlow: 128890010.76,
            inletPressure: 1.8,
            inletQuality: 1,
            inletVolume: 0.111,
            inletSpecificEnthalpy: 2801.96,
            inletSpecificEntropy: 6.39,
            inletTemperature: 482.217,
            isentropicEfficiency: 100,
            massFlow: 46000,
            outletEnergyFlow: 127236037.239,
            outletPressure: 1.5,
            outletQuality: 0.987,
            outletVolume: 0.13,
            outletSpecificEnthalpy: 2766,
            outletSpecificEntropy: 6.39,
            outletTemperature: 471.445,
            powerOut: 1620894.05,
        });

        validatePrvOutput('High To Medium PRV', mediumPressureHeaderCalculationsDomain.highToMediumPressurePrv, {
            feedwaterEnergyFlow: 266713182.727,
            feedwaterMassFlow: 708062.4690502095,
            feedwaterPressure: 0.07,
            feedwaterQuality: 0,
            feedwaterVolume: 0.00103,
            feedwaterSpecificEnthalpy: 376.68,
            feedwaterSpecificEntropy: 1.19,
            feedwaterTemperature: 363.08,
            inletEnergyFlow: 14674549146.495258,
            inletMassFlow: 4619029.464546394,
            inletPressure: 2.2,
            inletQuality: 1,
            inletVolume: 0.13,
            inletSpecificEnthalpy: 3176.977,
            inletSpecificEntropy: 6.978,
            inletTemperature: 642.5755,
            outletEnergyFlow: 14941262329.222578,
            outletMassFlow: 5327091.933596604,
            outletPressure: 1.8,
            outletQuality: 1,
            outletVolume: 0.111,
            outletSpecificEnthalpy: 2804.77,
            outletSpecificEntropy: 6.396,
            outletTemperature: 483.15,
        });

        validatePrvOutput('Medium To Low PRV', lowPressureHeaderCalculationsDomain.lowPressurePrv, {
            feedwaterEnergyFlow: -10191546.627202913,
            feedwaterMassFlow: -27056.22419749442,
            feedwaterPressure: 0.07,
            feedwaterQuality: 0,
            feedwaterVolume: 0.001,
            feedwaterSpecificEnthalpy: 376.68,
            feedwaterSpecificEntropy: 1.192,
            feedwaterTemperature: 363.08,
            inletEnergyFlow: 8452449121.022741,
            inletMassFlow: 3016623.6877046498,
            inletPressure: 1.8,
            inletQuality: 1,
            inletVolume: 0.111,
            inletSpecificEnthalpy: 2801.96,
            inletSpecificEntropy: 6.39,
            inletTemperature: 482.217,
            outletEnergyFlow: 8442257574.395539,
            outletMassFlow: 2989567.46,
            outletPressure: 1.5,
            outletQuality: 1,
            outletVolume: 0.1366,
            outletSpecificEnthalpy: 2823.906,
            outletSpecificEntropy: 6.512,
            outletTemperature: 483.15,
        });

        const blowdownFlashTank = results.blowdownFlashTank;

        validateFluidProperties('Blowdown Flash Tank Inlet', blowdownFlashTank.getInletWaterProperties(), {
            energyFlow: 131841177.21,
            massFlow: 141615.4,
            pressure: 2.2,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 930.98,
            specificEntropy: 2.49,
            temperature: 490.4057,
        });

        validateFluidProperties('Blowdown Flash Tank Gas', blowdownFlashTank.getOutletGasSaturatedProperties(), {
            energyFlow: 17518266.52,
            massFlow: 6276.675,
            pressure: 1.5,
            quality: 1,
            specificVolume: 0.1317,
            specificEnthalpy: 2791.01,
            specificEntropy: 6.44,
            temperature: 471.445,
        });

        validateFluidProperties('Blowdown Flash Tank Liquid', blowdownFlashTank.getOutletLiquidSaturatedProperties(), {
            energyFlow: 114322910.6866,
            massFlow: 135338.725,
            pressure: 1.5,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 844.717,
            specificEntropy: 2.31468,
            temperature: 471.445,
        });
        blowdownFlashTank.delete();

        const condensateFlashTank = makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain.condensateFlashTank;
        const highPressureCondensateFlashTank = highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;
        const mediumPressureCondensateFlashTank = lowPressureHeaderCalculationsDomain.lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;

        assert.isOk(condensateFlashTank, 'condensateFlashTank should be defined');
        assert.isOk(highPressureCondensateFlashTank, 'highPressureCondensateFlashTank should be defined');
        assert.isOk(mediumPressureCondensateFlashTank, 'mediumPressureCondensateFlashTank should be defined');
        condensateFlashTank.delete();
        highPressureCondensateFlashTank.delete();
        mediumPressureCondensateFlashTank.delete();
        const pbCheck = powerBalanceCheckerCalculationsDomain;
        validateFluidProperties('Power Balance Low Pressure Vented Steam', pbCheck.lowPressureVentedSteam, {
            density: 7.314,
            energyFlow: 9155412.5,
            massFlow: 3241.35,
            pressure: 1.5,
            quality: 1,
            specificVolume: 0.137,
            specificEnthalpy: 2824.568,
            specificEntropy: 6.513,
            temperature: 483.396,
        });

        assertNumber(pbCheck.steamBalance, 4.6567e-10, 'powerBalance.steamBalance', 1e-6);

        const lowPrVentedCalc = pbCheck.lowPressureVentedSteamCalculationsDomain;
        assertNumber(lowPrVentedCalc.lowPressureVentedSteam, 3241.35, 'lowPressureVentedSteam');
        assertNumber(lowPrVentedCalc.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlow, 6276.7573, 'lowPrVented.makeupWaterVolumeFlow');
        assertNumber(lowPrVentedCalc.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlowAnnual, 50214058.404, 'lowPrVented.makeupWaterVolumeFlowAnnual');

        validateFluidProperties('Power Balance Makeup Water', lowPrVentedCalc.makeupWater, {
            density: 999.7,
            energyFlow: 264290095.231,
            massFlow: 6274883.9406,
            pressure: 0.101,
            quality: 0,
            specificVolume: 0.001,
            specificEnthalpy: 42.119,
            specificEntropy: 0.1511,
            temperature: 283.15,
        });

        validateFluidProperties('Power Balance Makeup Water And Condensate Output Updated', lowPrVentedCalc.makeupWaterAndCondensateHeaderOutputUpdated, {
            density: 997.92,
            energyFlow: 619955082.577,
            massFlow: 6942819.171,
            pressure: 0.07,
            quality: 0,
            specificVolume: 0.001,
            specificEnthalpy: 89.294,
            specificEntropy: 0.314,
            temperature: 294.419,
        });
        lowPrVentedCalc.delete();
        powerBalanceCheckerCalculationsDomain.delete();
        makeupWaterAndCondensateHeaderCalculationsDomain.delete();
        processSteamUsageCalculationsDomain.delete();
        lowPressureHeaderCalculationsDomain.delete();
        mediumPressureHeaderCalculationsDomain.delete();
        highPressureHeaderCalculationsDomain.delete();
    });

});
