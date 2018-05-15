#include "DataFusion.h"

DataFusion::DataFusion(const int &fusionMethod): fusionMethod_(fusionMethod){

}

DataFusion::DataFusion()
{
    fusionMethod_ = 1;
}

void DataFusion::dataFusionInterface()
{
    int itemSelect;
    cout << "Select data fusion method, enter 1 to 3: " << endl;
    cout << "1. Maximum" << endl
         << "2. Minimum" << endl
         << "3. Average" << endl;
    while(cin >> itemSelect){
        if(itemSelect > 0 && itemSelect < 4)
            break;
        cout << "Invalid input, please enter again." << endl;
    }

    // Set and display configured fusion method
    cout << "Fusion method is set to " ;
    if(itemSelect == 1)
    {
        fusionMethod_ = 1;
        cout << "Maximum" << endl;
    }

    else if (itemSelect == 2)
    {
        fusionMethod_ = 2;
        cout << "Minimum" << endl;
    }
    else
    {
        fusionMethod_ = 3;
        cout << "Average" << endl;
    }
    return;
}

double DataFusion::fuseSensorData(vector<Ranger*> &rangers, chrono::steady_clock::time_point &timeInit)
{
    // Create variables to temperary hold data to be compared
    vector<double> tempData;
    double fusedData = 0;
    double maxValue = 0;
    double minValue = 999;
    double averageValue = 0;
    // Cycle through each sensor to obtain first two sensor data
    // Extrapolate using two set of data to obtain current data
    cout << "Interpolating: " << endl;
    for(auto &i : rangers)
    {
        cout << "Interpolating data :";
        double v1 = i->getSensorData()[0];
        cout << v1 << " ";
        double v2 = i->getSensorData()[1];
        cout << v2 << " ";
        double t1 = i->getSensorDataTime()[0];
        cout << t1 << " ";
        double t2 = i->getSensorDataTime()[1];
        cout << t2 << " ";
        double t3 = (chrono::steady_clock::now()-timeInit).count();
        cout << "current time: " << t3 << " ";
        // Linearly interpolate current data
        double data = v1-((v1-v2)/(t1-t2))*(t1-t3);
        tempData.push_back(data);
        cout << "Interpolated result: "<< data << endl;
//        cout << endl << endl;
    }

     switch(fusionMethod_)
     {

     // Fuse data base on its maximum sensor reading
     case 1:
         for(auto dataValue : tempData)
         {
            if(dataValue > maxValue)
               maxValue = dataValue;
         }
         return maxValue;

     // Fuse data base on minimum sensor reading
     case 2:
         for(auto dataValue : tempData)
         {
            if(dataValue < minValue)
               minValue = dataValue;
         }
         return minValue;

     // Fuse data base on average sensor reading
     case 3:
         for(auto dataValue : tempData)
         {
            if(dataValue > maxValue)
               averageValue += dataValue;
         }
         averageValue /= tempData.size();
         return averageValue;
     }

}
