#ifndef DATAFUSION_H
#define DATAFUSION_H

#include "Ranger.h"
#include <iostream>
using namespace std;

class DataFusion{
private:
    int fusionMethod_;

public:
    DataFusion(const int &fusionMethod);
    DataFusion();
    double fuseSensorData(vector<Ranger *> &rangers, chrono::_V2::steady_clock::time_point &timeInit);
    // Data fusion user interface for change fusion method
    void dataFusionInterface();
};

#endif
