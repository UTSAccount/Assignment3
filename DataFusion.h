#ifndef DATAFUSION_H
#define DATAFUSION_H

#include "Ranger.h"
#include <iostream>
using namespace std;

//! Data Fusion Class.
/*!
 * \brief The DataFusion class is responsible to fuse sensor data.
 *
 * Data fusion will have different fusing methods and threading process method.
 */

class DataFusion{
private:
    int fusionMethod_;
    int processMethod_;
    int fusionRate_;
    chrono::steady_clock::time_point initTime_;
public:

    //! DataFusion constructor
    /*!
     * \brief DataFusion constructor take values to set fusion method, process method and fusion rate.
     * \param fusionMethod
     * \param processMethod
     * \param fusionRate
     */
    DataFusion(const int &fusionMethod, const int &processMethod, const int &fusionRate);

    //! DataFusion default constructor
    /*!
     * \brief DataFusion default initialize fusion method to maximum,
     *  process method to process every 5Hz,
     * fusion rate to 5Hz.
     */
    DataFusion();

    /*!
    * \brief getFusionMethod obtains the current fusion method
    * \return fusion method index:
    *
    * \return 1 = Maximum
    *
    * \return 2 = Minimum
    *
    * \return 3 = Average.
    */
    int getFusionMethod();
    /*!
     * \brief getProcessMethod obtains the process method index
     * \return process method index:
     *
     * \return 1 = Process data every 5Hz.
     *
     * \return 2 = Process data when new data is sampled.
     */
    int getProcessMethod();
    /*!
     * \brief getFusionRate
     * \return Fusion rate in milliseconds
     */
    int getFusionRate();
    /*!
     * \brief fuseSensorData function extract data and time value from rangers sensors.
     * The data is then extrapolated to obtain current data at current time.
     * The extrapolated data is fused base on fusion method and return to the function call
     * \param rangers
     * \return Fused data
     */
    double fuseSensorData(vector<Ranger *> &rangers);
    /*!
     * \brief dataFusionInterface is the user interface for change fusion method.
     * The function generate a user menu to set data fusion method.
     */
    void dataFusionInterface();
    /*!
     * \brief processMethodInterface generate a user menu to set data fusion method.
     */
    void processMethodInterface();

};

#endif
