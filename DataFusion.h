#ifndef DATAFUSION_H
#define DATAFUSION_H

#include "Ranger.h"

class DataFusion{
private:
    int fusionMethod_;

public:
    DataFusion(const int &fusionMethod);
    DataFusion();
    vector<double> fuseSensorData();
};

#endif
