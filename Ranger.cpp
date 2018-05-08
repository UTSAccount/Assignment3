#include"Ranger.h"

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

void Ranger::setBaud(int baud)
{
    baud_ = baud;
}

int Ranger::getBaud()
{
   return baud_;
}

// Obtain field of view of ranger sensor
int Ranger::getFieldOfView()
{
    return fieldOfView_;
}

//
int Ranger::getUsbPort()
{
    return usbPort_;
}

vector<double> Ranger::getData()
{
    return data_;
}

double Ranger::getMax()
{
    return max_;
}

double Ranger::getMin()
{
    return min_;
}

int Ranger::getDataRate()
{
    return dataRate_;
}

void Ranger::baudRateInterface(double itemSelect)
{
    cout << "Select baud rate, enter 1 to 2: " << endl;
    cout << "1. 38400" << endl << "2. 115200" << endl;
    while(cin >> itemSelect){
        if(itemSelect < 3 && itemSelect > 0)
            break;
        cout << "Invalid input, please enter again." << endl << endl;
    }
    if(itemSelect == 1)
        setBaud(38400);
    else
        setBaud(115200);
    cout << "Baud rate is set to "  << getBaud() << endl << endl;
}


void Ranger::usbPortInterface(double itemSelect)
{
    cout << "Select USB port, enter 0 to 2: " << endl;
    while(cin >> itemSelect)
    {
        if(itemSelect >= 0 && itemSelect < 3)
            break;
        cout << "Invalid input, please enter again." << endl;
    }
    usbPort_ = itemSelect;
    cout << "USB port is set to " << usbPort_ << endl << endl;
}

void Ranger::getConfiguration()
{
    cout << "Model: " << model_ << endl;
    cout << "Baud rate: " << baud_ << endl;
    cout << "Port: " << usbPort_ << endl;
    cout << "Field of view: " << fieldOfView_ << endl;
    cout << "Maximum distance: " << max_ << " meters" << endl;
    cout << "Minimum distance: " << min_ << " meters" << endl;
    cout << "Data rate: " << dataRate_ << endl;

}

void Ranger::configurationInterface()
{
    int menuSelect;
    int itemSelect;
        // Select from menu to configure
        while (menuSelect!=5){
            cout << "select item to modify, enter 1 to 8:" << endl;
            cout << "1. Baud rate" << endl
                 << "2. USB port" << endl
                 << "3. Field of view" << endl
                 << "4. Review setting" << endl
                 << "5. Exit Configuration" << endl << endl;
            cin >> menuSelect;
            if(menuSelect > 0 && menuSelect < 5){
                switch(menuSelect){

                // Sensor configuration interfacing
                case 1:
                    baudRateInterface(itemSelect);
                    break;

                // Set USB port
                case 2:
                    usbPortInterface(itemSelect);
                    break;

                case 3:
                    // Set field of view
                    fieldOfViewInterface(itemSelect);
                    break;

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

void Ranger::sampleData()
{
    double tempData = 0;
    double omega = 2*pi*0.05;
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine engine(seed);
    normal_distribution<double> gaussianNoise(mean,standardDeviation);
    double delta = gaussianNoise(engine);
    tempData = 6 + (4 * sin(omega)) + delta;
    data_.push_back(tempData);
}
