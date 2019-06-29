

float sharp(int Sharp_Pin)
{
 // Serial1.begin(9600);

  float Value_Sharp_Pin=analogRead(Sharp_Pin);
  float Voltage=Value_Sharp_Pin*ResolutionADC;
  //Serial1.println(Value_Sharp_Pin);
  //Serial1.print(" Voltage");
  //Serial1.print(Voltage);
  //Serial1.println(" V");
  //Serial1.print(" Distancia Sharp: ");
  float distance=GetDistance(Voltage);
  //Serial1.print(distance);
  //GetDistance(Voltage);
  //Serial1.println(" cm");

  delay(1000);//Tratar el delay con velocidad de movimiento
  return distance;
}


float GetDistance(float Voltage)
{
    //Serial.print(1/(0.05*Voltage-0.01));

  if(Voltage<0.4 || Voltage>2.5)return 0;
    else return (1/((Voltage+0.3568)/15.71)+0.42);

  //else return (1/(0.05*Voltage-0.01));
}
