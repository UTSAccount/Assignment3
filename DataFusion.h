#ifndef DATAFUSION_H
#define DATAFUSION_H

#include "Ranger.h"
#include <iostream>
using namespace std;

class DataFusion{
private:
    int fusionMethod_;
    int processMethod_;
    int fusionRate_;
    chrono::steady_clock::time_point initTime_;
public:
    DataFusion(const int &fusionMethod, const int &processMethod, const int &fusionRate);
    DataFusion();
    // Obtain fusion method
    int getFusionMethod();
    // Get processing method
    int getProcessMethod();
    // Get the rate of fusion process
    int getFusionRate();
    // The fuse Sensor data function extract data and time value from rangers sensors
    // The data is then extrapolated to obtain current data at current time
    // The extrapolated data is fused base on fusion method and return to the function call
    double fuseSensorData(vector<Ranger *> &rangers);
    // Data fusion user interface for change fusion method
    void dataFusionInterface();
    // Data fusion user interface for change data processing method
    void processMethodInterface();

};

#endif
