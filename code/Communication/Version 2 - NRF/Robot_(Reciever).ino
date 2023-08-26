// Motor 1 connections
int in1A = 22;
int in1B = 24;
int pwm1 = 2;
// Motor 2 connections
int in2A = 26;
int in2B = 28;
int pwm2 = 3;
// Motor 3 connections
int in3A = 30;
int in3B = 32;
int pwm3 = 4;
// Motor 4 connections
int in4A = 34;
int in4B = 36;
int pwm4 = 5;
// Motor 5 connections
int in5A = 31;
int in5B = 33;
int pwm5 = 6;
// Motor 6 connections
int in6A = 35;
int in6B = 37;
int pwm6 = 7;

int yAxis;
int xAxis;


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

//int MO_Status = false;

struct package
{
    int X = 512;
    int Y = 512;
    int hammer_weapon_input = 0;
    int roller_weapon_switch_state = 0;
    //int ManualOverride = 0;
};
typedef struct package Package;
Package dataReceived;

RF24 radio(43, 41); // CE, CSN
RF24Network network(radio); // Include the radio in the network
const uint16_t this_node = 00; // Address of our node in Octal format

void setup()
{
    pinMode(in1A,OUTPUT);  pinMode(in1B,OUTPUT);  pinMode(pwm1,OUTPUT);
    pinMode(in2A,OUTPUT);  pinMode(in2B,OUTPUT);  pinMode(pwm2,OUTPUT);
    pinMode(in3A,OUTPUT);  pinMode(in3B,OUTPUT);  pinMode(pwm3,OUTPUT);
    pinMode(in4A,OUTPUT);  pinMode(in4B,OUTPUT);  pinMode(pwm4,OUTPUT);
    pinMode(in5A,OUTPUT);  pinMode(in5B,OUTPUT);  pinMode(pwm5,OUTPUT);
    pinMode(in6A,OUTPUT);  pinMode(in6B,OUTPUT);  pinMode(pwm6,OUTPUT);
  
    Serial.begin(9600);
    radio.begin();
    SPI.begin();
    network.begin(90, this_node);
    radio.setPALevel(RF24_PA_MIN);
    radio.setDataRate(RF24_250KBPS);
    radio.startListening();

    move_forward();
    delay(2000);
    move_backwards();
    delay(2000);
}

void loop()
{
    network.update();
    while (network.available())
    {
        RF24NetworkHeader header;
        network.read(header, &dataReceived, sizeof(dataReceived)); // Read the incoming data

        if (header.from_node == 1)
        {
            yAxis = dataReceived.Y;
            xAxis = dataReceived.X;
            //print_values();
        }

         /*
        if (header.from_node == 2)
        {
            print_values();
        }
        */
    }


    /*-------------  Mapping Joystick Values to Motion-Motor Driver PWM Values  --------------*/



    /*          Analog Input Range: 0-1023      ,       Analog Output Range: 0-255        */

    /*
    //Map analog inputs as follows:- 600-1023: Forward, 0-400: Backward, 400-600: Do nothing (Controller Deadzone)
    int speed_forward   = map(yAxis, 600, 1023, 0, 255);  
    int speed_backwards = map(yAxis, 400, 0, 0, 255);

    //Map analog inputs as follows:- 600-1023: Right  , 0-400: Left    , 400-600: Do nothing (Controller Deadzone)
    int speed_right     = map(xAxis, 600, 1023, 0, 255);
    int speed_left      = map(xAxis, 400, 0, 0, 255);
    */
    
    /*-------------------------------  Motion Control  --------------------------------------*/

    if (yAxis > 600) 
    {   
        move_forward();     //DEFINE : Use speed_forward value
    } 
    else if (yAxis < 400) 
    {                     
        move_backwards();   //DEFINE : Use speed_backwards value
    } 
    /*
    else if (xAxis > 600) 
    {                    
        turn_right();       //DEFINE : Use speed_right value
    } 
    else if (xAxis < 400) 
    {                     
        turn_left();        //DEFINE : Use speed_left value
    } 
    else  
    {     
        stop_moving();      //DEFINE : Give zero velocity to all motion motors
    }
    */

}

void print_values()
{
    Serial.print("X: ");
    Serial.print(dataReceived.X);
    Serial.print(", Y: ");
    Serial.print(dataReceived.Y);
    Serial.print(", Roller: ");
    Serial.print(dataReceived.roller_weapon_switch_state);
    Serial.print(", Hammer: ");
    Serial.println(dataReceived.hammer_weapon_input);
    //Serial.print(", MO: ");
    //Serial.println(dataReceived.ManualOverride);
    delay(10); 
}

void  motor_1_move_forward()
{
  digitalWrite(in1A,HIGH);digitalWrite(in1B,LOW);analogWrite(pwm1,255);  
}

void motor_1_move_backwards()
{
  digitalWrite(in1A,LOW);digitalWrite(in1B,HIGH);analogWrite(pwm1,255); 
}

void motor_1_stop()
{
  digitalWrite(in1A,HIGH);digitalWrite(in1B,HIGH);
}

void  motor_2_move_forward()
{
  digitalWrite(in2A,HIGH);digitalWrite(in2B,LOW);analogWrite(pwm2,255);  
}

void motor_2_move_backwards()
{
  digitalWrite(in2A,LOW);digitalWrite(in2B,HIGH);analogWrite(pwm2,255); 
}

void motor_2_stop()
{
  digitalWrite(in2A,HIGH);digitalWrite(in2B,HIGH);
}

void move_forward()
{
  motor_1_move_forward();
  motor_2_move_forward();
}

void move_backwards()
{
  motor_1_move_backwards();
  motor_2_move_backwards();
}
