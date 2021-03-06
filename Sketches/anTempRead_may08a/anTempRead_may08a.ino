 

  
int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V

int adc_fs = 1024;
int adc_voq = 155;

int val = 0;           // variable to store the value read
float temp_c = 0;

int setpoint = 310;
int error = 0;
int lasterror = 0;

float deltaT = 0.1;
float Ppart, Ipart, Dpart, out;
float kp = 0.2;
float ki = 0.01;
float kd = 0.01;

float maxout = 10000;
float minout = -10000;

void setup()

{

  Serial.begin(9600);          //  setup serial

}



void loop()

{

  val = analogRead(analogPin);    // read the input pin
  temp_c = (val - 155 ) / 3.10303;

  error = setpoint - val;
  Ppart = error * kp;  

  if ((Ppart >0 && out <maxout )||(Ppart < 0 && out >minout ))/**antiwindup condition**/  
    Ipart= Ipart + ki*error*deltaT; 

  Dpart= (kd *(error - lasterror ))/deltaT; 

  out = Ppart+Ipart+Dpart; //total output

  lasterror = error;
 
  Serial.print(val);             // debug value
  Serial.print("\t");
  Serial.print(temp_c); 
  Serial.print("\t");
  Serial.print(error); 
  Serial.print("\t");
  Serial.print(Ppart);
  Serial.print("\t");
  Serial.print(Ipart);  
  Serial.print("\t");
  Serial.print(Dpart);
  Serial.print("\t");
  Serial.print(out);
  Serial.print("\n");  
  
  delay(100);


  
}
