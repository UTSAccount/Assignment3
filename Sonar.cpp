#include "Sonar.h"

Sonar::Sonar():Ranger("SON-001", 38400, 0, 90, 6, 0.2, 3)
{

}

Sonar::Sonar(const int &baud, const int &usbPort, const int &fieldOfView):
      Ranger("SON-001", baud, usbPort, fieldOfView, 6, 0.2, 3)
{

}

void Sonar::fieldOfViewInterface(int)
{
    cout << "Current sensor cannot change field of view setting" << endl << endl;
    return;
}
