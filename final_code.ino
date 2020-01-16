//include biblio de servo motors
#include <Servo.h>

//define pin of arduino Mega
#define sensor_left A1 
#define sensor_middle A2 
#define sensor_right A3
#define valve_pine 9
#define tank_pine 10
#define trig_pine 29
#define echo_pine A9
#define broche2 2
#define broche8 24
#define motor_left_up 8
#define motor_left_down 9
#define motor_right_up 4
#define motor_right_down 5
#define threshold 500
#define S0 13                                      
#define S1 12                                   
#define S2 4                                    
#define S3 7
#define sensorOut 5

//define variables
Servo valve;
Servo tank;
int pos=50;
int pos1=40;
int i=0;
int j=0;
int b=0;
int R=0;
int B=0;
int G=0;
int duration=0;
int distance=0;

//define functions
void Red() 
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  R = (pulseIn(sensorOut, LOW));
}

void Green() 
{
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  G = pulseIn(sensorOut, LOW);
}

void Blue() 
{
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  B = pulseIn(sensorOut, LOW);
}

int read_color() 
{
  if ((R>10 && G>10 && B>10))
    return (1);
 else 
 return(0);
}

void robot_moving_forward () 
{
  analogWrite( motor_left_up,120);  
  analogWrite(motor_right_up,120);  
  analogWrite( motor_left_down,0);    
  analogWrite(motor_right_down,0);     
}

void robot_turn_right() 
{
  analogWrite( motor_left_up,0);
  analogWrite(motor_right_up,120);
  analogWrite( motor_left_down,0);
  analogWrite(motor_right_down,0);
}

void robot_turn_left () 
{
  analogWrite( motor_left_up,120);
  analogWrite(motor_right_up,0);
  analogWrite( motor_left_down,0);
  analogWrite(motor_right_down,0);
}

void stopMotors()
{
  analogWrite( motor_left_up,0);
  analogWrite(motor_right_up,0);
  analogWrite( motor_left_down,0);
  analogWrite(motor_right_down,0);
}

int read_one_sensor(int pin)
{
  if ( analogRead ( pin ) > threshold )
        return(1); 
  else 
        return(0);
}

int read_sensors()
{
  return (read_one_sensor(sensor_left)*100+read_one_sensor(sensor_middle)*10+read_one_sensor(sensor_right));
}

//define configurations and initialisations
void setup() {
  pinMode(broche2, OUTPUT);
  pinMode(broche8, OUTPUT);
  valve.attach(valve_pine);
  valve.write(pos);
  tank.attach(tank_pine);
  tank.write(pos1);
  pinMode( motor_left_up,OUTPUT);
  pinMode( motor_left_down,OUTPUT);
  pinMode(motor_right_up,OUTPUT);
  pinMode(motor_right_down,OUTPUT);
  pinMode(sensor_left,INPUT);
  pinMode(sensor_middle,INPUT);
  pinMode(sensor_right,INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  pinMode(broche8,OUTPUT);
  pinMode(echo_pine,INPUT);
  Serial.begin(9600);
}

//function loop
void loop() {
  
//reed color sensor
Red();
Green();
Blue();

//if the robot doesn't attain the second black line yet
if(i<2)
{      
       //if the robot attain the green square
       if (read_color()==1)
       {
                stopMotors();
                digitalWrite(broche8,HIGH);
                tank.write(140);
                delay(3000);
                tank.write(pos1);
                digitalWrite(broche8,LOW);
                robot_moving_forward();
                delay(400);
       }
       
       //else
       b=read_sensors();
       switch(b)
       {
                case(1):
                {
                robot_turn_left();
                break;
                }
                case(10):
                {
                robot_moving_forward();
                break;
                }
                case(11):
                {
                robot_turn_left();
                break;
                }
                case(100):
                {
                robot_turn_right();
                break;
                }
                case(111):
                {
                i++;
                stopMotors();
                valve.write(pos+65);
                delay (10000); 
                robot_moving_forward();
                delay(400);
                break;
                }
  
       }
       
}
//if the robot attain the second black line
if(i==2)
{      
       //if it's white
       if((read_color()==0))
       {
                digitalWrite(broche8,HIGH);
                delay(50);
                digitalWrite(broche8,LOW);
                duration=pulseIn(echo_pine,HIGH);
                distance=(duration/2)/29.1;
                if(distance<4)
                    robot_turn_left();
                if(distance>6)
                    robot_turn_right();
                if((distance<6)&&(distance>4))
                    robot_moving_forward();
       }
       
       //if the robot attain the red line 
       if((read_color()==1)&&(j==0))
       { 
                stopMotors();
                digitalWrite(broche2, HIGH);
                delay(5000);
                digitalWrite(broche2,LOW);
                robot_moving_forward();
                delay(400);
                j++;
       }
       
       //if the robot attain the green line
       if((read_color()==1)&&(j==1))
       {
                stopMotors();
                digitalWrite(broche8,HIGH);
                tank.write(140);
                delay(3000);
                tank.write(pos1);
                analogWrite(broche8,LOW);
                while(1) {}                    //end of the circuit              
       } 
}
}
              
