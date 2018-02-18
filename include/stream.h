//
// Created by rasp on 2/15/18.
//

#ifndef LEARN_VIDRONE_STREAM_H
#define LEARN_VIDRONE_STREAM_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "configParam.h"

class Stream {
public:
    Stream(ConfigParam *configParam);
    ~Stream();
    void gps_position(uint64_t time, float lat, float lon, float alt);

    long missionid;
};

#endif //LEARN_VIDRONE_STREAM_H
