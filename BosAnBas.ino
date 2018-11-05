#include <DHT.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "bosanbas.firebaseio.com"
#define FIREBASE_AUTH "4imrg8KkukIxQnrghJ6MO4DB73nxgnvTv6aaTvZz"

// Config connect WiFi
#define WIFI_SSID "MastreEWTC_2.4G"
#define WIFI_PASSWORD "12345abcde"

//About DHT11
//#include <DHT.h>                // Include DHT sensor library
#define DHTTYPE DHT11           // Define type of sensor 
#define DHTPIN  D4              // Define connected pin

DHT dht(DHTPIN, DHTTYPE, 15);   // Initial DHT sensor

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

  dht.begin();                  // Start DHT sensor operation
  
}

void loop() {

  float humid = dht.readHumidity();     // Read humidity data
  float temp = dht.readTemperature();   // Read temperature data
  Serial.print("Humidity = ");       // Send string to serial port.
  Serial.print(humid);            // Send analog value to serial port.
  Serial.print(" Temperature = ");       // Send string to serial port.
  Serial.println(temp);            // Send analog value to serial port.
  delay(300);

//  For Humidity
  Firebase.setInt("Humidity", humid);
  if (Firebase.failed()) {
    Serial.print("set /Humidity failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("set /Humidity to ");
  Serial.println(Firebase.getInt("Humidity"));

//  For Temporator
  Firebase.setInt("Temp", temp);
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
