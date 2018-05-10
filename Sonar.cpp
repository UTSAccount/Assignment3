#include "Sonar.h"


// Default constructor of Sonar class
Sonar::Sonar():Ranger("SON-001", 38400, 0, 90, 6, 0.2, 3)
{

}

// Constructor of Sonar class
Sonar::Sonar(const int &baud, const int &usbPort, const int &fieldOfView):
      Ranger("SON-001", baud, usbPort, fieldOfView, 6, 0.2, 3)
{

}

// Sonar field of view interface notifying user field of view of sonar is unchangable
void Sonar::fieldOfViewInterface()
{
    cout << "Current sensor cannot change field of view setting" << endl << endl;
    return;
}
