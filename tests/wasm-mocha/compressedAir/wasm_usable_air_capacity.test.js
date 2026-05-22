import { assert } from 'chai';

describe('Compressed Air Usable Air Capacity', function () {
    let moduleInstance;

    before(async function () {
        const ToolsSuiteModule = (await import('../../../bin/client.js')).default;
        moduleInstance = await ToolsSuiteModule({
            locateFile: (filename) => '/base/bin/' + filename
        });
    });

    it('should calculate usable capacity with a 10 PSI pressure differential', function () {
        const receiverTank = new moduleInstance.ReceiverTank();

        const result = receiverTank.calculateUsableCapacity(660, 110, 100);
        assert.approximately(result, 60.024009603, 0.01);

        receiverTank.delete();
    });

    it('should calculate usable capacity for a larger tank with a 10 PSI pressure differential', function () {
        const receiverTank = new moduleInstance.ReceiverTank();

        const result = receiverTank.calculateUsableCapacity(760, 110, 100);
        assert.approximately(result, 69.1185565135, 0.01);

        receiverTank.delete();
    });

    it('should calculate usable capacity with a 50 PSI pressure differential', function () {
        const receiverTank = new moduleInstance.ReceiverTank();

        const result = receiverTank.calculateUsableCapacity(760, 150, 100);
        assert.approximately(result, 345.5927825676, 0.01);

        receiverTank.delete();
    });

    it('should calculate usable capacity with a 20 PSI pressure differential at higher pressure', function () {
        const receiverTank = new moduleInstance.ReceiverTank();

        const result = receiverTank.calculateUsableCapacity(760, 150, 130);
        assert.approximately(result, 138.237113027, 0.01);

        receiverTank.delete();
    });
});
