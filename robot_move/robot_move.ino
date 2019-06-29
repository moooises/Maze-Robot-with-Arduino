

int input;

void StopROBOT(int pin1,int pin2,int pin3,int pin4)
{
  UnaRuedaAdelante(pin1,pin2,0);
  UnaRuedaAdelante(pin3,pin4,0);
  delay(1000);
}

void ForwardROBOT(int pin1,int pin2,int pin3,int pin4,int velocidad)
{
  //visto desde atras
    UnaRuedaAdelante(pin1,pin2,velocidad+70);//rueda drch
    UnaRuedaAdelante(pin3,pin4,velocidad);//Rueda izq
}

void BackwardROBOT(int pin1,int pin2,int pin3,int pin4,int velocidad)
{
     UnaRuedaAdetras(pin1,pin2,velocidad);
    UnaRuedaAdetras(pin3,pin4,velocidad);
}

void UnaRuedaAdelante(int pin1,int pin2,int velocidad)//Para ir hacia adelante tenemos que llamar dos veces a esta funcion con pines distintos
{
    input=map(velocidad,0,1023,0,254);
    analogWrite(pin1,input);
    analogWrite(pin2,0);
}

void UnaRuedaAdetras(int pin1,int pin2,int velocidad)//Para ir hacia atras tenemos que llamar dos veces a esta funcion con pines distintos
{  
    input=map(velocidad,0,1023,0,254);
    analogWrite(pin1,0);
    analogWrite(pin2,input);

}

void RightROBOT(int pin1,int pin2,int pin3,int pin4,int velocidad)//Dos primeros pines, rueda derecha,dos ultimos, rueda izquierda
{
  input=map(velocidad,0,1023,0,254);
  UnaRuedaAdelante(pin3,pin4,velocidad);
  UnaRuedaAdetras(pin1,pin2,velocidad+70);
  
}

void LeftROBOT(int pin1,int pin2,int pin3,int pin4,int velocidad)
{
  input=map(velocidad,0,1023,0,254);
  UnaRuedaAdelante(pin1,pin2,velocidad+150);
  UnaRuedaAdetras(pin3,pin4,velocidad+70);
}
