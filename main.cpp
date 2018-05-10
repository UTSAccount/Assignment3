#include "main.h"
#include <thread>


void sensorSampling(Ranger &sensor, string thread, mutex &mtx)
{

    while(1)
    {
        unique_lock<mutex> lock(mtx);
        cout << thread << ": ";
        sensor.sampleData();
        cout << endl;
    }
}

void printDuck()
{
    cout << "duck" << endl;
}

int main()
{
    mutex mtx;
    // initialize starting time
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    cout << seed << endl;
    cout << seed * chrono::milliseconds::period::num / chrono::milliseconds::period::den << endl;
    // Default initialise sensor objects
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
    std::thread sonarDataCollect(sensorSampling,ref(sonar),"sonar sensor", ref(mtx));
    std::thread radarDataCollect(sensorSampling,ref(radar),"radar sensor", ref(mtx));


    // Wait for thread to finish
    sonarDataCollect.join();
    radarDataCollect.join();


}
