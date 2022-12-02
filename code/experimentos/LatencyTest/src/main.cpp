#include <Arduino.h>
#include "Wifi.h"
#include "Firebase.h"

unsigned long latencyTime = millis();
int check = 1;

String strValue = "";
String strValue2 = "";

void setup() {
  Serial.begin(115200);

  Wificonnection("Wifi_Id", "Senha");
  
  setFirebase();
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Pega um valor inteiro do caminho do database test/int 
    if (Firebase.RTDB.getString(&fbdo, "/Cadastro")) {

      if (fbdo.dataType() == "string") {
        strValue = fbdo.stringData();

        if(check){
          check = 0;
          latencyTime = millis() - latencyTime;
          Serial.print("Tempo de latência: ");
          Serial.println(latencyTime);
        }

        Serial.println(strValue);
    }

    }else {

      Serial.println(fbdo.errorReason());

    }
  }
}
