#include <AFMotor.h>
AF_DCMotor motor1(1); //Motor izquierdo
AF_DCMotor motor2(2); //Motor derecho
const int Led = 9;

void setup() {
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  pinMode(Led, OUTPUT);
}

void motor(int izq, int der, int d){
  // Seteamos potencia de motor
  if(izq > 0){ motor1.setSpeed(izq);} else{motor1.setSpeed(-izq);}
  if(der > 0){ motor2.setSpeed(der);} else{motor2.setSpeed(-der);}
  // Ponemos en marcha los motores: brumm, bruuuuuum...
  if(izq > 0){ motor1.run(FORWARD);} 
  if(izq < 0){ motor1.run(BACKWARD);}
  if(der > 0){ motor2.run(FORWARD);} 
  if(der < 0){ motor2.run(BACKWARD);}
  //Apagamos motores luego de d seg
  delay(d*1000); motor1.run(RELEASE); motor2.run(RELEASE); 
}

void loop() {
  digitalWrite(Led, LOW);

  motor(100, 100, 6);
  motor(100, -100, 2);
  motor(-100, -100, 5);
  motor(-100, 100, 2);

  while(true){ //Final del programa, indicacion.
    digitalWrite(Led, HIGH);
    delay(250);
    digitalWrite(Led, LOW);
    delay(250);
  }           
}
