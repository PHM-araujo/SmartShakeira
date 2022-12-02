#include <WiFi.h>                 // Lib de comunicação do ESP  

// Conecta o ESP a internet 
void Wificonnection(const char * WIFI_SSID, const char * WIFI_PASSWORD){
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wifi");

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.print("Conectado com IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}