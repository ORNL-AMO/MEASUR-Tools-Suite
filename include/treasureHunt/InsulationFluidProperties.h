#ifndef TOOLSSUITEAIRPROPERTIESH
#define TOOLSSUITEAIRPROPERTIESH

#include <cmath>

class InsulationFluidProperties
{
public:
    InsulationFluidProperties(double conductivity = 0, double viscosity = 0, double prandtl = 0, double expansionCoefficient = 0, double density = 0,
                              double kinViscosity = 0, double specificHeat = 0, double alpha = 0, double reynolds = 0, double rayleigh = 0)
        : conductivity(conductivity), viscosity(viscosity), prandtl(prandtl), expansionCoefficient(expansionCoefficient), density(density),
        kinViscosity(kinViscosity), specificHeat(specificHeat), alpha(alpha), reynolds(reynolds), rayleigh(rayleigh) {}

    double getConductivity()
    {
        return this->conductivity;
    }

    double getViscosity()
    {
        return this->viscosity;
    }

    double getPrandtl()
    {
        return this->prandtl;
    }

    double getExpansionCoefficient()
    {
        return this->expansionCoefficient;
    }

    double getDensity()
    {
        return this->density;
    }

    double getKinViscosity()
    {
        return this->kinViscosity;
    }

    double getSpecificHeat()
    {
        return this->specificHeat;
    }

    double getAlpha()
    {
        return this->alpha;
    }

    double getReynolds()
    {
        return this->reynolds;
    }

    double getRayleigh()
    {
        return this->rayleigh;
    }

    void setConductivity(double conductivity)
    {
        this->conductivity = conductivity;
    }

    void setViscosity(double viscosity)
    {
        this->viscosity = viscosity;
    }

    void setPrandtl(double prandtl)
    {
        this->prandtl = prandtl;
    }

    void setExpansionCoefficient(double expansionCoefficient)
    {
        this->expansionCoefficient = expansionCoefficient;
    }

    void setDensity(double density)
    {
        this->density = density;
    }

    void setKinViscosity(double kinViscosity)
    {
        this->kinViscosity = kinViscosity;
    }

    void setSpecificHeat(double specificHeat)
    {
        this->specificHeat = specificHeat;
    }

    void setAlpha(double alpha)
    {
        this->alpha = alpha;
    }

    void setReynolds(double reynolds)
    {
        this->reynolds = reynolds;
    }

    void setRayleigh(double rayleigh)
    {
        this->rayleigh = rayleigh;
    }

private:
    double conductivity;
    double viscosity;
    double prandtl;
    double expansionCoefficient;
    double density;
    double kinViscosity;
    double specificHeat;
    double alpha;
    double reynolds;
    double rayleigh;
};

#endif