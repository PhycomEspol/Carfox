//Variables y valores definidos a usar
#define temperatura A4
#define sensorFuerza A3
#define buzzer 6
#define ejex A0
#define ejey A1
#define ejez A2
float Ax, Ay, Az;
float temp;
int presion;
//Parametros limitantes
int aceleracionLimite = 70;
int limiteCaidaLibre = 50;
int presionLimite = 50;
int temperaturaLimite = 40;
String estado = "Estable";

void setup() {
  Serial.begin(9600);
  

}


void loop() {
  
  Ax = map(analogRead(ejex), 0, 1023, -100, 100);
  Ay = map(analogRead(ejey), 0, 1023, -100, 100);
  Az = map(analogRead(ejez), 0, 1023, -100, 100);
/*
  temp = (analogRead(temperatura) / 10240.0) * 5000.0;
  Serial.println(temp);
  Serial.println(Ax);
  Serial.println(Ay);
  Serial.println(Az);
  //Serial.println(ejez);
  */

  if (abs(Ax) >  aceleracionLimite || abs(Ay) >  aceleracionLimite || abs(Az) >  aceleracionLimite) {
    estado = "Exceso de velocidad";
    analogWrite(buzzer, 100);
        delay(100);
        analogWrite(buzzer, 0);
        delay(200);
  }
  else{
    analogWrite(buzzer, 0);
  }
 
  float caidaLibre = abs(Az);
  if (caidaLibre > limiteCaidaLibre && abs(Ax) < 70 && abs(Ay) < 70) {
    estado = "Caida Libre";
    analogWrite(buzzer,500);
        delay(100);
        analogWrite(buzzer, 0);
        delay(200);
  }

  else{
    analogWrite(buzzer, 0);
  }

  if (Az < 0 && (abs(Ax) > 40 || abs(Ay) > 40)) {
    estado = "Volcamiento";
    analogWrite(buzzer, 300);
        delay(100);
        analogWrite(buzzer, 0);
        delay(200);
  }
  
  else{
    analogWrite(buzzer, 0);
  }
  
  presion =  map(analogRead(sensorFuerza), 0, 205, 0, 100);
  
  //Serial.println(presion);
  if (presion > presionLimite) {
    estado = "Choque!!!";
    analogWrite(buzzer, 900);
        delay(100);
        analogWrite(buzzer, 0);
        delay(200);
  }

  else{
    analogWrite(buzzer, 0);
  }

  temp = (analogRead(temperatura) / 10240.0) * 5000.0;
  if (temp > temperaturaLimite) {
    estado = "Incendio!!!";
    analogWrite(buzzer, 900);
        delay(100);
        analogWrite(buzzer, 0);
        delay(200);
  }

  else{
    analogWrite(buzzer, 0);
  }

  Serial.print(estado);
  delay(400);
  
  

}
