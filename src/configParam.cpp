#include "../include/configParam.h"

ConfigParam::ConfigParam()
{
   initialization();
}
ConfigParam::ConfigParam(int argc, char **argv)
{
    initialization();
    parse_commandline(argc, argv);
}

ConfigParam::~ConfigParam()
{
   initialization();
}

void ConfigParam::setfps(int fps_){
    fps = fps_;
    timespace = 10000000/fps;
}

void ConfigParam::fps2Timespace(int fps){
    timespace = 10000000/fps;
}

void ConfigParam::initialization(){
    // Default input arguments
#ifdef __APPLE__
    uart_name = (char*)"/dev/tty.usbmodem1";
#else
    uart_name = (char *) "/dev/ttyS0";

#endif
    baudrate = 921600; // 57600 or 921600 px4 companion link buadrate
    vocabulary = (char *) "../Vocabulary/ORBvoc.txt";
    setting = (char *) "../config/mobius.yaml";
    mode = (char *) "LIVE";
    gui = (char *) "ENABLE";
    folder_name = (char *) "Sample_data";
    fps = 10;
    timespace = 1000000;
    mission_route = (char*) "./mission_route.txt";
    drone = "Tarot 450";
}

//   Parse Command Line
void ConfigParam::parse_commandline(int argc, char **argv) {
    // string for command line usage
    const char *commandline_usage = "usage: mavlink_serial -d <devicename> -b <baudrate> -v <path_to_vocabulary> -s <path_to_setting>";

    // Read input arguments
    for (int i = 1; i < argc; i++) { // argv[0] is "mavlink"

        // Help
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("%s\n", commandline_usage);
            throw EXIT_FAILURE;
        }

        // UART device ID
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
            if (argc > i + 1) {
                uart_name = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Baud rate
        if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--baud") == 0) {
            if (argc > i + 1) {
                baudrate = atoi(argv[i + 1]);

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Path to vocabulary
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vocab") == 0) {
            if (argc > i + 1) {
                vocabulary = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Path to setting
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--setting") == 0) {
            if (argc > i + 1) {
                setting = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Mode
        if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
            if (argc > i + 1) {
                mode = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Mode
        if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--gui") == 0) {
            if (argc > i + 1) {
                gui = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }
        // Filename
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--foldername") == 0) {
            if (argc > i + 1) {
                folder_name = argv[i + 1];

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Time space between frame
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--time") == 0) {
            if (argc > i + 1) {
                timespace = atoi(argv[i + 1]);

            } else {
                printf("%s\n", commandline_usage);
                throw EXIT_FAILURE;
            }
        }
    }
    // end: for each input argument

    return;
}
