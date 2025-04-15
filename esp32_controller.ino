#include <BluetoothSerial.h> //libreria bluetooth

// conexiones en pines ->
const int brake = 28;
const int stop = 27;
const int direccion=26;
const int stopnuevo = 33;
const int motorEnA = 12;
const int paro=25;
const int motorEnB = 14;
const int motorIn3 = 13;
const int motorIn4 = 25;

BluetoothSerial SerialBT; // objeto para conectar bluetooth

int velocidad = 0;   // start velocity

void setup() {
// pins outpout
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  pinMode(direccion, OUTPUT);
// configuration for velocity control (PWM)
  ledcSetup(0, 5000, 8); // 0 5kHz, 8b
  ledcAttachPin(motorEnA, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(motorEnB, 1);

  Serial.begin(115200); // monitor
  SerialBT.begin("ESP32test4"); // nombre del blutu
  Serial.println("Listo para estar emparejado");
  
  ledcWrite(0, velocidad);
  ledcWrite(1, velocidad);// startup 0 
}

void loop() { // in case of a bluetooth signal: 
  if (SerialBT.available()) {
    char comando = SerialBT.read(); // read
    controlarMotores(comando); // action
    Serial.println(comando); // show in monitor
  }
}

void controlarMotores(char comando) {
  switch (comando) {
    
    case 'F': // forward
      digitalWrite(direccion, HIGH);
      break;
    
    case 'P': // Stop motors
      digitalWrite(motorIn3, LOW);
      digitalWrite(motorIn4, LOW);
      break;
    
    case 'w': // Deactivate brake
      digitalWrite(paro, LOW); // PARO ES EL BRAKE (PENULTIMO) pin 25  Y HACE QUE no se pueda mover la rueda
      break;

    case 'W': // Activate brake
      digitalWrite(paro, HIGH);
      break;
    
    case 'B': // Reverse
      //digitalWrite(brake, HIGH);
      //digitalWrite(stop, LOW);
      digitalWrite(direccion,LOW);
      //digitalWrite(paro,LOW);
      break;

    case 'X': // new stop activate
      digitalWrite(stopnuevo,HIGH);
      break;
    
    case 'x': // new stop deactivate
      digitalWrite(stopnuevo,LOW);
      break;
    // space for more actions -->
    case 'S':

      break;
    
    case 'L':
      
      break;
    
    case 'R': // Deactivate brake (again)
      digitalWrite(paro,LOW);
      break;
    
    default: // velocity  0-9
      ajustarVelocidad(comando); 
  }

  ledcWrite(0, velocidad); //same velocity for both motors
  ledcWrite(1, velocidad);
}

void ajustarVelocidad(char comando) { // function to adjust velocity
  if (comando >= '0' && comando <= '9') {
    int nueva_velocidad = map(comando - '0', 0, 9, 0, 255);
    velocidad = nueva_velocidad;
  }
}
