/**
 * @file Default data for Lighting system
 *
 * @author Omer Aziz (omerb)
 *
 */

#ifndef MEASUR_TOOLS_SUITE_LIGHTING_DATA_DB_H
#define MEASUR_TOOLS_SUITE_LIGHTING_DATA_DB_H

class LightingData;

std::vector<LightingData> DefaultData::get_default_lighting_data() {
    return {
            {"Metal Halide","175-W Metal Halide",1,175,12000,10000,65,0.45,1.2,0.8333 },
            {"Metal Halide","250-W Metal Halide",1,250,17000,10000,65,0.45,1.15,0.8696 },
            {"Metal Halide","325-W Metal Halide",1,325,22000,15000,65,0.45,1.15,0.8696 },
            {"Metal Halide","350-W Metal Halide",1,350,23000,20000,65,0.45,1.15,0.76 },
            {"Metal Halide","400-W Metal Halide",1,400,26000,20000,65,0.45,1.15,0.8696 },
            {"Metal Halide","1000-W Metal Halide",1,1000,86000,20000,65,0.45,1.1,0.9091 },
            {"High Pressure Sodium","70-W HP Sodium",1,70,5450,24000,22,0.4,1.35,0.7407 },
            {"High Pressure Sodium","100-W HP Sodium",1,100,8550,24000,22,0.4,1.35,0.7407 },
            {"High Pressure Sodium","150-W HP Sodium",1,150,14400,24000,22,0.4,1.25,0.8 },
            {"High Pressure Sodium","250-W HP Sodium",1,250,27000,24000,22,0.4,1.2,0.8333 },
            {"High Pressure Sodium","400-W HP Sodium",1,400,45000,24000,22,0.4,1.15,0.8696 },
            {"High Bay Fluorescent","2-lamp T8 HBF",2,32,2700,30000,83,0.6,1.2,1 },
            {"High Bay Fluorescent","2-lamp T5 HBF",2,54,4200,25000,85,0.65,1.1,1 },
            {"High Bay Fluorescent","3-lamp T8 HBF",3,32,2700,30000,83,0.6,1.2,1 },
            {"High Bay Fluorescent","3-lamp T5 HBF",3,54,4200,25000,85,0.65,1.1,1 },
            {"High Bay Fluorescent","4-lamp T8 HBF",4,32,2700,30000,83,0.6,1.2,1 },
            {"High Bay Fluorescent","4-lamp T5 HBF",4,54,4200,25000,85,0.65,1.1,1 },
            {"High Bay Fluorescent","4-lamp T5 HBF Retrofit",4,54,4200,25000,85,0.65,1.1,1 },
            {"High Bay Fluorescent","6-lamp T8 HBF",6,32,2700,30000,83,0.6,1.2,1 },
            {"High Bay Fluorescent","6-lamp T5 HBF",6,54,4200,25000,85,0.65,1.1,1 },
            {"High Bay Fluorescent","8-lamp T5 HBF",8,54,4200,25000,85,0.65,1.1,1 },
            {"Fluorescent XP Retrofit","1-lamp 28-W T8 XPS",1,28,2590,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","1-lamp 32-W T8 XPS",1,32,2850,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","2-lamp 28-W T8 XPS",2,28,2590,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","2-lamp 32-W T8 XPS",2,32,2850,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","3-lamp 28-W T8 XPS",3,28,2590,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","3-lamp 32-W T8 XPS",3,32,2850,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","4-lamp 28-W T8 XPS",4,28,2590,36000,85,0.53,0.78,1 },
            {"Fluorescent XP Retrofit","4-lamp 32-W T8 XPS",4,32,2850,36000,85,0.53,0.78,1 },
            {"Fluorescent 4 ft","2-lamp 34-W T12",2,34,2280,20000,62,0.51,0.87,1 },
            {"Fluorescent 4 ft","2-lamp 40-W T12",2,40,2910,20000,62,0.51,0.86,1 },
            {"Fluorescent 4 ft","2-lamp 32-W T8 Retrofit",2,32,2675,31000,83,0.53,0.88,1 },
            {"Fluorescent 4 ft","4-lamp 34-W T12",4,34,2280,20000,62,0.51,0.88,1 },
            {"Fluorescent 4 ft","4-lamp 40-W T12",4,40,2910,20000,62,0.51,0.95,1 },
            {"Fluorescent 4 ft","4-lamp 32-W T8",4,32,2675,31000,83,0.53,0.88,1 },
            {"Fluorescent 4 ft","4-lamp 32-W T8 Retrofit",4,32,2675,31000,83,0.53,0.88,1 },
            {"Fluorescent 4 ft","4-lamp 28-W T5 Retrofit",4,28,2900,20000,85,0.6,0.9,1 },
            {"Fluorescent 8 ft","2-lamp 60-W T12",2,60,5060,12000,60,0.51,1,1 },
            {"Fluorescent 8 ft","2-lamp 75-W T12",2,75,6110,12000,72,0.51,1,1 },
            {"Fluorescent 8 ft","2-lamp 95-W T12",2,95,6960,12000,62,0.51,1,1 },
            {"Fluorescent 8 ft","2-lamp 110-W T12",2,110,8280,12000,70,0.51,1,1 },
            {"Fluorescent 8 ft","2-lamp 120-W T12",2,120,8444,12000,62,0.51,1,1 },
            {"Fluorescent 8 ft","2-lamp 59-W T8",2,59,5500,15000,78,0.53,1,1 },
            {"Fluorescent 8 ft","2-lamp 86-W T8",2,86,7600,18000,78,0.53,1,1 },
            {"Induction High Bay","1-lamp 100-W IHB",1,100,8000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","1-lamp 120-W IHB",1,120,9600,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","1-lamp 150-W IHB",1,150,12000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","1-lamp 200-W IHB",1,200,16000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","2-lamp 100-W IHB",2,100,8000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","2-lamp 120-W IHB",2,120,9600,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","2-lamp 150-W IHB",2,150,12000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","2-lamp 200-W IHB",2,200,16000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","3-lamp 100-W IHB",3,100,8000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","3-lamp 120-W IHB",3,120,9600,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","3-lamp 150-W IHB",3,150,12000,100000,85,0.56,1.05,0.9 },
            {"Induction High Bay","3-lamp 200-W IHB",3,200,16000,100000,85,0.56,1.05,0.9 },
            {"Mercury Vapor","75-W MV",1,75,2700,18000,45,0.4,1.15,0.79 },
            {"Mercury Vapor","100-W MV",1,100,4000,24000,45,0.4,1.15,0.79 },
            {"Mercury Vapor","175-W MV",1,175,7700,24000,45,0.4,1.15,0.79 },
            {"Mercury Vapor","250-W MV",1,250,12500,24000,45,0.4,1.15,0.79 },
            {"Mercury Vapor","400-W MV",1,400,22000,24000,45,0.4,1.15,0.79 },
            {"High Bay LED","4-tube 80-W LED",4,20,2000,60000,70,0.75,1,1 },
            {"High Bay LED","6-tube 120-W LED",6,20,2000,60000,70,0.75,1,1 },
            {"High Bay LED","8-tube 160-W LED",8,20,2000,60000,70,0.75,1,1 },
            {"High Bay LED","10-tube 200-W LED",10,20,2000,60000,70,0.75,1,1 },
            {"High Bay LED","LED HID Replacement - 150W Equivalent",1,36,4800,50000,80,0.75,1,1 },
            {"High Bay LED","LED HID Replacement - 250W Equivalent",1,54,7200,50000,80,0.75,1,1 },
            {"High Bay LED","LED HID Replacement - 400W Equivalent",1,100,13300,50000,80,0.75,1,1 },
            {"High Bay LED","LED HID Replacement - 600W Equivalent",1,120,16000,50000,80,0.75,1,1 },
            {"LED Troffers","2L 4 foot LED ",2,33.8,1900,60000,75,0.75,1,1 },
            {"LED Troffers","3L 4 foot LED ",3,54,1900,60000,75,0.75,1,1 },
            {"LED Troffers","4L 4 foot LED ",4,72,1900,60000,80,0.75,1,1 },
            {"LED Troffers","2L 2 foot LED",2,17,950,60000,70,0.75,1,1 },
            {"LED Troffers","4L 2 Foot LED",4,34,950,60000,80,0.75,1,1 },
    };
}

#endif //MEASUR_TOOLS_SUITE_LIGHTING_DATA_DB_H
