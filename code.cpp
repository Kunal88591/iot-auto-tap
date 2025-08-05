#define BLYNK_TEMPLATE_ID "TMPL3nJ-rkAcd"
#define BLYNK_TEMPLATE_NAME "Water Tap Automation"
#define BLYNK_AUTH_TOKEN "eojgsswj3vbuQ4RcDexQd7yi-y6B7m8W"


// ----- Blynk Configuration -----
//#define BLYNK_TEMPLATE_ID "TMPL3xs_CxO-T"
//#define BLYNK_TEMPLATE_NAME "Water Tap Automation"
//#define BLYNK_AUTH_TOKEN "-8jaX_KRi3Ql54eGvy3WNGENPOb2P58O"
//#define BLYNK_PRINT Serial

// ----- Libraries -----
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// ----- WiFi Credentials -----
char ssid[] = "Dizzy_space";
char pass[] = "osvz1405";

// ----- SinricPro Configuration -----
#define APP_KEY     "d86b6333-f8e9-40fa-a78c-cc76e5f12207"
#define APP_SECRET  "60a8e4cc-7dbe-40bb-85ec-a0b76228ecfd-f5ed1f6d-5e71-4835-8c1f-324f07fd70d9"
#define DEVICE_ID   "6889f134ddd2551252ba9a4a"

// ----- Pin Definitions -----
#define RELAY_PIN D4
#define IR_PIN D5
#define BUTTON_PIN D6
#define FLOW_SENSOR_PIN D2

#define RELAY_ON HIGH
#define RELAY_OFF LOW

// ----- OLED Display -----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----- Global Variables -----
volatile int flowPulseCount = 0;
float calibrationFactor = 4.5;
float flowRate = 0;
float totalLiters = 0;
unsigned long lastFlowCalc = 0;

BlynkTimer timer;
bool manualActive = false;
bool blynkOverride = false;
bool sinricOverride = false;

unsigned long manualStart = 0;
int countdown = 0;
int runDuration = 20;

// ----- Interrupt Service Routine -----
void IRAM_ATTR flowPulse() { 
  flowPulseCount++; 
}

// ----- Voice Control Handler -----
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Voice command: %s\n", state ? "ON" : "OFF");

  if (state) {
    sinricOverride = true;
    blynkOverride = false;
    manualActive = false;
    digitalWrite(RELAY_PIN, RELAY_ON);
    countdown = runDuration;
    updateBlynkWidgets(true);
    Serial.printf("Voice ON for %d sec\n", countdown);
  } else {
    sinricOverride = false;
    digitalWrite(RELAY_PIN, RELAY_OFF);
    countdown = 0;
    updateBlynkWidgets(false);
    Serial.println("Voice OFF");
  }
  return true;
}

// ----- Widget Update Function -----
void updateBlynkWidgets(bool state) {
  if (!Blynk.connected()) return;

  Blynk.virtualWrite(V2, state ? "💧 Water ON" : "🚱 Water OFF");  
  Blynk.virtualWrite(V3, digitalRead(IR_PIN) ? "🤚 No Hand" : "✋ Hand Detected");

  // ✅ These will always send latest values
  Blynk.virtualWrite(V4, countdown);    
  Blynk.virtualWrite(V5, flowRate);      // ✅ Gauge
  Blynk.virtualWrite(V6, totalLiters);   // ✅ Total Liters

  // Debug log
  Serial.print("📤 Sent to Blynk → FlowRate: ");
  Serial.print(flowRate);
  Serial.print(" L/min | Total: ");
  Serial.print(totalLiters);
  Serial.print(" L | Countdown: ");
  Serial.println(countdown);
}

// ----- Network Connection -----
void connectNetwork() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 8080);
    Blynk.connect(3000); // 3sec timeout
    if (Blynk.connected()) {
      Serial.println("✅ Blynk connected!");
      Blynk.syncAll();
    }
  }
}

// ----- Setup Function -----
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Initialize hardware
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);
  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), flowPulse, RISING);

  // Initialize OLED
  Wire.begin(D3, D1);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed!");
    while(1);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("System OK");
  display.display();
  delay(2000);

  // Connect to network
  connectNetwork();
  
  // ✅ Timer to refresh Blynk every second
  timer.setInterval(1000L, []() {
    updateBlynkWidgets(digitalRead(RELAY_PIN));
  });

  // Initialize SinricPro
  SinricProSwitch &mySwitch = SinricPro[DEVICE_ID];
  mySwitch.onPowerState(onPowerState);
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// ----- Main Loop -----
void loop() {
  Blynk.run();
  timer.run();
  SinricPro.handle();

  // Network watchdog
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {
    lastCheck = millis();
    if (!Blynk.connected()) {
      Serial.println("Reconnecting...");
      connectNetwork();
    }
  }

  // Manual button control
  if (digitalRead(BUTTON_PIN) == LOW && !manualActive) {
    manualActive = true;
    blynkOverride = false;
    sinricOverride = false;
    manualStart = millis();
    digitalWrite(RELAY_PIN, RELAY_ON);
    updateBlynkWidgets(true);
    Serial.println("Manual ON (10s)");
  }

  // Manual timeout
  if (manualActive && (millis() - manualStart >= 10000)) {
    manualActive = false;
    digitalWrite(RELAY_PIN, RELAY_OFF);
    updateBlynkWidgets(false);
    Serial.println("Manual OFF");
  }

  // IR sensor control
  if (!manualActive && !blynkOverride && !sinricOverride && countdown == 0) {
    digitalWrite(RELAY_PIN, digitalRead(IR_PIN) ? RELAY_OFF : RELAY_ON);
  }

  // Countdown timer
  if (countdown > 0) {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate >= 1000) {
      lastUpdate = millis();
      countdown--;
      Blynk.virtualWrite(V4, countdown);
      if (countdown == 0) {
        digitalWrite(RELAY_PIN, RELAY_OFF);
        blynkOverride = false;
        sinricOverride = false;
        updateBlynkWidgets(false);
      }
    }
  }

  // ✅ Flow sensor calculation every second
  if (millis() - lastFlowCalc > 1000) {
    lastFlowCalc = millis();
    flowRate = (flowPulseCount / calibrationFactor);
    totalLiters += (flowRate / 60.0);
    flowPulseCount = 0;
    
    // ✅ Print flow data every second
    Serial.print("🌊 Flow: ");
    Serial.print(flowRate);
    Serial.print(" L/min | 💧 Total: ");
    Serial.println(totalLiters);

    // ✅ Update OLED
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,10);
    display.print("Water: ");
    display.println(digitalRead(RELAY_PIN) ? "ON" : "OFF");
    
    display.setTextSize(1);
    display.setCursor(0,30);
    display.print("Flow: ");
    display.print(flowRate, 1);
    display.print(" L/m");
    
    display.setCursor(0,45);
    display.print("Total: ");
    display.print(totalLiters, 1);
    display.print(" L");
    
    if (countdown > 0) {
      display.setCursor(0,55);
      display.print("OFF in: ");
      display.print(countdown);
      display.print("s");
    }
    display.display();
  }
}

// ----- Blynk Button Handler -----
BLYNK_WRITE(V1) {
  int value = param.asInt();
  Serial.printf("Blynk button: %d\n", value);
  
  if (value) {
    blynkOverride = true;
    sinricOverride = false;
    manualActive = false;
    digitalWrite(RELAY_PIN, RELAY_ON);
    countdown = runDuration;
    updateBlynkWidgets(true);
  } else {
    blynkOverride = false;
    digitalWrite(RELAY_PIN, RELAY_OFF);
    countdown = 0;
    updateBlynkWidgets(false);
  }
}

// ----- Blynk Slider Handler -----
BLYNK_WRITE(V7) {
  runDuration = param.asInt();
  runDuration = constrain(runDuration, 5, 120);
  Serial.printf("Duration set: %ds\n", runDuration);
  
  if (digitalRead(RELAY_PIN)) {
    countdown = runDuration;
    Blynk.virtualWrite(V4, countdown);
  }
}

// ----- Blynk Connection Handler -----
BLYNK_CONNECTED() {
  Serial.println("Blynk connected!");
  Blynk.syncAll();
}
