#include <BluetoothSerial.h>

const int brake = 28;
const int stop = 27;
const int direccion=26;
const int stopnuevo = 33;
const int motorEnA = 12;
const int paro=25;
const int motorEnB = 14;
const int motorIn3 = 13;
const int motorIn4 = 25;

BluetoothSerial SerialBT;

int velocidad = 0;  

void setup() {

  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  pinMode(direccion, OUTPUT);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(motorEnA, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(motorEnB, 1);

  Serial.begin(115200);
  SerialBT.begin("ESP32test4"); // nombre del blutu
  Serial.println("Listo para estar emparejado");
  
  ledcWrite(0, velocidad);
  ledcWrite(1, velocidad);
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
      digitalWrite(direccion, HIGH);
      break;
    case 'P':

      digitalWrite(motorIn3, LOW);
      digitalWrite(motorIn4, LOW);
      break;
    case 'w':
      digitalWrite(paro, LOW); // PARO ES EL BRAKE (PENULTIMO) pin 25  Y HACE QUE no se pueda mover la rueda
      break;

    case 'W':
      digitalWrite(paro, HIGH);
      break;
    case 'B':
      //digitalWrite(brake, HIGH);
      //digitalWrite(stop, LOW);
      digitalWrite(direccion,LOW);
      //digitalWrite(paro,LOW);
      break;

    case 'X':
      digitalWrite(stopnuevo,HIGH);
      break;
    case 'x':
      digitalWrite(stopnuevo,LOW);
      break;
    case 'S':

      break;
    case 'L':
      
      break;
    case 'R':
      digitalWrite(paro,LOW);
     
      break;
    default:
      ajustarVelocidad(comando);
  }

  ledcWrite(0, velocidad);
  ledcWrite(1, velocidad);
}

void ajustarVelocidad(char comando) {
  if (comando >= '0' && comando <= '9') {
    int nueva_velocidad = map(comando - '0', 0, 9, 0, 255);
    velocidad = nueva_velocidad;
  }
}
