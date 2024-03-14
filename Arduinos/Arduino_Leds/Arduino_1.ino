const int LED_RED = 12;
const int LED_YELLOW = 13;
const int LED_GREEN = 11;
bool redOn = false;
bool yellowOn = false;
bool greenOn = false;
bool blinking = false;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char opt = Serial.read();
    switch(opt) {
      case '1':
        greenOn = !greenOn;
        digitalWrite(LED_GREEN, greenOn ? HIGH : LOW);
        break;
      case '2':
        redOn = !redOn;
        digitalWrite(LED_RED, redOn ? HIGH : LOW);
        break;
      case '3':
        yellowOn = !yellowOn;
        digitalWrite(LED_YELLOW, yellowOn ? HIGH : LOW);
        break;
      case '4':
        if (blinking) {
          stopBlinking();
        } else {
          startBlinking();
        }
        break;
      case '5':
        turnOffAllLights();
        break;
      case '6': // Nuevo comando para mostrar el menú
        printMenu();
        break;
      default:
        break;
    }
  }
}

void startBlinking() {
  blinking = true;
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    delay(500);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    delay(500);
  }
}

void stopBlinking() {
  blinking = false;
}

void turnOffAllLights() {
  greenOn = false;
  redOn = false;
  yellowOn = false;
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
}

void printMenu() {
  Serial.println("::: MENU :::");
  Serial.println("[1]. Turn on/off green LED");
  Serial.println("[2]. Turn on/off red LED");
  Serial.println("[3]. Turn on/off yellow LED");
  Serial.println("[4]. Toggle blinking all LEDs");
  Serial.println("[5]. Turn off all LEDs");
  Serial.println("[6]. Print menu");
  Serial.println("Please enter your option:");
}