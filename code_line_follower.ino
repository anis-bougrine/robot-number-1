//define sensor ports on arduino uno
#define sensor_left A8
#define sensor_middle A9
#define sensor_right A10

//define the level of sensor thresshold
#define threshold 500

//define motors ports on arduino uno
#define motor_left_up 8
#define motor_left_down 9
#define motor_right_up 4
#define motor_right_down 5

//define variables
int i=0;
int j=0;
int b=0;
int k=0;

//dfine functions
void robot_moving_forward() 
{
  analogWrite(motor_left_up,150);  
  analogWrite(motor_right_up,150); 
  analogWrite(motor_left_down,0);    
  analogWrite(motor_right_down,0);    
}

void robot_turn_right () 
{
  analogWrite(motor_left_up,100);
  analogWrite(motor_right_up,0);
  analogWrite(motor_left_down,0);
  analogWrite(motor_right_down,0);
}

void robot_turn_left () 
{
  analogWrite(motor_left_up,0);
  analogWrite(motor_right_up,100);
  analogWrite(motor_left_down,0);
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
void setup(){
pinMode(motor_left_up,OUTPUT);
pinMode(motor_left_down,OUTPUT);
pinMode(motor_right_up,OUTPUT);
pinMode(motor_right_down,OUTPUT);
pinMode(sensor_left,INPUT);
pinMode(sensor_middle,INPUT);
pinMode(sensor_right,INPUT);
Serial.begin(9600);
}

//the loop mode
void loop() {
 
  b=read_sensors();
  
  switch(b){
    
    case(1):{
    robot_turn_left();
    break;
    }
    
    case(10):{
    robot_moving_forward();
    break;
    }
    
    case(11):{
    robot_turn_left();
    break;
    }
    
    case(100):{
    robot_turn_right();
    break;
    }
    
  }
}
//end program
