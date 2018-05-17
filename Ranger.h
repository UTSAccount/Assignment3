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
#include <condition_variable>
#define pi 3.1415
#define mean 0
#define standardDeviation 0.1

using namespace std;

/*!
 * \brief The Ranger class is the parent class of both Radar class and Sonar class
 * It is responsible to store sensor data, generate sensor data and generate user menu for setting different sensor parrameters.
 */

class Ranger
{
private:
    Ranger();
protected:
    string model_; /*!< Model number of sensor */
    int fieldOfView_; /*!< Store field of view */
    deque<double> data_; /*!< deque container store sensor distance data */
    deque<double> dataTime_; /*!< deque container stores time when a sensor data is sampled */
    int usbPort_; /*!< Stores usb port of sensor */
    int baud_; /*!< Stores baud rate of sensor */
    double max_; /*!< Stores the maximum distance the sensor can detect */
    double min_; /*!< Stores the minimum distance the sensor can detect */
    int dataRate_; /*!< Stores the rate of data sampling in millisecond */
    mutex mutex_; /*!< Mutex use to lock thread while the thread is accessing data */
    chrono::steady_clock::time_point initTime_; /*!< initTime is initialised when object is created to obtain data time when sampled */
    /*!
     * \brief Ranger class constructor
     * \param model
     * \param baud
     * \param usbPort
     * \param fieldOfView
     * \param max
     * \param min
     * \param dataRate
     */
    Ranger(const string &model, const int &baud, const int &usbPort, const int &fieldOfView,
            const double &max, const double &min, const int &dataRate);
public:
    /*!
     * \return model number of sensor
     */
    string getModel();
    /*!
     * \return Field of view value
     */
    int getFieldOfView();
    /*!
     * \brief setFieldOfView set field of view of sensor.
     * \param fieldOfView
     */
    void setFieldOfView(int fieldOfView);
    /*!
     * \return deque container of sensor data.
     */
    deque<double> getSensorData();
    /*!
     * \return deque container of sensor data time.
     */
    deque<double> getSensorDataTime();
    /*!
     * \return baud rate of sensor.
     */
    int getBaud();
    /*!
     * \brief setBaud sets the baud rate of sensor.
     * \param baud
     */
    void setBaud(int baud);
    /*!
     * \return usb port
     */
    int getUsbPort();
    /*!
     * \brief setUsbPort sets the usb port of sensor.
     * \param usbPort
     */
    void setUsbPort(int usbPort);
    /*!
     * \return Maximum distance of sensor.
     */
    double getMax();
    /*!
     * \return Minimum distance of sensor.
     */
    double getMin();
    /*!
     * \return data rate in millisecond
     */
    int getDataRate();
    /*!
     * \brief sampleData generate sensor data with r= 6 + (4 * sin(wt) + sigma
     * Where w = 2*pi*f (f=0.05Hz)
     * \param cv
     * \param dataGenerated
     */
    void sampleData(condition_variable &cv, bool &dataGenerated);
    //
    /*!
     * \brief containerManagement limit number of element in container of ranger class to input number
     * \param limitNumber
     */
    void containerManagement(int limitNumber);
    /*!
     * \brief fieldOfViewInterface is virtual function of Ranger class.
     */
    virtual void fieldOfViewInterface() = 0;
    /*!
     * \brief baudRateInterface generate a user menu for configuring the baud rate of sensor.
     */
    void baudRateInterface();
    /*!
     * \brief usbPortInterface generate a user menu for configuring the usb port of sensor.
     */
    void usbPortInterface();
    /*!
     * \brief getConfiguration generate a list of current sensor configurations
     */
    void getConfiguration();
    /*!
     * \brief configurationInterface generate a comprehenisve menu that is capable of select and set all the configurable parameters of a ranger sensor.
     */
    void configurationInterface();
};

#endif
