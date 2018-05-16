#ifndef RANGER_H
#define RANGER_H

#include <deque>
#include <random>
#include <math.h>
#include <chrono>
#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <thread>
#define pi 3.1415
#define mean 0
#define standardDeviation 0.1

using namespace std;

class Ranger
{
private:
    Ranger();
protected:
    string model_;
    int fieldOfView_;
    deque<double> data_;
    deque<double> dataTime_;
    int usbPort_;
    int baud_;
    double max_;
    double min_;
    int dataRate_;
    // mutex use for locking data when process data using threading
    mutex mutex_;
    // initTime is initialised when object is created to obtain data time when sampled
    chrono::steady_clock::time_point initTime_;
    Ranger(const string &model, const int &baud, const int &usbPort, const int &fieldOfView,
            const double &max, const double &min, const int &dataRate);
public:
    // Obtain model number of sensor
    string getModel(void);
    // Obtain field of view of sensor
    int getFieldOfView();
    // Set field of view
    void setFieldOfView(int);
    // Obtain stored sensor data
    deque<double> getSensorData();
    // Get time frame of gathered sensor data
    deque<double> getSensorDataTime();
    // Obtain baud rate
    int getBaud();
    // Set baud rate
    void setBaud(int);
    // Obtain usb port
    int getUsbPort();
    // Set sensor usb port
    void setUsbPort(int);
    // Get maximum distance value of the sensor
    double getMax();
    // Get minimum distance value of the sensor
    double getMin();
    // Get rate of sampling a sensor data
    int getDataRate();
    // Generate sensor data with r= 6 + (4 * sin(wt) + sigma
    // Where w = 2*pi*f (f=0.05Hz)
    void sampleData();
    // Limit number of element in container of ranger class to input number
    void containerManagement(int);
    // Userinterface for sensor configuration
    virtual void fieldOfViewInterface() = 0;
    // User menu for baud rate configuration
    void baudRateInterface();
    // User menu for usb port configuration
    void usbPortInterface();
    // Generate a list of current configuration on current data in cmd
    void getConfiguration();
    // User menu consist of field of view, baud rate and usb port configuration interface
    void configurationInterface();
};

#endif
