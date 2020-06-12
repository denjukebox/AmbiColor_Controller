#ifndef Configuration_h
#define Configuration_h

// VERSION
#define VERSION 100

// SERIAL CONFIG
#define INITIAL_SERIAL_RX_SIZE 64

//LED CONFIG
#define NUM_OF_STRIPS 2
#define MAX_OF_STRIPS 4
#define LED_TYPE WS2811_GRB | WS2811_800kHz

//LED DATA PINS
#define DATA_PIN_1 2
#define DATA_PIN_2 14
#define DATA_PIN_3 7
#define DATA_PIN_4 8

#define DEBUG_SETTINGS
#define DEBUG_INPUT
#define DEBUG_MAIN
#define DEBUG_CONTROLLER
#define DEBUG_BUFFER


#endif
