#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "base64.h"

// WiFi Credentials
const char* ssid = "************g";
const char* password = "**********7";

// Firebase Configuration
#define FIREBASE_API_KEY "AIzaSy******************"
#define FIREBASE_DATABASE_URL "https://eco-bin-36651-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Gemini API Configuration
const char* gemini_api_key = "AIzaS***********";
const char* gemini_endpoint = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=";

// Firebase Objects
FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;

unsigned long previousMillis = 0;
const unsigned long interval = 10000; // Run every 10 seconds
bool isProcessing = false;
String lastDetectionResult = ""; // Store last result to avoid duplicates

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  Serial.println("\nESP32-CAM Tea Leaf Disease Detection");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");

  // Initialize Firebase
  firebaseConfig.api_key = FIREBASE_API_KEY;
  firebaseConfig.database_url = FIREBASE_DATABASE_URL;
  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);

  Serial.println("📷 Initializing Camera...");

  // Camera Setup
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sccb_sda = 26;
  config.pin_sccb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_CIF;
    config.jpeg_quality = 10;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("❌ Camera init failed with error 0x%x\n", err);
    ESP.restart();
  }
  Serial.println("✅ Camera Initialized!");
}

// Convert Image to Base64
String encodeImageBase64(camera_fb_t *fb) {
  return base64::encode(fb->buf, fb->len);
}

// Parse API Response
String parseGeminiResponse(String response) {
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.print("❌ JSON Parse Error: ");
    Serial.println(error.c_str());
    return "Error";
  }

  if (doc.containsKey("candidates")) {
    return String(doc["candidates"][0]["content"]["parts"][0]["text"].as<const char*>());
  }

  return "Error";
}

// Upload Result to Firebase
void sendToFirebase(String disease) {
    String resultToUpload = "Healthy";
    if (disease != "Healthy" && disease != "Error" && disease != "API Error") {
        resultToUpload = disease;
    }

    if (resultToUpload != lastDetectionResult && Firebase.ready()) {
        String path = "/tea_leaves/detection_result";  // Firebase path
        String finalResult = "Detection Result: " + resultToUpload; // Format result

        Serial.println("📤 Uploading to Firebase..."); // Serial monitor log

        if (Firebase.RTDB.setString(&firebaseData, path, finalResult)) {
            Serial.println("✅ Firebase Upload Successful: " + finalResult);
            lastDetectionResult = resultToUpload; // Store last uploaded value
        } else {
            Serial.println("❌ Firebase Upload Failed!");
            Serial.println("🔴 Error: " + firebaseData.errorReason()); // Print Firebase error
        }
    }
}

// Capture & Analyze Image
String detectDisease() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("❌ Camera Capture Failed");
    return "Error";
  }

  String imageBase64 = encodeImageBase64(fb);
  esp_camera_fb_return(fb);

  HTTPClient http;
  String fullEndpoint = String(gemini_endpoint) + gemini_api_key;
  http.begin(fullEndpoint);
  http.addHeader("Content-Type", "application/json");
  http.setTimeout(10000); // Increased timeout to 10s

  String payload = "{"
    "\"contents\": [{"
      "\"parts\": ["
        "{ \"text\": \"Analyze this tea leaf image for diseases. Respond with only the disease name or 'Healthy'.\" },"
        "{ \"inline_data\": {"
          "\"mime_type\": \"image/jpeg\","
          "\"data\": \"" + imageBase64 + "\""
        "} }"
      "]"
    "}]}"
  ;

  Serial.println("📤 Sending Image to Gemini API...");
  int httpCode = http.POST(payload);
  String response = http.getString();

  if (httpCode == HTTP_CODE_OK) {
    Serial.println("✅ API Response: " + response);
    return parseGeminiResponse(response);
  } else {
    Serial.printf("❌ HTTP Error: %d\n", httpCode);
    Serial.println("🔴 Response: " + response);
    return "API Error";
  }

  http.end();
}

// Main Loop
void loop() {
  if (!isProcessing && millis() - previousMillis >= interval) {
    isProcessing = true;
    Serial.println("\n🔄 Starting Detection Cycle...");

    String result = detectDisease();
    Serial.println("🔍 Detection Result: " + result);

    sendToFirebase(result);

    previousMillis = millis();
    isProcessing = false;
    Serial.println("✅ Detection Cycle Completed\n");
  }
}
