#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

const int x_axis_pin = A1;    //Joystick x_axis input pin
const int y_axis_pin = A0;    //Joystick y_axis input pin


const int hammer_weapon_button = 3;       //Instantaneous Digital input from push button


struct package
{
    int X = 512;
    int Y = 512;
    int hammer_weapon_input = 0;
    int roller_weapon_switch_state = 0;
    int ManualOverride = 0;
};

typedef struct package Package;
Package dataToSend;

RF24 radio(7, 8); // CE, CSN
RF24Network network(radio); // Include the radio in the network
const uint16_t this_node = 01; // Address of this node in Octal format
const uint16_t node00 = 00; 

void setup() 
{
    Serial.begin(9600);
    radio.begin();
    SPI.begin();
    network.begin(90, this_node);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();
    
    /*PinMode declaration for 2 switches*/
    pinMode(hammer_weapon_button, INPUT_PULLUP);

    /*PinMode declaration for Joystick pins*/
    pinMode(x_axis_pin,INPUT);
    pinMode(y_axis_pin,INPUT);

}

void loop() 
{

    network.update();
    
    dataToSend.X = 1024-analogRead(x_axis_pin);
    dataToSend.Y = 1024-analogRead(y_axis_pin);
    dataToSend.roller_weapon_switch_state = 0;
    dataToSend.hammer_weapon_input = 1;

    RF24NetworkHeader header7(node00);
    network.write(header7,&dataToSend, sizeof(dataToSend)); // Send the entire struct as a binary packet

}
