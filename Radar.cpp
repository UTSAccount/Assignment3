#include "Radar.h"
Radar::Radar():Ranger(RADAR_MODEL_NUM, RADAR_BAUD_RATE, RADAR_USB_PORT, RADAR_FIELD_OF_VIEW
                      , RADAR_MAX_DISTANCE, RADAR_MIN_DISTANCE, RADAR_DATA_RATE)
{
    initTime_ = chrono::steady_clock::now();
}

Radar::Radar(const int &baud, const int &usbPort, const int &fieldOfView):
      Ranger(RADAR_MODEL_NUM, baud, usbPort, fieldOfView, RADAR_MAX_DISTANCE, RADAR_MIN_DISTANCE, RADAR_DATA_RATE)
{
    initTime_ = chrono::steady_clock::now();
}

void Radar::fieldOfViewInterface()
{
    int itemSelect;
    // User selects a valid option by inputing 1 or 2
    cout << "Select field of view, enter 1 to 2: " << endl;
    cout << "1. 20 degree" << endl
         << "2. 40 degree" << endl;
    while(cin >> itemSelect){
        // If the input is valid break out of the while loop, otherwise give an warning to user and re-enter input again.
        if(itemSelect > 0 && itemSelect < 3)
            break;
        // Give error message if input is invalid
        cout << "Invalid input, please enter again." << endl;
    }
    // Set field of view base on valid user input.
    if(itemSelect == 1)
        fieldOfView_ = 20;
    else
        fieldOfView_ = 40;
    cout << "field of view is set to " << fieldOfView_ << endl << endl;
}
