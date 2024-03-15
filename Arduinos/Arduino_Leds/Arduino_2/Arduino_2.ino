const int LM35_PIN = A0;      // Pin analógico donde está conectado el sensor LM35
const int LED_PIN = 13;       // Pin digital donde está conectado el LED
const int VENTILADOR_PIN = 12; // Pin digital donde está conectado el ventilador (motor)

void setup() {
  pinMode(LM35_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(VENTILADOR_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lee la temperatura del sensor LM35
// Lectura de temperatura
  int temperature=(-40+0.488155*(analogRead(LM35_PIN)-20)); 
  // Mostrar la temperatura en el Monitor Serie
  // Imprime la temperatura en el puerto serial
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Validación 1: Si la temperatura es inferior a 5 °C
  if (temperature <= 5) {
    blinkLED(500); // El LED parpadea con un retardo de 0.5 segundos
    digitalWrite(VENTILADOR_PIN, LOW); // El ventilador está apagado
  } 
  // Validación 2: Si la temperatura está entre 6 °C y 25 °C
  else if (temperature >= 6 && temperature <= 25) {
    digitalWrite(LED_PIN, LOW); // El LED está apagado
    digitalWrite(VENTILADOR_PIN, LOW); // El ventilador está apagado
  } 
  // Validación 3: Si la temperatura es mayor a 25 °C
  else if (temperature > 25) {
    digitalWrite(LED_PIN, HIGH); // El LED se enciende
    digitalWrite(VENTILADOR_PIN, HIGH); // El ventilador se enciende
  }

  delay(1000); // Espera un segundo antes de la próxima lectura
}

// Función para leer la temperatura del sensor LM35


// Función para hacer parpadear el LED
void blinkLED(int interval) {
  digitalWrite(LED_PIN, HIGH);
  delay(interval);
  digitalWrite(LED_PIN, LOW);
  delay(interval);
}