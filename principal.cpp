#include<Servo.h>

Servo servo1;// brazo
Servo servo2;// brazo
Servo servo3;// puerta de entrada
Servo servo4;// puerta de salida

int buzzer=2;
int a=0,estado=0;
int pstat1=0,pstat2=0;
int led1=3,led2=4;
const int sensorT=A0;
int pir=13;
int enableA=5,enableB=6;
int sensorD1=11,sensorD2=12;
unsigned long tpulse,tpulse2;
int distancia,distancia2;
float tempC;

void setup(){
  servo1.attach(7);//activacion del brazo
  servo2.attach(8);//activacion del brazo
  servo3.attach(10);//activacion del servomotor - entrada
  servo4.attach(9);//activacion del servomotor - salida
  pinMode(pir, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);

}

void loop(){
  
  //activacioon sensor PIR para el brazo
  pstat1 = digitalRead(pir);
  if (pstat1 == HIGH){  
  // medicion de temperatura    
  tempC = analogRead(sensorT);
  tempC = ((5.0 /1024) * tempC*100-50); // formula de la temperatura
  Serial.print("Su Temperatura es: ");
  Serial.print(tempC);
  Serial.println("\n");//para imprimir en el monitor serie
    
    //condicional cuando la temperatura es menor de 38ª
    if (tempC<38){
      digitalWrite(enableB,HIGH);
      servo1.write(90); 
      servo2.write(180);
      delay(5000);
      servo1.write(0);
      servo2.write(0);
      delay(2000);
      digitalWrite(3,HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(500);
      Serial.println("BIENVENIDO¡¡¡¡ SIGA ADELANTE ");
      Serial.println("\n");
    }
    //cuando la temperatura esta se registra y avisa
      else{
        digitalWrite(4,HIGH);
        delay(3000);
        digitalWrite(4,LOW);
        delay(3000);
        Serial.println("Temperatura encima de los limites");
        digitalWrite(buzzer,HIGH);
        servo1.write(0);
        servo2.write(0);
        delay(2000);
        digitalWrite(buzzer,LOW);
      }
    }
    ultrasonido1();
    ultrasonido2();
}

//declaracion de la sensor 1
void ultrasonido1(){
 calculadist();
  Serial.print("distancia1: ");
  Serial.println(distancia);
  //condicional del movimiento de la puerta de entrada
  if(distancia>70 && distancia<290){
    //contador
    estado = digitalRead(11);
    if (estado == HIGH){
    a=a-a;
    delay(1000);
    Serial.print("Nº persona : ");
    Serial.print(a);
    Serial.println("\n");
    }else{
      a=a+1;
      Serial.print("Numero persona: ");
      Serial.print(a);
      Serial.println("\n");
    }
  	digitalWrite(enableA,HIGH);
    servo3.write(90);
    delay(3000);
    servo3.write(0);
    delay(3000);    
  }else if (distancia >= 291){
    servo3.write(0);
  }
}
void ultrasonido2(){
  calculadist2();
  Serial.print("distancia2: ");
  Serial.println(distancia2);
  if(distancia2>70 && distancia2<290){
    estado = digitalRead(11);
    if (estado == HIGH){
    a=a+a;
    delay(1000);
    Serial.print("Nº persona : ");
    Serial.print(a);
    Serial.println("\n");
    }else{
      a=a-1;
      Serial.print("Numero persona: ");
      Serial.println(a);
      Serial.println("Hasta luego :D");
      Serial.println("\n");
    }
  	digitalWrite(enableA,HIGH);
    servo4.write(90);
    delay(3000);
    servo4.write(0);
    delay(3000);
    
  }else if (distancia2 >= 291){
    servo4.write(0);
  } 
  
}
void calculadist2(){
  pinMode(sensorD1, OUTPUT);
  digitalWrite(sensorD1, LOW);
  digitalWrite(sensorD1, HIGH);
  delay(2);
  digitalWrite(sensorD1, LOW);
  pinMode(sensorD1, INPUT);
  tpulse =  pulseIn(sensorD1, HIGH);
  distancia =(345 * tpulse) / (2 * 10000);
}

void calculadist(){
   pinMode(sensorD2, OUTPUT);
  digitalWrite(sensorD2, LOW);
  digitalWrite(sensorD2, HIGH);
  delay(2);
  digitalWrite(sensorD2, LOW);
  pinMode(sensorD2, INPUT);
  tpulse2 =  pulseIn(sensorD2, HIGH);
  distancia2 =(345 * tpulse2) / (2 * 10000);
}

