#include <StackList.h>

//Motores
const int pin1_Motor=10;
const int pin2_Motor=9;
const int pin3_Motor=5;
const int pin4_Motor=6;
//
const int pin1_CNY=A2;
const int pin2_CNY=A5;
const int pin3_CNY=A0;
const int pin4_CNY=A1;
//
const int pin1_SHARP=A3;
const int pin2_SHARP=A4;
//
const int pin_ULTRA=2;

const float ResolutionADC=0.0048;
float dist;

struct posicion
{
   int fila=0;
   int columna=0;
};
typedef struct posicion Posicion;

enum Direcc{F,L,R,B};//La N es nothing//Enviar esto como char a python
Direcc actual;
//Para los CNY, calibrado
float v_blanco=0;
float v_negro=0;

int fin=0;

StackList <Direcc> posibles; //Almacenara maximo 3 direcc
StackList <Posicion> recorrido;
//StackList <StackList<Direcc>> Opciones;//Almacenara todos los poibles caminos de cada celda, varios posibles
StackList <Direcc> Camino;//Almacenara el camino direccto a seguir desde la salida

Posicion pos_actual;
Posicion visitados[25];
int sentido=0;
int pos=0;
int v;//La velocidad, testear
int v_e;

bool calibrar=false;
String Data="";
//6,5
//9,10


int casilla_repetida(int ,int ,struct posicion [],int );
int es_fin(int ,int ,int ,int );


int casilla_repetida(int f,int c,struct posicion v[],int tam)
{
  int i;
  for(i=0;i<tam;++i)
  {
    if(v[i].fila==f && v[i].columna==c) return 1;
  }
  return 0;
}

void AdelanteGiro(int pin1_Motor,int pin2_Motor,int pin3_Motor,int pin4_Motor,int v)
{
        ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
      delay(1800);
      StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
      delay(500);
}

void Derecha(int pin1_Motor,int pin2_Motor,int pin3_Motor,int pin4_Motor,int pin1_CNY,int pin2_CNY)
{
  int v=800;
  RightROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(950);
  StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  delay(500);
  AdelanteGiro(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
}

void Izquierda(int pin1_Motor,int pin2_Motor,int pin3_Motor,int pin4_Motor,int pin1_CNY,int pin2_CNY)
{
  int v=800;
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(950);
  StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  delay(500);
  AdelanteGiro(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v+100);
}

void Adelante(int pin1_Motor,int pin2_Motor,int pin3_Motor,int pin4_Motor,int pin1_CNY,int pin2_CNY)
{
    int v_e=500;
    int v=800;
    while((CNY70(pin1_CNY)==0 && CNY70(pin2_CNY)==0))
    {
      ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
    }
      StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
      delay(500);  
      if(CNY70(pin1_CNY)==1 && CNY70(pin2_CNY)==0)
      {
        RightROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v_e);
        while(CNY70(pin1_CNY)!=0){}
            StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  
                 //Serial1.println("Esta en el primer caso");
  
        delay(500);
      }
      else
      {
        if(CNY70(pin1_CNY)==0 && CNY70(pin2_CNY)==1)
        {
          LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v_e);
          while(CNY70(pin2_CNY)!=0){}
  
         //  Serial1.println("Esta en el segundo caso");
           delay(500);
        }
        else
        {
         // Serial1.println("Ambos negros");
  ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
      delay(500);
            StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);

        }
   
      }
      ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
      delay(1600);
      StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
      delay(1000);

}
void Atras(int pin1_Motor,int pin2_Motor,int pin3_Motor,int pin4_Motor,int pin3_CNY,int pin_CNY)
{

  int v_e=500;
   int v=800;
   while(CNY70(pin3_CNY)==0 && CNY70(pin4_CNY)==0)
   {
      BackwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
   }
     StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
     delay(1000);  
     if(CNY70(pin3_CNY)==1 && CNY70(pin4_CNY)==0)
     {
       RightROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v_e);
       while(CNY70(pin3_CNY)!=0){}
       StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
       //Serial1.println("Esta en el primer caso");
       delay(1000);
      }
      else
      {
        if(CNY70(pin3_CNY)==0 && CNY70(pin4_CNY)==1)
        {
          LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v_e);
          while(CNY70(pin4_CNY)!=0){}
              StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  
           //Serial1.println("Esta en el segundo caso");
           delay(1000);
        }
   
      }
      BackwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
      delay(2500);
      StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
      delay(1000);
}



float calibrar_blanco(int pin1_CNY,int pin2_CNY,int pin3_CNY,int pin4_CNY)
{
  return (CNY70_V(pin1_CNY)+CNY70_V(pin2_CNY)+CNY70_V(pin3_CNY)+CNY70_V(pin4_CNY))/4;
}

float calibrar_negro(int pin1_CNY,int pin2_CNY,int pin3_CNY,int pin4_CNY)
{
  return (CNY70_V(pin1_CNY)+CNY70_V(pin2_CNY)+CNY70_V(pin3_CNY)+CNY70_V(pin4_CNY))/4;
}

int es_fin(int pin1_CNY,int pin2_CNY,int pin3_CNY,int pin4_CNY)
{
  if(CNY70(pin1_CNY)==1 && CNY70(pin2_CNY)==1 && CNY70(pin3_CNY)==1 && CNY70(pin4_CNY)==1)
  {
    Serial1.println("Fin");
    return 1;
  }
  else
  {
    return 0;
  }
}

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);

   
  
  pinMode(pin1_Motor,OUTPUT);
  pinMode(pin2_Motor,OUTPUT);
  pinMode(pin3_Motor,OUTPUT);
  pinMode(pin4_Motor,OUTPUT);
  
  
  
  
  pinMode(pin1_CNY,INPUT);
  pinMode(pin2_CNY,INPUT);
  pinMode(pin3_CNY,INPUT);
  pinMode(pin4_CNY,INPUT);
 

  
  pinMode(pin1_SHARP,INPUT);
  pinMode(pin2_SHARP,INPUT);
  

  pinMode
  (pin_ULTRA,INPUT);


  
  pos_actual.fila=0;
  pos_actual.columna=0;
  sentido=1;
  //1 -Adelante 2-Derecha 3-Atras 4- Izquierda
  visitados[pos]=pos_actual;
  calibrar=true;
  //v_blanco=calibrar_blanco(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
  //v_negro=calibrar_negro(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
}

void ca()
{
  /**
  Serial1.println("Poner en blanco");
  char aux=Serial.read();
  if(aux!='r'){}
  */
/**
  
      delay(5000);


  float b=calibrar_blanco(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
  Serial1.print("Blanco: ");
  Serial1.println(b);
  Serial1.println();
    delay(5000);

  
  Serial1.println("Poner en negro");
  
  
  float n=calibrar_negro(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
  Serial1.print("Negro: ");
  Serial1.println(n);
  Serial1.println();
  c=(b+n)/2;
  Serial1.println(c);
  delay(5000);
  */
  /**
delay(3000);
  int a=es_fin(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
  if(a)Serial1.println("Es fin");
  */

    //Atras(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
  //Atras(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);

  //Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
  //Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
  //Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
  String Data="";
  if(Serial1.available())
  {
    Data=Serial1.readString();
    Serial1.println(Data);
  }
  if(Data.substring(0)=="ee")
  {
  Izquierda(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
  Serial1.println("Adelante");
  }
/**
delay(1000);
      ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,700 );
delay(3000);
      StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
                        Derecha(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
                        Izquierda(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);

delay(1000);

*/


/**
float d=sharp(pin1_SHARP);
if(d>13.2 )Serial1.println("Izquierda");
 d=sharp(pin2_SHARP);
 if(d>13 )Serial1.println("Derecha");
 d=ultrasonic_distance(pin_ULTRA);
  if(d>10)Serial1.println("Adelante");
 delay(2000);
*/
  }
  /**
  
  */
  //Para testear los sensores de distancias
  //float d=ultrasonic_distance(pin_ULTRA);
  /**
  float d=sharp(pin2_SHARP);
  //Serial.println("distancia
  //float d2=sharp(pin2_SHARP);
  */


  
  //para testear el giro
  /**
  v=700;
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(710);
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(710);
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(710);
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(710);
  
  LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  delay(800);
  
  StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  delay(4000);

  //ForwardROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
  */


void loop()
{

  /**
  if(calibrar)
  {
    delay(5000);
    float b=calibrar_blanco(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
    Serial1.print("Blanco: ");
    Serial1.println(b);
    Serial1.println();
      delay(5000);
  
    /**
    Serial1.println("Poner en negro");
    aux=  while(Serial.read()!='r'){} 
    */
    /**
    float n=calibrar_negro(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY);
    Serial1.print("Negro: ");
    Serial1.println(n);
    Serial1.println();
    c=(b+n)/2;
    Serial1.println( c);
    delay(5000);
    calibrar=false;
  }
  */
  //Serial1.println(sentido);
  if(Serial1.available())
  {
        Data=Serial1.readString();
    Serial1.println(Data);
  }
  if(Data.substring(0)=="Start")
  {
  
  if(!es_fin(pin1_CNY,pin2_CNY,pin3_CNY,pin4_CNY) && !fin)
  {
       //Comprobamos las direcciones 
    float dh=ultrasonic_distance(pin_ULTRA);
    if(dh>10)
    {
      posibles.push(F);//ultrasonic es el de delante
      //Serial1.println("Puede ir adelante");
    }
    else
    {
       Serial1.println("Muro_Enfrente");
    }

    dh=sharp(pin1_SHARP);
     //Serial1.println(dh);

    if(dh>13.2)  //Por ahora este es el que apunta a la izquierda, el que esta puesto ahora
    {
      posibles.push(L);
      //Serial1.println("Puede ir a la Izquierda");
    }
    else
    {
       Serial1.println("Muro_Izquierda");
    }
      
     dh=sharp(pin2_SHARP);
     //Serial1.println(dh);
    if(dh>9.4)//14.5
    {
      posibles.push(R);
      //Serial1.println("Puede ir a la derecha");
    }
    else
    {
       Serial1.println("Muro_Derecha");
    }
  
    //Daremos prioridad al de delante
  
    delay(1000);//¿?¿?¿

    //Aqui comprabamos si una casilla esta repetida
    bool valido=0;
    int auxfila=pos_actual.fila;
    int auxcol=pos_actual.columna;
    while(!posibles.isEmpty() && !valido)
    {
  
        actual=posibles.pop();
        //Verificar el movimiento para el enderezado
        
        switch (actual)
      {
        case F:
                  if(sentido==4)auxcol=auxcol+1;
                  else
                  {
                    if(sentido==1)auxfila=auxfila+1;
                    else
                    {
                      if(sentido==3)auxfila=auxfila-1;
                      else
                      {
                        if(sentido==2)auxcol=auxcol-1;
                      }
                    }
                  }
                
                if(!casilla_repetida(auxfila,auxcol,visitados,pos+1))
                {
                  recorrido.push(pos_actual); 
                  ++pos;
                  valido=1;
        
                  //el sentido no cambia
                  pos_actual.columna=auxcol;
                  pos_actual.fila=auxfila;       
                  //Serial1.println(auxfila);
                  //Serial1.println(auxcol);           
                  visitados[pos]=pos_actual;
                  Camino.push(F);
                  Serial1.println("Avanza");
                  Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
                }
                break;
                
        case R:

                  if(sentido==4)auxfila=auxfila+1;
                  else
                  {
                    if(sentido==1)auxcol=auxcol-1;
                    else
                    {
                      if(sentido==3)auxcol=auxcol+1;
                      else
                      {
                        if(sentido==2)auxfila=auxfila-1;
                      }
                    }
                  }
                
        
                if(!casilla_repetida(auxfila,auxcol,visitados,pos+1))
                {
                  recorrido.push(pos_actual);  ++pos;
                  valido=1;

                  if(sentido==4)sentido=1;
                  else sentido=sentido+1;
                    
                  pos_actual.columna=auxcol;
                  pos_actual.fila=auxfila;
                 // Serial1.println(auxfila);
                  //Serial1.println(auxcol);
                  visitados[pos]=pos_actual;
                  Camino.push(L);//Metemos el opuesto
                  Serial1.println("Gira_Derecha");
                  Derecha(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);

                }
                break;
                
        case L:

                  if(sentido==4)auxfila=auxfila-1;
                  else
                  {
                    if(sentido==1)auxcol=auxcol+1;
                    else
                    {
                      if(sentido==3)auxcol=auxcol-1;
                      else
                      {
                        if(sentido==2)auxfila=auxfila+1;
                      }
                    }
                  }
        
                if(!casilla_repetida(auxfila,auxcol,visitados,pos+1))
                {
                  recorrido.push(pos_actual);  ++pos;
                 valido=1;

             
                  if(sentido==1)sentido=4;
                  else sentido=sentido-1;
                   
                  pos_actual.columna=auxcol;
                  pos_actual.fila=auxfila;
                  //Serial1.println(auxfila);
                  //Serial1.println(auxcol);
                  visitados[pos]=pos_actual;
                  Camino.push(R);
                  Serial1.println("Gira_Izquierda");
                  Izquierda(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);

                }
                break;
      }
    
    }
    
  
    if(posibles.isEmpty() && !valido)//No hay direcciones posibles
    {

      Atras(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
      Serial1.println("Retrocede");
      Posicion pos_aux=recorrido.pop();
      pos_actual.fila=pos_aux.fila;
      pos_actual.columna=pos_aux.columna;
      //--pos;
      actual=Camino.pop();
      if(actual!=F)
      {
        if(actual==L)
        {
           LeftROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
           Serial1.println("Gira_Izquierda");
           if(sentido==1)sentido=4;
           else sentido=sentido-1;
        }
        else
        {
           RightROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,v);
           Serial1.println("Gira_Derecha");
           if(sentido==4)sentido=1;
           else sentido=sentido+1;
        }
      }
    }
  
    while(!posibles.isEmpty())//Vaciamos la lista de posibles
    {
      actual=posibles.pop();
    }

  }
  else
  {
  if(!fin)
  {
      
  
  RightROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,800);
  delay(2500);
  StopROBOT(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor);
  delay(500);
  AdelanteGiro(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,800);
    /**
    Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
 Atras(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
 Derecha(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
  Izquierda(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
  */

    while(!Camino.isEmpty() && Camino.count()>1)
    {
      actual=Camino.pop();
        switch (actual)//
      {
        case F:
                Adelante(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin1_CNY,pin2_CNY);
                break;
                
        case R:
                Derecha(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
                break;
                
        case L:
                Izquierda(pin1_Motor,pin2_Motor,pin3_Motor,pin4_Motor,pin3_CNY,pin4_CNY);
                break;
      }
    }
    
    fin=1;
    }
  }
  }
} 
