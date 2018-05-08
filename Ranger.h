#ifndef RANGER_H
#define RANGER_H

#include <vector>
#include <random>
#include <math.h>
#include <chrono>
#include <iostream>
#include <string>

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
    vector<double> data_;
    int usbPort_;
    int baud_;
    double max_;
    double min_;
    int dataRate_;
    Ranger(const string &model, const int &baud, const int &usbPort, const int &fieldOfView,
            const double &max, const double &min, const int &dataRate);
public:
    string getModel(void);
    int getFieldOfView();
    void setFieldOfView(int);
    vector<double> getSensorData();
    int getBaud();
    void setBaud(int);
    int getUsbPort();
    void setUsbPort(int);
    double getMax();
    double getMin();
    int getDataRate();
    vector<double> getData();
    void sampleData(void);

    // Userinterface for sensor configuration
    virtual void fieldOfViewInterface(int) = 0;
    void baudRateInterface(double);
    void usbPortInterface(double);
    void getConfiguration();
    void configurationInterface();
};

#endif
