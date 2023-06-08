#include <Arduino.h>
#include <WiFi.h>
#include <esp32-hal-ledc.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

const int sensor_pin = 33;  /* Soil moisture sensor O/P pin */
const int relej_pin = 17;
int vlaga=0;

#define WIFI_SSID "Amna"
#define WIFI_PASSWORD "sifrasifra"
#define API_KEY "AIzaSyCDF379WGtauZqSck2o4O8qoHTdQGUNo4A"
#define DATABASE_URL "arduino-222cd-default-rtdb.europe-west1.firebasedatabase.app/" 


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool signupOK = true;

 
void setup(){
  Serial.begin(115200);
  pinMode(sensor_pin,INPUT);

  analogReadResolution(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
  }

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);  
}


void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
   sendDataPrevMillis = millis();
   vlaga=map(analogRead(sensor_pin),1023,0,0,100);
Serial.print("Vlaga koju ocitava senzor:");
Serial.println(vlaga);

Firebase.RTDB.setInt(&fbdo,"PWS/Vlaga",vlaga);
  vlaga=fbdo.floatData();

  delay(5000);
  }
}


