/**
 * @file
 * @brief Contains the implementation of the flash tank calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include <iostream>
#include "steamModeler/FlashTank.h"

FlashTank::FlashTank(const double inletWaterPressure, const SteamProperties::ThermodynamicQuantity quantityType,
					 const double quantityValue, const double inletWaterMassFlow, const double tankPressure)
	: inletWaterPressure(inletWaterPressure), quantityValue(quantityValue), inletWaterMassFlow(inletWaterMassFlow),
	  tankPressure(tankPressure), quantityType(quantityType)
{
	calculateProperties();
}

std::ostream &operator<<(std::ostream &stream, const FlashTank &flashTank) {
    stream << "FlashTank["
           << "inletWaterPressure=" << flashTank.inletWaterPressure
           << ", inletWaterMassFlow=" << flashTank.inletWaterMassFlow
           << ", tankPressure=" << flashTank.tankPressure
           << ", quantityType=" << static_cast< int >(flashTank.quantityType)
           << ", quantityValue=" << flashTank.quantityValue
           << ", inletWaterProperties=" << flashTank.inletWaterProperties
           << ", outletLiquidSaturatedProperties=" << flashTank.outletLiquidSaturatedProperties
           << ", outletGasSaturatedProperties=" << flashTank.outletGasSaturatedProperties
           << "]";

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<FlashTank> &flashTank) {
    if (flashTank == nullptr) {
        stream << "FlashTank[nullptr]";
    } else {
        stream << *flashTank;
    }

    return stream;
}

void FlashTank::calculateProperties()
{
	auto sp = SteamProperties(inletWaterPressure, quantityType, quantityValue).calculate();
	inletWaterProperties = {inletWaterMassFlow, inletWaterMassFlow * sp.specificEnthalpy, sp};

	auto saturatedProperties = SaturatedProperties(tankPressure, SaturatedTemperature(tankPressure).calculate()).calculate();
	double liquidMassFlow;
	if (inletWaterProperties.specificEnthalpy > saturatedProperties.gasSpecificEnthalpy)
	{
		liquidMassFlow = 0;
		// TODO question density is 0 below bc saturated properties doesn't return density, same with both sp objects here
		sp = {
			saturatedProperties.temperature, saturatedProperties.pressure, 0,
			saturatedProperties.liquidSpecificVolume, 0,
			saturatedProperties.liquidSpecificEnthalpy, saturatedProperties.liquidSpecificEntropy};
		outletLiquidSaturatedProperties = {
			liquidMassFlow,
			liquidMassFlow * saturatedProperties.liquidSpecificEnthalpy,
			sp};
	}
	else if (inletWaterProperties.specificEnthalpy < saturatedProperties.liquidSpecificEnthalpy)
	{
		liquidMassFlow = inletWaterMassFlow;
		outletLiquidSaturatedProperties = inletWaterProperties;
	}
	else
	{
		liquidMassFlow = inletWaterMassFlow * (inletWaterProperties.specificEnthalpy - saturatedProperties.gasSpecificEnthalpy) / (saturatedProperties.liquidSpecificEnthalpy - saturatedProperties.gasSpecificEnthalpy);
		// TODO question density is 0 below bc saturated properties doesn't return density, same with both sp objects here
		sp = {
			saturatedProperties.temperature, saturatedProperties.pressure, 0,
			saturatedProperties.liquidSpecificVolume, 0,
			saturatedProperties.liquidSpecificEnthalpy, saturatedProperties.liquidSpecificEntropy};

		outletLiquidSaturatedProperties = {
			liquidMassFlow,
			liquidMassFlow * saturatedProperties.liquidSpecificEnthalpy,
			sp};
	}

	sp = {
		saturatedProperties.temperature, saturatedProperties.pressure, 1,
		saturatedProperties.gasSpecificVolume, 0,
		saturatedProperties.gasSpecificEnthalpy, saturatedProperties.gasSpecificEntropy};

	double const gasMassFlow = inletWaterMassFlow - outletLiquidSaturatedProperties.massFlow;
	outletGasSaturatedProperties = {gasMassFlow, gasMassFlow * sp.specificEnthalpy, sp};
}

double FlashTank::getInletWaterPressure() const { return inletWaterPressure; }

double FlashTank::getQuantityValue() const { return quantityValue; }

double FlashTank::getInletWaterMassFlow() const { return inletWaterMassFlow; }

double FlashTank::getTankPressure() const { return tankPressure; }

SteamProperties::ThermodynamicQuantity FlashTank::getQuantityType() const { return quantityType; }

void FlashTank::setInletWaterPressure(double inletWaterPressure)
{
	this->inletWaterPressure = inletWaterPressure;
	calculateProperties();
}

void FlashTank::setQuantityValue(double quantityValue)
{
	this->quantityValue = quantityValue;
	calculateProperties();
}

void FlashTank::setInletWaterMassFlow(double inletWaterMassFlow)
{
	this->inletWaterMassFlow = inletWaterMassFlow;
	calculateProperties();
}

void FlashTank::setTankPressure(double tankPressure)
{
	this->tankPressure = tankPressure;
	calculateProperties();
}

void FlashTank::setQuantityType(SteamProperties::ThermodynamicQuantity quantityType)
{
	this->quantityType = quantityType;
	calculateProperties();
}
