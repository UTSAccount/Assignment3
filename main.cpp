#include "main.h"



void sensorSampling(Ranger &radar, chrono::steady_clock::time_point& timeInit, mutex &mtx)
{

    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(int((1/radar.getDataRate())*1000)));
        unique_lock<mutex> lck(mtx);
        radar.sampleData(timeInit);
    }
}

void dataFusion(DataFusion &fusion, vector<Ranger*> &rangers, mutex &mtx)
{
    while(1){
        this_thread::sleep_for(chrono::milliseconds(fusionRate));
        unique_lock<mutex> lck(mtx);
        fusion.fuseSensorData(rangers);
        cout << "fusion output" << endl;
    }
}

// container management must call a ranger function to modify sensor data directly
void containerManagement(vector<Ranger*> &rangers, mutex &mtx)
{
    while(1)
    {
        for(auto &i : rangers)
        {
            unique_lock<mutex> lck(mtx);
            i->containerManagement(10);
        }
    }
}

int main()
{
    mutex mtx;
    chrono::steady_clock::time_point timeInit = chrono::steady_clock::now();
    // Default initialise sensor and data fusion objects
    Radar radar;
    Sonar sonar;
    Ranger *radarPointer = &radar;
    Ranger *sonarPointer = &sonar;
    vector<Ranger* > rangers = {radarPointer, sonarPointer};
    DataFusion fusion;
    // Display initialized sensor configuration
    radar.getConfiguration();
    sonar.getConfiguration();

    // Configuration user menu interface for both sensor and fusion method
    radar.configurationInterface();
    sonar.configurationInterface();
    fusion.dataFusionInterface();

    // Initialize thread for sensor data sampling and data fusion
    thread sonarSamplingThread(sensorSampling,ref(sonar),ref(timeInit),ref(mtx));
    thread radarSamplingThread(sensorSampling,ref(radar),ref(timeInit),ref(mtx));
    thread dataFusionThread(dataFusion,ref(fusion),ref(rangers),ref(mtx));
    thread dataManagementThread(containerManagement, ref(rangers), ref(mtx));


    // Wait for thread to finish
    dataFusionThread.join();
    sonarSamplingThread.join();
    radarSamplingThread.join();
    dataManagementThread.join();

}
