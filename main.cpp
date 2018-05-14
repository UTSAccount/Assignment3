#include "main.h"



void sensorSampling(Ranger &radar, mutex &mtx)
{

    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(int((1/radar.getDataRate())*1000)));
        unique_lock<mutex> lck(mtx);
        radar.sampleData();
    }
}

void dataFusion(DataFusion &fusion)
{

}


int main()
{
    mutex mtx;

    // Default initialise sensor and data fusion objects
    Radar radar;
    Sonar sonar;
    DataFusion fusion;
    // Display initialized sensor configuration
    radar.getConfiguration();
    sonar.getConfiguration();

    // Configuration user menu interface for both sensor and fusion method
    radar.configurationInterface();
    sonar.configurationInterface();
    fusion.dataFusionInterface();

    // Initialize thread for sensor data sampling and data fusion
    thread sonarSamplingThread(sensorSampling,ref(sonar),ref(mtx));
    thread radarSamplingThread(sensorSampling,ref(radar),ref(mtx));


    // Wait for thread to finish
    sonarSamplingThread.join();
    radarSamplingThread.join();


}
