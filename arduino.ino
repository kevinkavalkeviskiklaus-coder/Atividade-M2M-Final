#if defined(ESP32)
  #include <WiFi.h>
  #define LED_PIN 2            // LED interno da maioria das placas ESP32
  #define LED_ON  HIGH
  #define LED_OFF LOW
#else
  #include <ESP8266WiFi.h>
  #define LED_PIN LED_BUILTIN  // GPIO2 no NodeMCU/Wemos
  #define LED_ON  LOW          // LED interno do ESP8266 é ativo em LOW
  #define LED_OFF HIGH
#endif

const char* ssid     = "SEU_WIFI";
const char* password = "SUA_SENHA";

void piscaLed(int vezes, int intervaloMs) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(LED_PIN, LED_ON);
    delay(intervaloMs);
    digitalWrite(LED_PIN, LED_OFF);
    delay(intervaloMs);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_OFF);

  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  piscaLed(5, 200);  // pisca 5 vezes ao conectar
}

void loop() {
  // Se a conexão cair, tenta reconectar e pisca de novo ao voltar
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão perdida. Reconectando...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    Serial.println("Reconectado!");
    piscaLed(5, 200);
  }
  delay(1000);
}
