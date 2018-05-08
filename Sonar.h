#include "Ranger.h"

class Sonar : public Ranger
{
public:
    Sonar();
    Sonar(const int &baud, const int &usbPort, const int &fieldOfView);
    void fieldOfViewInterface(int);
};
