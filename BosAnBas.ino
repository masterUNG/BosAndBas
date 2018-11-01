#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "bosanbas.firebaseio.com"
#define FIREBASE_AUTH "4imrg8KkukIxQnrghJ6MO4DB73nxgnvTv6aaTvZz"

// Config connect WiFi
#define WIFI_SSID "MastreEWTC_2.4G"
#define WIFI_PASSWORD "12345abcde"

int i = 0;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

//  For Humidity
  Firebase.setInt("Humidity", i);
  if (Firebase.failed()) {
    Serial.print("set /Humidity failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("set /Humidity to ");
  Serial.println(Firebase.getInt("Humidity"));

//  For Temp
  Firebase.setInt("Temp", i);
  if (Firebase.failed()) {
    Serial.print("set /Temp failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("set /Temp to ");
  Serial.println(Firebase.getInt("Temp"));

  i++;
  delay(500);
}
