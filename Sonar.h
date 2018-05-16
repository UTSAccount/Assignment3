#ifndef SONAR_H
#define SONAR_H

#include "Ranger.h"

// Macro for constructors
#define SONAR_MODEL_NUM "SON-001"
#define SONAR_BAUD_RATE 38400
#define SONAR_USB_PORT 0
#define SONAR_FIELD_OF_VIEW 90
#define SONAR_MAX_DISTANCE 6
#define SONAR_MIN_DISTANCE 0.2
#define SONAR_DATA_RATE 333

class Sonar : public Ranger
{
public:
    // Default constructor
    Sonar();
    // Constructor
    Sonar(const int &baud, const int &usbPort, const int &fieldOfView);
    // User interface for setting field of view of sonar sensor
    void fieldOfViewInterface();
};

#endif
