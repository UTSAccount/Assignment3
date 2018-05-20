#include"Ranger.h"


// Constructor taking values to set private members in ranger class, this constructor is for inherented class only
Ranger::Ranger(const string &model, const int &baud, const int &usbPort, const int &fieldOfView,
        const double &max, const double &min, const int &dataRate)
        : model_(model), baud_(baud), usbPort_(usbPort), fieldOfView_(fieldOfView), max_(max), min_(min), dataRate_(dataRate)
{
}

// Set field of view
void Ranger::setFieldOfView(int fieldOfView)
{
    fieldOfView_ = fieldOfView;
}

// Set usb port
void Ranger::setUsbPort(int usbPort)
{
    usbPort_ = usbPort;
}

// Set baud rate
void Ranger::setBaud(int baud)
{
    baud_ = baud;
}

// Obtain baud rate
int Ranger::getBaud()
{
   return baud_;
}

// Obtain field of view of ranger sensor
int Ranger::getFieldOfView()
{
    return fieldOfView_;
}

// Obtain usb port number
int Ranger::getUsbPort()
{
    return usbPort_;
}

// return sampled data
deque<double> Ranger::getSensorData()
{
    return data_;
}

// return time frame of sampled data
deque<double> Ranger::getSensorDataTime()
{
    return dataTime_;
}

// obtain maximum range of called sensor
double Ranger::getMax()
{
    return max_;
}

// obtain minimum range of called sensor
double Ranger::getMin()
{
    return min_;
}

// Obtain the rate of sampling data
int Ranger::getDataRate()
{
    return dataRate_;
}


void Ranger::baudRateInterface()
{
    // declare input variable for cin
    int itemSelect;
    // List of valid options for setting baud rate
    cout << "Select baud rate, enter 1 to 2: " << endl;
    cout << "1. 38400" << endl << "2. 115200" << endl;
    while(cin >> itemSelect){
        // if user selected a valid option, break out of loop
        if(itemSelect < 3 && itemSelect > 0)
            break;
        cout << "Invalid input, please enter again." << endl << endl;
    }
    // Set the baud rate base on valid option from user
    if(itemSelect == 1)
        setBaud(38400);
    else
        setBaud(115200);
    // Give feedback on which baud rate is been set
    cout << "Baud rate is set to "  << getBaud() << endl << endl;
}


void Ranger::usbPortInterface()
{
    // declare input variable for cin
    int itemSelect;
    // List of valid options for setting usb port
    cout << "Select USB port, enter 0 to 2: " << endl;
    while(cin >> itemSelect)
    {
        // if user selected a valid option, break out of loop
        if(itemSelect >= 0 && itemSelect < 3)
            break;
        cout << "Invalid input, please enter again." << endl;
    }
    // Set the baud rate base on valid option from user
    usbPort_ = itemSelect;
    // Give feedback on which baud rate is been set
    cout << "USB port is set to " << usbPort_ << endl << endl;
}

void Ranger::getConfiguration()
{
    // Obtain different sensor configuration and display at terminal as list
    cout << "Model: " << model_ << endl;
    cout << "Baud rate: " << baud_ << endl;
    cout << "Port: " << usbPort_ << endl;
    cout << "Field of view: " << fieldOfView_ << endl;
    cout << "Maximum distance: " << max_ << " meters" << endl;
    cout << "Minimum distance: " << min_ << " meters" << endl;
    cout << "Data rate: " << dataRate_ << " ms" << endl << endl;

}

void Ranger::configurationInterface()
{
    int menuSelect = 0;
        // Select from menu to configure corresponding setting
        while (menuSelect!=5){
            cout << model_ << " configuration menu" << endl;
            cout << "select item to modify, enter 1 to 8:" << endl;
            cout << "1. Baud rate" << endl
                 << "2. USB port" << endl
                 << "3. Field of view" << endl
                 << "4. Review setting" << endl
                 << "5. Exit Configuration" << endl << endl;
            // User input menu number from terminal
            cin >> menuSelect;
            if(menuSelect > 0 && menuSelect < 5){
                switch(menuSelect){
                // Navigate to baud rate selection menu
                case 1:
                    baudRateInterface();
                    break;
                // Navigate to USB port selection menu
                case 2:
                    usbPortInterface();
                    break;
                // Navigate to field of view selection menu
                case 3:
                    fieldOfViewInterface();
                    break;
                // Display current configuration of current sensor
                case 4:
                    getConfiguration();
                    break;
                }
            }

            // If user enters other than numerical input,
            // inform user the input is invalid and request to enter again
            else if(cin.fail()){
                cout << "Invalid input, please enter again" << endl << endl;
                cin.clear();
                cin.ignore(10000,'\n');
            }
        }
        cout << "Exiting sensor configuration" << endl << endl;
        return;
}

void Ranger::containerManagement(int limitNumber)
{
    // If any of the data container goes above the number limit
    // Erase the oldest data set from both container
    while (1)
    {
        unique_lock<mutex> lock(mutex_);
        if(data_.size() > limitNumber)
            data_.pop_back();
        if(dataTime_.size() > limitNumber)
            dataTime_.pop_back();
    }
}

void Ranger::sampleData(condition_variable &cv, bool &dataGenerated)
{
    while(1)
    {
        // Set thread to sleep at data sampling rate
        this_thread::sleep_for(chrono::milliseconds(dataRate_));
        unique_lock<mutex> lock(mutex_);
        // Display sampled sensor model number
        cout << model_<< ": " << endl;
        double tempData = 0;
        double omega = 2*pi*0.05;
        // Only store data when data is within sensor ranage
        while ((tempData < min_) || (tempData > max_))
        {
            // Generate a random seed
            unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
            default_random_engine engine(seed);
            // Use normal distrubution model to generate random number
            normal_distribution<double> gaussianNoise(mean,standardDeviation);
            double delta = gaussianNoise(engine);
            // Calculate final sensor data
            tempData = 6 + (4 * sin(omega*seed)) + delta;
        }
        // Obtain time which the sensor is generated
        chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
        double time = (t2-initTime_).count();
        // Store both data and time to sensor container
        data_.push_front(tempData);
        dataTime_.push_front(time);

        // Display sampled sensor data
        cout << "Data: ";
        for(auto i : data_)
        {
            cout << i << " ";
        }
        cout << endl;

        // Display time frame of sampled sensor data
        cout << "Time: ";
        for(auto i : dataTime_)
        {
            cout << i << " ";
        }
        cout << endl << endl;
        cv.notify_all();
        dataGenerated = true;
    }
}
