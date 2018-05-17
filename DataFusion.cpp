#include "DataFusion.h"

DataFusion::DataFusion(const int &fusionMethod, const int &processMethod, const int &fusionRate):
    fusionMethod_(fusionMethod), processMethod_(fusionMethod), fusionRate_(fusionRate)
{
    //Initialize current time
    initTime_ = chrono::steady_clock::now();
}

DataFusion::DataFusion()
{
    fusionMethod_ = 1;
    processMethod_ = 1;
    fusionRate_ = 200;
    initTime_ = chrono::steady_clock::now();
}

// Getter function to obtain fusion method
int DataFusion::getFusionMethod()
{
    return fusionMethod_;
}

// Getter function to obtain process method
int DataFusion::getProcessMethod()
{
    return processMethod_;
}

// Getter function to obtain fusion rate in milliseconds
int DataFusion::getFusionRate()
{
    return fusionRate_;
}

void DataFusion::dataFusionInterface()
{
    int itemSelect;
    // List of valid options for setting data fusion method
    cout << "Select data fusion method, enter 1 to 3: " << endl;
    cout << "1. Maximum" << endl
         << "2. Minimum" << endl
         << "3. Average" << endl;
    while(cin >> itemSelect){
        // if user selected a valid option, break out of loop
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
    cout << endl;
    return;
}

void DataFusion::processMethodInterface()
{
    int itemSelect;
    // List of valid options for setting data processing method
    cout << "Select data fusion method, enter 1 to 2: " << endl;
    cout << "1. Fuse data every 5Hz" << endl
         << "2. Fuse data when new sensor data arrive" << endl;
    while(cin >> itemSelect){
        if(itemSelect > 0 && itemSelect < 3)
            break;
        cout << "Invalid input, please enter again." << endl;
    }

    // Set and display configured data processing method
    cout << "Process method is set to " ;
    if(itemSelect == 1)
    {
        processMethod_ = 1;
        cout << "update every 5Hz" << endl;
    }
    else if (itemSelect == 2)
    {
        processMethod_ = 2;
        cout << "updata every new sensor data" << endl;
    }
    cout << endl;
    return;
}

void DataFusion::fuseSensorData(vector<Ranger*> &rangers, condition_variable &cv, bool &dataGenerated)
{

    while(1)
    {
        unique_lock<mutex> lck(mtx_);
        // Base on processing method, choose either fuse at 3Hz or at every new data
        if(processMethod_==1)
        {
            // Unlock lock to prevent lock while thread is sleeping
            lck.unlock();
            this_thread::sleep_for(chrono::milliseconds(fusionRate_));
            lck.lock();
        }
        else
        {
            // Wait for other thread to notify there are new data been sampled
            while(!dataGenerated)
            {
                cv.wait(lck);
            }
        }
        // Create variables to temperary hold data to be compared
        vector<double> tempData;
        double maxValue = 0;
        double minValue = 999;
        double averageValue = 0;
        double data = 0;
        // Cycle through each sensor to obtain first two sensor data
        // Extrapolate using two set of data to obtain current data
        cout << "Interpolating: " << endl;
        for(auto &i : rangers)
        {
            cout << "Interpolating data :";
            // Extract newest two sensor data for interpolation
            double v1 = i->getSensorData()[0];
            cout << v1 << " ";
            double v2 = i->getSensorData()[1];
            cout << v2 << " ";
            double t1 = i->getSensorDataTime()[0];
            cout << t1 << " ";
            double t2 = i->getSensorDataTime()[1];
            cout << t2 << " ";
            // Obtain current time since fusion object is initialised
            double t3 = (chrono::steady_clock::now()-initTime_).count();
            cout << "current time: " << t3 << " ";
            // Linearly interpolate current data
            double data = ((v2-v1)/(t2-t1))*(t3-t2)+v2;
            // If linearly interpolated data exceed the maximum or minimum range of sensor configuration
            // Assign interpolated data as maximum/minimum sensor distance
            if(data < i->getMin())
                data = i->getMin();
            if(data > i->getMax())
                data = i->getMax();
            // Store extrapolated data in a temporary for data fusion
            tempData.push_back(data);
            cout << "Interpolated result: "<< data << endl;
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
             data = maxValue;
             break;

         // Fuse data base on minimum sensor reading
         case 2:
             for(auto dataValue : tempData)
             {
                if(dataValue < minValue)
                   minValue = dataValue;
             }
             data = minValue;
             break;

         // Fuse data base on average sensor reading
         case 3:
             for(auto dataValue : tempData)
             {
                if(dataValue > maxValue)
                   averageValue += dataValue;
             }
             averageValue /= tempData.size();
             data = averageValue;
             break;
         }
         cout << "fusion output: " << data << endl << endl;
         dataGenerated = false;
    }
}
