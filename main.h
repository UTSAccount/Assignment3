#ifndef MAIN_H
#define MAIN_H


#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Radar.h"
#include "Ranger.h"
#include "Sonar.h"
#include "DataFusion.h"

using namespace std;

void sampleSensor(Ranger&);

#endif
