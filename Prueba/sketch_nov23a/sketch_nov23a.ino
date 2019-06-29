/* Giro alterno de motor DC con driver L293D
*/
const int in1Pin=9;
const int in2Pin=10;

const int in1Pin2=5;
const int in2Pin2=6;


void setup() {
  pinMode(in1Pin,OUTPUT);
  pinMode(in2Pin,OUTPUT);
  pinMode(in1Pin2,OUTPUT);
  pinMode(in2Pin2,OUTPUT);

}

void loop() {



   // delay(1000);
    digitalWrite(in1Pin,HIGH);
    digitalWrite(in2Pin,LOW);
    digitalWrite(in1Pin2,HIGH);
    digitalWrite(in2Pin2,LOW);
    

    delay(1000);
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,HIGH);
    digitalWrite(in1Pin2,LOW);
    digitalWrite(in2Pin2,HIGH);

    delay(1000);

  
  
}
