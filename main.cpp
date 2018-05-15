#include "main.h"
bool dataGenerated = false;


void sensorSampling(Ranger &sensor, chrono::steady_clock::time_point& timeInit, mutex &mtx, condition_variable &cv)
{
    while(1)
    {
        // Set thread to sleep at data sampling rate
        this_thread::sleep_for(chrono::milliseconds(int((1/sensor.getDataRate())*1000)));
        unique_lock<mutex> lck(mtx);
        sensor.sampleData(timeInit);
        cv.notify_all();
        dataGenerated = true;
        // Display sampled sensor data
        cout << "Data: ";
        for(auto i : sensor.getSensorData())
        {
            cout << i << " ";
        }
        cout << endl;

        // Display time frame of sampled sensor data
        cout << "Time: ";
        for(auto i : sensor.getSensorDataTime())
        {
            cout << i << " ";
        }
        cout << endl << endl;
    }
}

void dataFusion(DataFusion &fusion, vector<Ranger*> &rangers, chrono::steady_clock::time_point& timeInit, mutex &mtx, condition_variable &cv)
{
    while(1){
        unique_lock<mutex> lck(mtx);
        if(fusion.getProcessMethod()==1)
        {
            lck.unlock();
            this_thread::sleep_for(chrono::milliseconds(fusionRate));
            lck.lock();
        }
        else
        {
            while(!dataGenerated)
            {
                cv.wait(lck);
            }
        }
        double data = fusion.fuseSensorData(rangers, timeInit);
        cout << "fusion output: " << data << endl << endl;
        dataGenerated = false;
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
            i->containerManagement(5);
        }
    }
}

int main()
{
    // Default initialise sensor and data fusion objects
    mutex mtx;
    condition_variable cv;
    chrono::steady_clock::time_point timeInit = chrono::steady_clock::now();
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
    thread sonarSamplingThread(sensorSampling,ref(sonar),ref(timeInit),ref(mtx),ref(cv));
    thread radarSamplingThread(sensorSampling,ref(radar),ref(timeInit),ref(mtx),ref(cv));
    thread dataFusionThread(dataFusion,ref(fusion),ref(rangers),ref(timeInit),ref(mtx),ref(cv));
    thread dataManagementThread(containerManagement, ref(rangers), ref(mtx));

    // Wait for thread to finish
    dataFusionThread.join();
    sonarSamplingThread.join();
    radarSamplingThread.join();
    dataManagementThread.join();

}
