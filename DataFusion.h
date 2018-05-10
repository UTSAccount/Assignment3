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
    vector<double> fuseSensorData();
    // Data fusion user interface for change fusion method
    void dataFusionInterface();
};

#endif
