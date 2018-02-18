//
// Created by rasp on 2/15/18.
//
#include "../include/stream.h"

Stream::Stream(ConfigParam *configParam) {
    missionid = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    nlohmann::json drone_info= {{"misison_id", missionid}, {"drone", configParam->drone}};
    auto r = cpr::Post(cpr::Url{"192.168.1.107:3000/mission_info"},
                       cpr::Body{drone_info.dump()});
}

Stream::~Stream() {}

void Stream::gps_position(uint64_t time, float lat, float lon, float alt){
    //stream position data
    nlohmann::json drone_position = {{"misison_id", 1}, {"time", time}, {"lat", lat},{"lon", lon}, {"alt", alt}};
    auto r = cpr::Post(cpr::Url{"192.168.1.107:3000/current_pos"},
                       cpr::Body{drone_position.dump()});
}