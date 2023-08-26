#include <Wire.h>
#include <Servo.h>
Servo arm_servo;



int in1A = 22;
int in1B = 24;
int pwm1 = 2;

int in2A = 26;
int in2B = 28;
int pwm2 = 3;

int EN1_ENTC = 7; 

int in4A = 34;
int in4B = 36;
int pwm4 = 5;

int in5A = 31;
int in5B = 33;
int pwm5 = 6;



void setup() 
{
  
    Serial.begin(9600);

    arm_servo.attach(9);
    arm_servo.write(140);

    digitalWrite(EN1_ENTC,LOW);
    
    pinMode(in1A,OUTPUT);  pinMode(in1B,OUTPUT);  pinMode(pwm1,OUTPUT);
    pinMode(in2A,OUTPUT);  pinMode(in2B,OUTPUT);  pinMode(pwm2,OUTPUT);
    pinMode(EN1_ENTC,OUTPUT);
    pinMode(in4A,OUTPUT);  pinMode(in4B,OUTPUT);  pinMode(pwm4,OUTPUT);
    pinMode(in5A,OUTPUT);  pinMode(in5B,OUTPUT);  pinMode(pwm5,OUTPUT);    
    
}



void loop() 
{
  
  if (Serial.available()) 
  {
    char receivedData = Serial.read(); 

    if (receivedData == 'B') 
    {
      move_forward();
      delay(200);
    }
    else if (receivedData == 'F') 
    {
      move_backwards();
      delay(200);
    }
    else if (receivedData == 'R') 
    {
      left_turn();
      delay(200);
    }
    else if (receivedData == 'L') 
    {
      right_turn();
      delay(200);
    }
    else if (receivedData == 'X')
    {
      arm_down();
      delay(500);
      arm_up();
      delay(10);
    }
    else if (receivedData == 'U')
    {
      roller_on();
      delay(10);
    }
    else if (receivedData == 'I')
    {
      roller_off();
      delay(10);
    }
    else if (receivedData == 'S')
    {
      stop_all();      
    }
  }
  else
  {
    stop_all();
  }

}


 
void motor_1_move_forward()  
{
  digitalWrite(in1A,HIGH);digitalWrite(in1B,LOW);analogWrite(pwm1,255);  
}

void motor_1_move_backwards()  
{
  digitalWrite(in1A,LOW);digitalWrite(in1B,HIGH);analogWrite(pwm1,255); 
}

void motor_1_move_forward_slow()  
{
  digitalWrite(in1A,HIGH);digitalWrite(in1B,LOW);analogWrite(pwm1,180);  
}

void motor_1_move_backwards_slow() 
{
  digitalWrite(in1A,LOW);digitalWrite(in1B,HIGH);analogWrite(pwm1,180); 
}


void motor_1_stop() 
{
  digitalWrite(in1A,LOW);digitalWrite(in1B,LOW);
}

void  motor_2_move_forward()
{
  digitalWrite(in2A,HIGH);digitalWrite(in2B,LOW);analogWrite(pwm2,255);  
}

void motor_2_move_backwards()
{
  digitalWrite(in2A,LOW);digitalWrite(in2B,HIGH);analogWrite(pwm2,255); 
}

void  motor_2_move_forward_slow()
{
  digitalWrite(in2A,HIGH);digitalWrite(in2B,LOW);analogWrite(pwm2,180);  
}

void motor_2_move_backwards_slow()
{
  digitalWrite(in2A,LOW);digitalWrite(in2B,HIGH);analogWrite(pwm2,180); 
}

void motor_2_stop() 
{
  digitalWrite(in2A,LOW);digitalWrite(in2B,LOW);
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

void stop_all()
{
  motor_1_stop();
  motor_2_stop();
}

void right_turn()
{
  motor_1_move_forward_slow();
  motor_2_move_backwards_slow();
}

void left_turn()
{
  motor_1_move_backwards_slow();
  motor_2_move_forward_slow();
}

void arm_down()
{
  for(int i=140;i>=87;i=i-1)
  {
    arm_servo.write(i);     
    delay(2);
  }
}

void arm_up()
{
  for (int i=87;i<=104;i=i+1)
  {
    arm_servo.write(i);     
    delay(15);
  }
  for (int i=104;i<=122;i=i+1)
  {
    arm_servo.write(i);     
    delay(30);
  } 
  for (int i=122;i<=140;i=i+1)
  {
    arm_servo.write(i);     
    delay(45);
  } 
}

void roller_on()
{
  digitalWrite(EN1_ENTC,HIGH);
  delay(10);
}

void roller_off()  
{
  digitalWrite(EN1_ENTC,LOW);
  delay(10);  
}
