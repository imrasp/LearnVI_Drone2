//
// Created by rasp on 1/23/18.
//

#include "../include/imu_recorder.h"

IMU_Recorder::IMU_Recorder(bool active_) : active(active_),time_to_exit(false) {

}

IMU_Recorder::~IMU_Recorder() {

}

void IMU_Recorder::stop() {
    time_to_exit = true;
    threadRecordIMU.join();
}


void IMU_Recorder::start(Autopilot_Interface *autopilot_interface_) {
    autopilot_interface = autopilot_interface_;

    std::cout << "Start IMU record thread..." << std::endl;
    threadRecordIMU = boost::thread(&IMU_Recorder::record, this);

}

void IMU_Recorder::record(){
    // write out queue
    std::cout << "\n start record IMU \n";
    std::string sep = ",";
    ofstream datasetimu;
    datasetimu.open("./record_data/imu0.csv");
    datasetimu << "timestamp" << sep << "omega_x" << sep << "omega_y" << sep << "omega_z" << sep << "alpha_x" << sep
               << "alpha_y" << sep << "alpha_z" << "\n";

    while (!time_to_exit || !autopilot_interface->queueIMU.empty()) {
        pthread_mutex_lock(&autopilot_interface->mutexIMU);
        pthread_cond_wait(&autopilot_interface->unEmptyIMU, &autopilot_interface->mutexIMU);
        uint64_t timestamp_ms = ref_system_time.time_unix_usec + (autopilot_interface->queueIMU.front().time_usec -
                                                                  (ref_system_time.time_boot_ms * 1000));
        uint64_t timestamp_ns = timestamp_ms * 1000;

        datasetimu << timestamp_ns << sep
                   << autopilot_interface->queueIMU.front().xgyro << sep
                   << autopilot_interface->queueIMU.front().ygyro << sep
                   << autopilot_interface->queueIMU.front().zgyro << sep
                   << autopilot_interface->queueIMU.front().xacc << sep
                   << autopilot_interface->queueIMU.front().yacc << sep
                   << autopilot_interface->queueIMU.front().zacc << endl;
        autopilot_interface->queueIMU.pop();
//        cout << "queue size = " << autopilot_interface->queueIMU.size() << endl;
        pthread_mutex_unlock(&autopilot_interface->mutexIMU);
    }
}

void IMU_Recorder::set_ref_time(mavlink_system_time_t system_time) {
    ref_system_time = system_time;
}

