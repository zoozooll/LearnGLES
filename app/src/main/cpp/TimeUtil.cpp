//
// Created by Aaron Lee on 2023/9/14.
//


#include "TimeUtil.h"
static long long _startTime = 0;

long long GetTimestampMilliSeconds() {
    std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return ms.count();
}

void ResetTime() {
    _startTime = GetTimestampMilliSeconds();
}

float GetEscapeSecs() {
    auto cur = GetTimestampMilliSeconds();
    return float(cur - _startTime) / 1000.f;
}
