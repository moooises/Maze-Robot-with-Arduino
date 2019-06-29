
/**
void setup() {
 pinMode(LED,OUTPUT);
Serial.begin(9600);
0}*/

//const int LED=9;
float c;
int CNY70(int CNY_Pin) //Blanco 0 y negro 1 provisional
{
  const float Value_CNY_Pin=analogRead(CNY_Pin);
  const float ResolutionADC=0.0048;
  float Voltage=0.0048*Value_CNY_Pin;
  
  
  //Serial1.println(Value_CNY_Pin);
 // Serial1.print("Voltaje: ");
 // Serial1.print(Voltage);
 // Serial1.print(" V");

  if(Voltage>=2.9-0.8)//2.9
  {
   //Serial1.println(" Negro");
   return 1;
  }
  else
  {
   //Serial1.println(" Blanco");
   return 0;
  }
  
  
}

float CNY70_V(int CNY_Pin)
{
  const float Value_CNY_Pin=analogRead(CNY_Pin);
  const float ResolutionADC=0.0048;
  float Voltage=0.0048*Value_CNY_Pin;
  return Voltage;
}
