//
// Created by Aaron Lee on 2023/07/25.
//

#ifndef LEARNGLES_TIMEUTIL_H
#define LEARNGLES_TIMEUTIL_H

#include <chrono>

using namespace std::chrono;

void ResetTime();

long long GetTimestampMilliSeconds();

float GetEscapeSecs();


#endif //LEARNGLES_TIMEUTIL_H
