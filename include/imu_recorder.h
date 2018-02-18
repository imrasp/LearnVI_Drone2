//
// Created by rasp on 1/23/18.
//
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <common/mavlink.h>
#include "autopilot_interface.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#ifndef C_UART_INTERFACE_EXAMPLE_IMU_RECORDER_H
#define C_UART_INTERFACE_EXAMPLE_IMU_RECORDER_H

class IMU_Recorder{
public:
    IMU_Recorder(bool activate);
    ~IMU_Recorder();

    void start(Autopilot_Interface *autopilot_interface_);
    void stop();

    void set_ref_time(mavlink_system_time_t system_time);
    void record();
private:
    bool active;
    bool time_to_exit;
    Autopilot_Interface *autopilot_interface;
    uint64_t unix_time_ref, boot_time_ref;
    mavlink_system_time_t ref_system_time;

    boost::thread threadRecordIMU;
};
#endif //C_UART_INTERFACE_EXAMPLE_IMU_RECORDER_H
