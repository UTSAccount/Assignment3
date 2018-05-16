#include "main.h"
bool dataGenerated = false;


void sensorSampling(Ranger &sensor, condition_variable &cv)
{
    while(1)
    {
        // Sample sensor data
        sensor.sampleData();
        // Notify other thread that new data is sampled
        cv.notify_all();
        // Additional variable to notify new data is sampled
        dataGenerated = true;
    }
}

void dataFusion(DataFusion &fusion, vector<Ranger*> &rangers, mutex &mtx, condition_variable &cv)
{
    while(1){
        unique_lock<mutex> lck(mtx);
        // Base on processing method, choose either fuse at 3Hz or at every new data
        if(fusion.getProcessMethod()==1)
        {
            // Unlock lock to prevent lock while thread is sleeping
            lck.unlock();
            this_thread::sleep_for(chrono::milliseconds(fusion.getFusionRate()));
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
        double data = fusion.fuseSensorData(rangers);
        cout << "fusion output: " << data << endl << endl;
        dataGenerated = false;
    }
}

// container management must call a ranger function to modify sensor data directly
void containerManagement(vector<Ranger*> &rangers)
{
    while(1)
    {
        for(auto &i : rangers)
        {
            i->containerManagement(MAX_NUM_DATA);
        }
    }
}

int main()
{
    // Default initialise sensor and data fusion objects
    mutex mtx;
    condition_variable cv;
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
    fusion.processMethodInterface();

    // Initialize thread for sensor data sampling and data fusion
    thread sonarSamplingThread(sensorSampling,ref(sonar),ref(cv));
    thread radarSamplingThread(sensorSampling,ref(radar),ref(cv));
    thread dataFusionThread(dataFusion,ref(fusion),ref(rangers),ref(mtx),ref(cv));
    thread dataManagementThread(containerManagement, ref(rangers));

    // Wait for thread to finish
    dataFusionThread.join();
    sonarSamplingThread.join();
    radarSamplingThread.join();
    dataManagementThread.join();

}
