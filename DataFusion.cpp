#include "DataFusion.h"

DataFusion::DataFusion(const int &fusionMethod): fusionMethod_(fusionMethod){

}

DataFusion::DataFusion()
{
    fusionMethod_ = 1;
}

void DataFusion::dataFusionInterface()
{
    int itemSelect;
    cout << "Select data fusion method, enter 1 to 3: " << endl;
    cout << "1. Maximum" << endl
         << "2. Minimum" << endl
         << "3. Average" << endl;
    while(cin >> itemSelect){
        if(itemSelect > 0 && itemSelect < 4)
            break;
        cout << "Invalid input, please enter again." << endl;
    }

    // Set and display configured fusion method
    cout << "Fusion method is set to " ;
    if(itemSelect == 1)
    {
        fusionMethod_ = 1;
        cout << "Maximum" << endl;
    }

    else if (itemSelect == 2)
    {
        fusionMethod_ = 2;
        cout << "Minimum" << endl;
    }

    else
    {
        fusionMethod_ = 3;
        cout << "Average" << endl;
    }
    return;
}
