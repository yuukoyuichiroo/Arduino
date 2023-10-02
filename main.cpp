#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Define the analog pin for the MQ-2 sensor
const int mq2Pin = 36; // Adjust based on your wiring

// API endpoint for sending alerts
const String alertApiEndpoint = "https://api.fonnte.com/send";

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  // Initialize MQ-2 sensor
  pinMode(mq2Pin, INPUT);
}

void loop() {
  // Read the analog value from the MQ-2 sensor
  int sensorValue = analogRead(mq2Pin);

  // If smoke or fire is detected (analog value crosses a threshold), send an alert
  if (sensorValue > 500) {
    Serial.println("Fire or Smoke Detected!");

 

    // Send an HTTP alert to the specified URL
    sendAlertToServer("Fire or Smoke Detected!");
  }

  delay(1000); // Check the sensor periodically
}

// Function to send an HTTP alert to a server
void sendAlertToServer(String message) {
  HTTPClient http;
  String base_url = alertApiEndpoint;
  String target = "081398065915";
  String encodedMessage = "Berak%20berama";
  String token = "DRgTpk6#u0_o0I_AtG@X";

  // Construct the full URL with query parameters
  String url = base_url + "?target=" + target + "&message=" + encodedMessage + "&token=" + token;
  
  http.begin(url);

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.println("Alert Sent to API: " + message);
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
