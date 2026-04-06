export function getHighPressureHeaderObject(header, moduleInstance) {
    return new moduleInstance.HeaderWithHighestPressure(
        header.pressure,
        header.processSteamUsage,
        header.condensationRecoveryRate,
        header.heatLoss,
        header.condensateReturnTemperature,
        header.flashCondensateReturn
    );
}

export function getCondensingTurbineOperation(option, moduleInstance) {
    switch (option) {
        case 0:
            return moduleInstance.CondensingTurbineOperation.STEAM_FLOW;
        case 1:
            return moduleInstance.CondensingTurbineOperation.POWER_GENERATION;

    }
}

export function getPressureTurbineOperation(option, moduleInstance) {
    switch (option) {
        case 0:
            return moduleInstance.PressureTurbineOperation.STEAM_FLOW;
        case 1:
            return moduleInstance.PressureTurbineOperation.POWER_GENERATION;
        case 2:
            return moduleInstance.PressureTurbineOperation.BALANCE_HEADER;
        case 3:
            return moduleInstance.PressureTurbineOperation.POWER_RANGE;
        case 4:
            return moduleInstance.PressureTurbineOperation.FLOW_RANGE;
    }
}

export function getNotHighPressureHeaderObject(header, moduleInstance) {
    if (!header.processSteamUsage) {
        // Adding property for modification where user has not selected calculated from baseline
        header.processSteamUsage = 0;
    }
    return new moduleInstance.HeaderNotHighestPressure(
        header.pressure,
        header.processSteamUsage,
        header.condensationRecoveryRate,
        header.heatLoss,
        header.flashCondensateIntoHeader,
        header.desuperheatSteamIntoNextHighest,
        header.desuperheatSteamTemperature,
    );
}