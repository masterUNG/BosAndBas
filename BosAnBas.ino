//Library Conncected Wifi
#include <ESP8266WiFi.h>

//Library Connecred Firebase
#include <FirebaseArduino.h>

//Library Connected DHT
#include <DHT.h>

// Config Firebase Token
#define FIREBASE_HOST "bosanbas.firebaseio.com"
#define FIREBASE_AUTH "4imrg8KkukIxQnrghJ6MO4DB73nxgnvTv6aaTvZz"

// Config connect Router WiFi
#define WIFI_SSID "MastreEWTC_2.4G"
#define WIFI_PASSWORD "12345abcde"

//About DHT11
#define DHTTYPE DHT11           // Define type of sensor 
#define DHTPIN  D4              // Define connected pin

DHT dht(DHTPIN, DHTTYPE, 15);   // Initial DHT sensor


void setup() {
  
  Serial.begin(9600);

// connect to wifi.
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //  Start Connected Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Start DHT sensor operation
  dht.begin();                  
  
} // Setting

void loop() {

// Calculate Humidity and Temp
  float humid = dht.readHumidity();     // Read humidity data
  float temp = dht.readTemperature();   // Read temperature data
  Serial.print("Humidity = ");       // Send string to serial port.
  Serial.print(humid);            // Send analog value to serial port.
  Serial.print(" Temperature = ");       // Send string to serial port.
  Serial.println(temp);            // Send analog value to serial port.
  delay(500);

//  For Firebase Receive Humidity
  if (humid <= 100) {

    Firebase.setInt("Humidity", humid);
  if (Firebase.failed()) {
    Serial.print("set /Humidity failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("set /Humidity to ");
  Serial.println(Firebase.getInt("Humidity"));
    
  }   // if

//  For Firebase Receive Temporator
  if (temp <= 50) {

    Firebase.setInt("Temp", temp);
  if (Firebase.failed()) {
    Serial.print("set /Temp failed:");
    Serial.println(Firebase.error());
    return;
  }
  
  Serial.print("set /Temp to ");
  Serial.println(Firebase.getInt("Temp"));
    
    } // if

  delay(500);
}
