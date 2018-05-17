#include "main.h"

int main()
{
    // Default initialise sensor and data fusion objects
    mutex mtx;
    condition_variable cv;
    bool dataGenerated = false;
    Radar radar;
    Sonar sonar;
    Ranger *radarPointer = &radar;
    Ranger *sonarPointer = &sonar;
    vector<Ranger* > rangers = {radarPointer, sonarPointer};
    DataFusion fusion;
    DataFusion *fusionPointer = &fusion;

    // Display initialized sensor configuration
    radar.getConfiguration();
    sonar.getConfiguration();

    // Configuration user menu interface for both sensor and fusion method
    radar.configurationInterface();
    sonar.configurationInterface();
    fusion.dataFusionInterface();
    fusion.processMethodInterface();

    // Initialize thread for sensor data sampling and data fusion
    thread sonarSamplingThread(&Ranger::sampleData,sonarPointer,ref(cv),ref(dataGenerated));
    thread radarSamplingThread(&Ranger::sampleData,radarPointer,ref(cv),ref(dataGenerated));
    thread dataFusionThread(&DataFusion::fuseSensorData,fusionPointer,ref(rangers),ref(cv),ref(dataGenerated));
    thread radarManagementThread(&Ranger::containerManagement,radarPointer, MAX_NUM_DATA);
    thread sonarManagementThread(&Ranger::containerManagement,sonarPointer, MAX_NUM_DATA);

    // Wait for thread to finish
    dataFusionThread.join();
    sonarSamplingThread.join();
    radarSamplingThread.join();
    radarManagementThread.join();
    sonarManagementThread.join();
}
