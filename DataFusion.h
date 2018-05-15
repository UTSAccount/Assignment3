#ifndef DATAFUSION_H
#define DATAFUSION_H

#include "Ranger.h"
#include <iostream>
using namespace std;

class DataFusion{
private:
    int fusionMethod_;
    int processMethod_;
public:
    DataFusion(const int &fusionMethod);
    DataFusion();

    // Obtain fusion method
    int getFusionMethod();

    // Get processing method
    int getProcessMethod();

    // The fuse Sensor data function extract data and time value from rangers sensors
    // The data is then extrapolated to obtain current data at current time
    // The extrapolated data is fused base on fusion method and return to the function call
    double fuseSensorData(vector<Ranger *> &rangers, chrono::_V2::steady_clock::time_point &timeInit);

    // Data fusion user interface for change fusion method
    void dataFusionInterface();

    // Data fusion user interface for change data processing method
    void processMethodInterface();
};

#endif
