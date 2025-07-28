#define BLYNK_TEMPLATE_ID "TMPL3WVm2DlWD"
#define BLYNK_TEMPLATE_NAME "Water Tap Automation"
#define BLYNK_AUTH_TOKEN "Dh4W6AU8y03j-GA0i4cdzcVKQ5vF2skJ"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

#define RELAY_PIN D4      
#define IR_PIN D5         
#define BUTTON_PIN D6     

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

BlynkTimer timer;
unsigned long manualStart = 0;
bool manualActive = false;
bool blynkOverride = false;

void setup() {
  Serial.begin(115200);

  // relay stays OFF at startup
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // OLED init
  Wire.begin(D3, D1);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(F("Tap System"));
  display.display();
  delay(1000);

  // Non-blocking WiFi + Blynk
  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);
  // (don’t use Blynk.begin!)
  
  timer.setInterval(500L, sendStatusToBlynk);
}

void loop() {
  Blynk.run();        // runs if Wi-Fi connects
  timer.run();        

  bool handDetected = (digitalRead(IR_PIN) == LOW);
  bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

  // manual button
  if (buttonPressed && !manualActive) {
    manualActive = true;
    manualStart = millis();
    blynkOverride = false;
    digitalWrite(RELAY_PIN, LOW);
  }

  // auto-off after 10s
  if (manualActive && (millis() - manualStart >= 10000)) {
    manualActive = false;
    digitalWrite(RELAY_PIN, HIGH);
  }

  // IR sensor control (only if manual mode off & not blynk override)
  if (!manualActive && !blynkOverride) {
    digitalWrite(RELAY_PIN, handDetected ? LOW : HIGH);
  }

  // OLED update
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(F("Water: "));
  display.println(digitalRead(RELAY_PIN) == LOW ? F("ON") : F("OFF"));
  display.display();
}

// --- Blynk button (V1) ---
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value == 1) {
    blynkOverride = true;
    manualActive = false;
    digitalWrite(RELAY_PIN, LOW); // ON
  } else {
    blynkOverride = false;
    digitalWrite(RELAY_PIN, HIGH); // OFF
  }
}

// --- send status (V2) ---
void sendStatusToBlynk() {
  Blynk.virtualWrite(V2, digitalRead(RELAY_PIN) == LOW ? 1 : 0);
}
