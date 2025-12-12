import { assert } from 'chai';

describe('DB Default Data Test', function () {
    let moduleInstance;
    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('DB Default Data Test', function () {
        function logMessage(msg, header) {
            console.log(msg);
        }

        function motorDataLog(item){
            logMessage(item.getId() + ', ' + item.getHp() + ', ' + item.getSynchronousSpeed() + ', ' +
                item.getPoles() + ', ' + item.getNominalEfficiency()  + ', ' + item.getEfficiencyClass().value + ', ' +
                item.getNemaTable() + ', ' + item.getEnclosureType()  + ', ' + item.getLineFrequency().value + ', ' +
                item.getVoltageLimit() + ', ' + item.getCatalog());
        }

        function motorData(defaultData){
            logMessage('Motor Data');

            let listItems = defaultData.getMotorData();
            let count = listItems.size();
            assert.equal(count, 954, "Select All Default Data");

            logMessage('Default Data (start - end):');
            motorDataLog(listItems.get(0));
            motorDataLog(listItems.get(count-1));

            listItems.delete();
        }

        function compressorDataLog(item){
            logMessage(item.ID() + ', ' + item.idCompType() + ', ' +
                item.model() + ', ' + item.hp()  + ', ' + item.ratedCapacity() + ', ' +
                item.ratedPressure() + ', ' + item.maxFullFlowPressure()  + ', ' + item.idControlType() + ', ' +
                item.unloadPoint() + ', ' + item.minULSumpPressure()  + ', ' + item.blowdownTime() + ', ' +
                item.unloadSteps() + ', ' + item.modulatingPressRange()  + ', ' + item.powerFLBHP() + ', ' +
                item.totPackageInputPower() + ', ' + item.specPackagePower()  + ', ' + item.noLoadPowerFM() + ', ' +
                item.noLoadPowerUL() + ', ' + item.maxSurgePressure()  + ', ' + item.maxPressSurgeFlow() + ', ' +
                item.minStonewallPressure() + ', ' + item.minPressStonewallFlow()  + ', ' + item.designSurgeFlow() + ', ' +
                item.designInTemp() + ', ' + item.designInPressure()  + ', ' + item.ampsFL() + ', ' +
                item.effFL());
        }

        function compressorsData(defaultData){
            logMessage('Compressors Data');

            let listItems = defaultData.getCompressorType1Data();
            let count = listItems.size();
            assert.equal(count, 308, "Select All Compressor Default Data for Type 1 < 100 kW");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType1_GT100kWData();
            count = listItems.size();
            assert.equal(count, 317, "Select All Compressor Default Data for Type 1 > 100 kW");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType2Data();
            count = listItems.size();
            assert.equal(count, 225, "Select All Compressor Default Data for Type 2");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType3Data();
            count = listItems.size();
            assert.equal(count, 180, "Select All Compressor Default Data for Type 3");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType4Data();
            count = listItems.size();
            assert.equal(count, 294, "Select All Compressor Default Data for Type 4");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType5Data();
            count = listItems.size();
            assert.equal(count, 301, "Select All Compressor Default Data for Type 5");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems = defaultData.getCompressorType6Data();
            count = listItems.size();
            assert.equal(count, 5, "Select All Compressor Default Data for Type 6");
            logMessage('Default Data (start - end):');
            compressorDataLog(listItems.get(0));
            compressorDataLog(listItems.get(count-1));

            listItems.delete();
        }

        function lightingDataLog(item){
            logMessage(item.ID() + ', ' + item.category() + ', ' + item.type() + ', ' +
                item.lampsPerFixture() + ', ' + item.lampWattage()  + ', ' + item.lampOutput() + ', ' +
                item.lampLife() + ', ' + item.lampCRI()  + ', ' + item.coefficientOfUtilization() + ', ' +
                item.ballastFactor() + ', ' + item.lumenDegradationFactor());
        }

        function lightingData(defaultData){
            logMessage('Lighting Data');

            let listItems = defaultData.getLightingData();
            let count = listItems.size();
            assert.equal(count, 74, "Select All Default Data");

            logMessage('Default Data (start - end):');
            lightingDataLog(listItems.get(0));
            lightingDataLog(listItems.get(count-1));

            listItems.delete();
        }

        function db(){
            logMessage('DB Default Data Test:');

            let instance = new moduleInstance.DefaultData();
            motorData(instance);
            compressorsData(instance);
            lightingData(instance);

            instance.delete();

            logMessage('DB Default Data Test Complete');
        }

        db();
    });
});
