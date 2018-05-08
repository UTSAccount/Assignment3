#ifndef RADAR_H
#define RADAR_H

#include "Ranger.h"

class Radar : public Ranger
{
public:
    Radar();
    Radar(const int &baud, const int &usbPort, const int &fieldOfView);
    void fieldOfViewInterface(int);
};


#endif
