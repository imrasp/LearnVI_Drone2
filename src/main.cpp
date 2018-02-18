#include <iostream>

#include "../include/mavlink_control.h"
#include "../include/camera_recorder.h"
#include "../include/configParam.h"
#include "../include/log.h"
#include "../include/imu_recorder.h"
#include "../include/stream.h"
using namespace std;

int main(int argc, char **argv);

int main(int argc, char **argv) {
    bool bCamera = true;
    bool bIMU = true;
    bool bSLAM = false;

    try {
        ConfigParam configParam(argc, argv);
        Log log("record_data");
        Stream stream(&configParam);
        cout << "Starting main in " << configParam.mode << " mode " << endl;
        IMU_Recorder imu_recorder(true);
        Mavlink_Control mavlinkControl(&configParam, &imu_recorder, &stream);
        Camera_Recorder cameraRecorder(0);
        if(bIMU){
            mavlinkControl.start();
        }
        if(bCamera) cameraRecorder.start();
        mavlinkControl.cmd();
        if(bCamera) cameraRecorder.stop();
        if(bIMU)mavlinkControl.stop();

        return 0;
    }
    catch (int error) {
        fprintf(stderr, "threw exception %i \n", error);
        return error;
    }
}
