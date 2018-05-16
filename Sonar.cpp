#include "Sonar.h"


// Default constructor of Sonar class
Sonar::Sonar():Ranger(SONAR_MODEL_NUM, SONAR_BAUD_RATE, SONAR_USB_PORT, SONAR_FIELD_OF_VIEW
                      , SONAR_MAX_DISTANCE, SONAR_MIN_DISTANCE, SONAR_DATA_RATE)
{
    initTime_ = chrono::steady_clock::now();
}

// Constructor of Sonar class
Sonar::Sonar(const int &baud, const int &usbPort, const int &fieldOfView):
      Ranger(SONAR_MODEL_NUM, baud, usbPort, fieldOfView, SONAR_MAX_DISTANCE, SONAR_MIN_DISTANCE, SONAR_DATA_RATE)
{
    initTime_ = chrono::steady_clock::now();
}

// Sonar field of view interface notifying user field of view of sonar is unchangable
void Sonar::fieldOfViewInterface()
{
    cout << "Current sensor cannot change field of view setting" << endl << endl;
    return;
}
