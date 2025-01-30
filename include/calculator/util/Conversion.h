#ifndef TOOLS_SUITE_CONVERSION_H
#define TOOLS_SUITE_CONVERSION_H

class Conversion
{
  public:
    Conversion(double x)
        : x(x)
    {}

    double fractionToPercent();
    double percentToFraction();
    double manualConversion(double factor);

  private:
    double x;
};

#endif //TOOLS_SUITE_CONVERSION_H