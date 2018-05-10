#include "Radar.h"
Radar::Radar():Ranger("RAD-001", 38400, 0, 20, 10, 0.2, 10)
{

}

Radar::Radar(const int &baud, const int &usbPort, const int &fieldOfView):
      Ranger("RAD-001", baud, usbPort, fieldOfView, 10, 0.2, 10)
{

}

void Radar::fieldOfViewInterface()
{
    int itemSelect;
    cout << "Select field of view, enter 1 to 2: " << endl;
    cout << "1. 20 degree" << endl
         << "2. 40 degree" << endl;
    while(cin >> itemSelect){
        if(itemSelect > 0 && itemSelect < 3)
            break;
        cout << "Invalid input, please enter again." << endl;
    }
    if(itemSelect == 1)
        fieldOfView_ = 20;
    else
        fieldOfView_ = 40;
    cout << "field of view is set to " << fieldOfView_ << endl << endl;
}
