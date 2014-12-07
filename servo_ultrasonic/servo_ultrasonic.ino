#include <Servo.h> 

const int trigPin = 8; // Pin disparador. Se puede usar otro pin digital
const int echoPin = 7; // Pin eco. Se puede usar otro pin digital
long currentDistanceInCm, previousDistanceInCm, duration; // Declara variables

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created
int servoPos = 0;


void setup() {
  Serial.begin(9600); // Establece la velocidad de datos del puerto serie
  pinMode(trigPin, OUTPUT); // Establece pin como salida
  pinMode(echoPin, INPUT); // Establece pin como entrada
  digitalWrite(trigPin, LOW); // Pone el pin a un estado logico bajo
  currentDistanceInCm = 0;
  previousDistanceInCm = 0;
  
  myservo.attach(9);
}
void loop() {

  // Pulso de 10us para inicial el modulo
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Convierte el tiempo de recepción del eco en distancia:
  currentDistanceInCm = microsecondsToCentimeters(duration);
  
  if (abs(currentDistanceInCm - previousDistanceInCm) > 2) {
    // Imprime valores por el puerto serie:
    Serial.print(currentDistanceInCm);
    Serial.print("cm");
    Serial.println();
    
    moveServo(currentDistanceInCm);
    
    previousDistanceInCm = currentDistanceInCm;
  }
  delay(50); // Espera 50ms para la siguiente medición (Tiempo mínimo recomendado!!)
}
// Calcula la distancia en pulgadas
long microsecondsToInches(long microseconds) {
  return microseconds /148;
}
// Calcula la distancia en cm
long microsecondsToCentimeters(long microseconds) {
  return microseconds /58;
}

void moveServo(long val) {
  if (val > 80) {
    val = 80;
  }
  servoPos = map(val, 3, 80, 0, 179);
  myservo.write(servoPos);
}



