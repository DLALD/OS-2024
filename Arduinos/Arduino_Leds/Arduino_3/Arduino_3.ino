#include <LiquidCrystal.h>

const int LM35_PIN = A0;      // Pin analógico donde está conectado el sensor LM35
const int LED_PIN = 13;       // Pin digital donde está conectado el LED
const int VENTILADOR_PIN = 10; // Pin digital donde está conectado el ventilador

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup() {
  lcd_1.begin(16, 2); // Configura el número de columnas y filas en la pantalla LCD
  pinMode(LM35_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(VENTILADOR_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Lee la temperatura del sensor LM35
  int temperature = (-40 + 0.488155 * (analogRead(LM35_PIN) - 20));

  // Imprime la temperatura en el puerto serial
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Visualiza la temperatura en la pantalla LCD
  lcd_1.setCursor(0, 0);
  lcd_1.print("Temp: ");
  lcd_1.print(temperature);
  lcd_1.print(" C");

  // Validación 1: Si la temperatura es menor o igual a 10 °C
  if (temperature <= 10) {
    blinkLED(500); // El LED parpadea con un delay de medio segundo
    digitalWrite(VENTILADOR_PIN, LOW); // El ventilador está apagado
  } 
  // Validación 2: Si la temperatura está entre 11 °C y 25 °C
  else if (temperature > 10 && temperature <= 25) {
    digitalWrite(LED_PIN, LOW); // El LED está apagado
    digitalWrite(VENTILADOR_PIN, LOW); // El ventilador está apagado
  } 
  // Validación 3: Si la temperatura es mayor o igual a 26 °C
  else if (temperature >= 26) {
    digitalWrite(LED_PIN, HIGH); // El LED está encendido
    digitalWrite(VENTILADOR_PIN, HIGH); // El ventilador está encendido
  }

  delay(1000); // Espera un segundo antes de la próxima lectura
}

// Función para hacer parpadear el LED
void blinkLED(int interval) {
  digitalWrite(LED_PIN, HIGH);
  delay(interval);
  digitalWrite(LED_PIN, LOW);
  delay(interval);
}

