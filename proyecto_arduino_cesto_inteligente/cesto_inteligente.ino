 #include <Servo.h>

Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;

long duration;
int distanceThreshold = 54; // Umbral de distancia para activar el servo (ajustar según sea necesario)
boolean isHandNear = false;

void setup() {
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0); // Servo en posición inicial
  delay(1000); // Espera 1 segundo para estabilizar
  Serial.begin(9600); // Iniciar comunicación serial para depuración (opcional)
}

void loop() {
  // Medir la distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Calcular la distancia en cm
  
  // Comprobar si una mano está cerca
  if (distance < distanceThreshold && !isHandNear) {
    // Activar el servo
    servo.write(180); // Ángulo de apertura deseado
    isHandNear = true;
    Serial.println("Basurero abierto");
  }
  
  // Comprobar si la mano se ha alejado
  if (distance >= distanceThreshold && isHandNear) {
    // Volver a la posición inicial
    servo.write(0); // Ángulo de posición inicial
    isHandNear = false;
    Serial.println("Basurero cerrado");
  }
  
  delay(100); // Pequeña pausa para estabilidad
}
