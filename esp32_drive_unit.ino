#include <BluetoothSerial.h>

const int motorP = 12;
const int motorP1 = 27;
const int motorP2 = 26;

const int motorEnA = 25;
const int motorIn1 = 32;
const int motorIn2 = 33;

const int motorEnB = 14;
const int motorIn3 = 13;
const int motorIn4 = 35;
bool frenD = false;
bool frenI = false;
BluetoothSerial SerialBT;

int velocidad = 0;  

void setup() {
  pinMode(motorP1, OUTPUT);
  pinMode(motorP2, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  
  ledcSetup(0, 5000, 8);
  ledcAttachPin(motorP, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(motorEnA, 1);
  ledcSetup(2, 5000, 8);
  ledcAttachPin(motorEnB, 2);
  
  Serial.begin(115200);
  SerialBT.begin("ESP32test3"); // nombre del blutu
  Serial.println("Listo para estar emparejado");
  
  ledcWrite(0, velocidad);
  //ledcWrite(1, velocidad);
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    controlarMotores(comando);
    Serial.println(comando);
  }
}

void controlarMotores(char comando) {
  switch (comando) {
    
    case 'F':
      if(frenD == true){
        digitalWrite(motorIn1, LOW);
        digitalWrite(motorIn2, HIGH);
        delay(150);
        frenD = false;
      }else if(frenI == true){
        digitalWrite(motorIn3, HIGH);
        digitalWrite(motorIn4, LOW);
        delay(150);
        frenI = false;
      }
      digitalWrite(motorP1, HIGH);
      digitalWrite(motorP2, LOW);
      break;
    case 'B':
      digitalWrite(motorP1, LOW);
      digitalWrite(motorP2, HIGH);
      break;
    case 'S':
      digitalWrite(motorP1, LOW);
      digitalWrite(motorP2, LOW);
      break;
    case 'L':
      if(frenD == true){
        digitalWrite(motorIn1, LOW);
        digitalWrite(motorIn2, HIGH);
        delay(150);
        frenD = false;
      }
      if(frenI == false){
        digitalWrite(motorIn3, LOW);
        digitalWrite(motorIn4, HIGH);
        delay(150);
        frenI = true;
      }
      digitalWrite(motorP1, HIGH);
      digitalWrite(motorP2, LOW);
      break;
    case 'R':
      if(frenI == true){
        digitalWrite(motorIn3, HIGH);
        digitalWrite(motorIn4, LOW);
        delay(150);
        frenI = false;
      }
      if(frenD == false){
        digitalWrite(motorIn1, HIGH);
        digitalWrite(motorIn2, LOW);
        delay(150);
        frenD = true;
      }
      digitalWrite(motorP1, HIGH);
      digitalWrite(motorP2, LOW);
      break;
    default:
      ajustarVelocidad(comando);
  }

  ledcWrite(0, velocidad);
  //ledcWrite(1, velocidad);
}

void ajustarVelocidad(char comando) {
  if (comando >= '0' && comando <= '9') {
    int nueva_velocidad = map(comando - '0', 0, 9, 0, 255);
    velocidad = nueva_velocidad;
  }
}
