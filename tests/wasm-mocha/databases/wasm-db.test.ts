import { assert } from 'chai';
import createModule, {
    type CompressorsData,
    type CompressorsDataV,
    type DefaultData,
    type LightingData,
    type LightingDataV,
    type MeasurToolsSuite,
    type MotorData,
    type MotorDataV,
} from 'measur-tools-suite';

describe('DB Default Data Test', function () {
    let moduleInstance: MeasurToolsSuite;
    before(async function () {
        moduleInstance = await createModule({
            locateFile: (filename: string) => '/base/bin/' + filename
        });
    });

    it('DB Default Data Test', function () {
        function logMessage(msg: string): void {
            console.log(msg);
        }

        function motorDataLog(item: MotorData): void {
            logMessage(item.getId() + ', ' + item.getHp() + ', ' + item.getSynchronousSpeed() + ', ' +
                item.getPoles() + ', ' + item.getNominalEfficiency() + ', ' + Number(item.getEfficiencyClass()) + ', ' +
                item.getNemaTable() + ', ' + item.getEnclosureType() + ', ' + Number(item.getLineFrequency()) + ', ' +
                item.getVoltageLimit() + ', ' + item.getCatalog());
        }

        function motorData(defaultData: DefaultData): void {
            logMessage('Motor Data');
            const listItems: MotorDataV = defaultData.getMotorData();
            const count: number = listItems.size();
            assert.equal(count, 954, "Select All Default Data");
            logMessage('Default Data (start - end):');
            motorDataLog(listItems.get(0));
            motorDataLog(listItems.get(count - 1));
            listItems.delete();
        }

        function compressorDataLog(item: CompressorsData): void {
            logMessage(item.ID() + ', ' + item.idCompType() + ', ' +
                item.model() + ', ' + item.hp() + ', ' + item.ratedCapacity() + ', ' +
                item.ratedPressure() + ', ' + item.maxFullFlowPressure() + ', ' + item.idControlType() + ', ' +
                item.unloadPoint() + ', ' + item.minULSumpPressure() + ', ' + item.blowdownTime() + ', ' +
                item.unloadSteps() + ', ' + item.modulatingPressRange() + ', ' + item.powerFLBHP() + ', ' +
                item.totPackageInputPower() + ', ' + item.specPackagePower() + ', ' + item.noLoadPowerFM() + ', ' +
                item.noLoadPowerUL() + ', ' + item.maxSurgePressure() + ', ' + item.maxPressSurgeFlow() + ', ' +
                item.minStonewallPressure() + ', ' + item.minPressStonewallFlow() + ', ' + item.designSurgeFlow() + ', ' +
                item.designInTemp() + ', ' + item.designInPressure() + ', ' + item.ampsFL() + ', ' +
                item.effFL());
        }

        function compressorsData(defaultData: DefaultData): void {
            logMessage('Compressors Data');

            let listItems: CompressorsDataV = defaultData.getCompressorType1Data();
            let count: number = listItems.size();
            assert.equal(count, 308, "Select All Compressor Default Data for Type 1 < 100 kW");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType1_GT100kWData();
            count = listItems.size();
            assert.equal(count, 317, "Select All Compressor Default Data for Type 1 > 100 kW");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType2Data();
            count = listItems.size();
            assert.equal(count, 225, "Select All Compressor Default Data for Type 2");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType3Data();
            count = listItems.size();
            assert.equal(count, 180, "Select All Compressor Default Data for Type 3");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType4Data();
            count = listItems.size();
            assert.equal(count, 294, "Select All Compressor Default Data for Type 4");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType5Data();
            count = listItems.size();
            assert.equal(count, 301, "Select All Compressor Default Data for Type 5");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems = defaultData.getCompressorType6Data();
            count = listItems.size();
            assert.equal(count, 5, "Select All Compressor Default Data for Type 6");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count - 1));

            listItems.delete();
        }

        function lightingDataLog(item: LightingData): void {
            logMessage(item.ID() + ', ' + item.category() + ', ' + item.type() + ', ' +
                item.lampsPerFixture() + ', ' + item.lampWattage() + ', ' + item.lampOutput() + ', ' +
                item.lampLife() + ', ' + item.lampCRI() + ', ' + item.coefficientOfUtilization() + ', ' +
                item.ballastFactor() + ', ' + item.lumenDegradationFactor());
        }

        function lightingData(defaultData: DefaultData): void {
            logMessage('Lighting Data');
            const listItems: LightingDataV = defaultData.getLightingData();
            const count: number = listItems.size();
            assert.equal(count, 74, "Select All Default Data");
            logMessage('Default Data (start - end):');
            lightingDataLog(listItems.get(0));
            lightingDataLog(listItems.get(count - 1));
            listItems.delete();
        }

        function db(): void {
            logMessage('DB Default Data Test:');
            const instance: DefaultData = new moduleInstance.DefaultData();
            motorData(instance);
            compressorsData(instance);
            lightingData(instance);
            instance.delete();
            logMessage('DB Default Data Test Complete');
        }

        db();
    });
});

