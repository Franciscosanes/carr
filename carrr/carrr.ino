// Definir pines del puente H
const int IN1 = 25, IN2 = 26, ENA = 27, IN3 = 14, IN4 = 12, ENB = 13, EchoPin = 18, TriggerPin = 4;
const int umbralDistancia = 30; // Distancia de detección en cm
const int tiempoGiro = 700; // Tiempo de giro ajustado para un giro más completo

void setup() {
  for (int pin : {IN1, IN2, ENA, IN3, IN4, ENB, TriggerPin}) pinMode(pin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  float distancia = ping();
  
  Serial.print("Distancia: "); Serial.println(distancia);

  if (distancia <= umbralDistancia) {
    mover(IN1, IN2, IN3, IN4, LOW, LOW, LOW, LOW, 0); // Detener el carro
    delay(100); // Pausa breve para asegurar que el carro esté detenido

    // Esquivar el obstáculo
    int direccion = random(0, 2); // Aleatorio para decidir la dirección del giro
    if (direccion == 0) {
      // Girar izquierda
      mover(IN1, IN2, IN3, IN4, LOW, HIGH, LOW, LOW, 255);
    } else {
      // Girar derecha
      mover(IN1, IN2, IN3, IN4, LOW, LOW, HIGH, LOW, 255);
    }

    delay(tiempoGiro); // Tiempo suficiente para esquivar
    mover(IN1, IN2, IN3, IN4, LOW, LOW, LOW, LOW, 0); // Detener tras el giro
    delay(100); // Pausa antes de avanzar de nuevo
  } else {
    mover(IN1, IN2, IN3, IN4, HIGH, LOW, LOW, HIGH, 255); // Avanzar si no hay obstáculos
  }

  delay(50); // Reducción del tiempo de espera para una detección más rápida
}

float ping() {
  digitalWrite(TriggerPin, LOW); delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH); delayMicroseconds(10); digitalWrite(TriggerPin, LOW);
  return pulseIn(EchoPin, HIGH, 30000) / 58.2; // Retorna la distancia en cm
}

void mover(int in1, int in2, int in3, int in4, int m1a, int m1b, int m2a, int m2b, int velocidad) {
  digitalWrite(in1, m1a); digitalWrite(in2, m1b); analogWrite(ENA, velocidad);
  digitalWrite(in3, m2a); digitalWrite(in4, m2b); analogWrite(ENB, velocidad);
}
