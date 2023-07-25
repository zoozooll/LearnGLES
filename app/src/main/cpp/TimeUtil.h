//
// Created by Aaron Lee on 2023/07/25.
//

#ifndef LEARNGLES_TIMEUTIL_H
#define LEARNGLES_TIMEUTIL_H

#include <chrono>

using namespace std::chrono;

inline long long GetTimestampMilliSeconds() {
    milliseconds ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    return ms.count();
}


#endif //LEARNGLES_TIMEUTIL_H
