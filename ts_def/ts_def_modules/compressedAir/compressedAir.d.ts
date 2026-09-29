export * from "./pipe_data";
export * from "./air_system_capacity";
export * from "./air_velocity";

/**
 * Aggregate compressed air module surface.
 */
export type CompressedAirModule =
    import("./pipe_data").PipeDataModule &
    import("./air_system_capacity").AirSystemCapacityModule &
    import("./air_velocity").AirVelocityModule;
