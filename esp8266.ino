#define BLYNK_TEMPLATE_ID "TMPL3t2He2vjE"
#define BLYNK_TEMPLATE_NAME "3 Slot Car Parking System"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "VZ6xneKWbR_Od2OxUj2-8wEFKO8SBe1t"; // Replace with your Blynk Auth Tokenchar ssid[] = "optidock"; // Replace with your WiFi SSID
char pass[] = "qwerty122"; // Replace with your WiFi Password
BlynkTimer timer;
// Virtual Pins for Blynk
#define V_SLOT1 V0
#define V_SLOT2 V1
#define V_SLOT3 V2
#define V_AVAILABLE V3
int slotStatus[3] = {0, 0, 0}; // Store slot status
int totalSlots = 3;
void sendData() {
  if (Serial.available()) {
String data = Serial.readStringUntil(’\n’); // Read Serial data from Arduino
data.trim(); // Remove extra spaces
if (data.length() >= 3) {
int S1 = data.charAt(0) - ’0’;
int S2 = data.charAt(1) - ’0’;
int S3 = data.charAt(2) - ’0’;
// Ensure only valid data is used
if ((S1 >= 0 && S1 <= 1) && (S2 >= 0 && S2 <= 1) && (S3 >= 0 && S3 <= 1)) {
slotStatus[0] = S1;
slotStatus[1] = S2;
slotStatus[2] = S3;
}
int availableSlots = totalSlots - (slotStatus[0] + slotStatus[1] + slotStatus[2]);// Prevent negative values
availableSlots = max(0, availableSlots);
Blynk.virtualWrite(V_SLOT1, slotStatus[0]);
Blynk.virtualWrite(V_SLOT2, slotStatus[1]);
Blynk.virtualWrite(V_SLOT3, slotStatus[2]);
Blynk.virtualWrite(V_AVAILABLE, availableSlots);
}
}
}
void setup() {
Serial.begin(9600);
WiFi.begin(ssid, pass);
Blynk.begin(auth, ssid, pass);
timer.setInterval(300L, sendData); // Reduce interval for faster response
}
void loop() {
Blynk.run();
timer.run();
}
