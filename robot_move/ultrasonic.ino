

float distance;
unsigned long time_bounce;

float ultrasonic_distance(int ultra) {
    //Serial1.begin(9600);

    pinMode(ultra,OUTPUT);

    digitalWrite(ultra,LOW);
    delayMicroseconds(5);

    digitalWrite(ultra,HIGH);
    delayMicroseconds(10);
    digitalWrite(ultra,LOW);

     pinMode(ultra,INPUT);


    time_bounce=pulseIn(ultra,HIGH);
    distance=0.017*time_bounce;

    //Serial1.println("Distancia: ");
    //Serial1.print(distance);
    //Serial1.println(" cm");

    delay(500);
    return distance;
}
