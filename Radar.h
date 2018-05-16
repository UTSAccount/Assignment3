#ifndef RADAR_H
#define RADAR_H

#include "Ranger.h"
// Macro for radar sensor initialization
#define RADAR_MODEL_NUM "RAD-001"
#define RADAR_BAUD_RATE 38400
#define RADAR_USB_PORT 0
#define RADAR_FIELD_OF_VIEW 20
#define RADAR_MAX_DISTANCE 10
#define RADAR_MIN_DISTANCE 0.2
#define RADAR_DATA_RATE 100

class Radar : public Ranger
{
public:
    // Default constructor of Radar class
    Radar();
    // Constructor of Radar class
    Radar(const int &baud, const int &usbPort, const int &fieldOfView);
    void fieldOfViewInterface();
};


#endif
