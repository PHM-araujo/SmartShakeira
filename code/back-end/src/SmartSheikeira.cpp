#include "SmartShakeira.h"
#include "Firebase.h"

SmartShakeira::SmartShakeira(){}

// Conecta o ESP a internet 
void SmartShakeira::Wificonnection(const char * WIFI_SSID, const char * WIFI_PASSWORD){
  
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

void SmartShakeira::Init(){
  Wificonnection("GalaxyS10", "senha123");
  setFirebase();
}

String SmartShakeira::getPedido(){
  return strPedido;
}

bool SmartShakeira::checkPedido(){
  if(Serial.available() > 0){
    strPedido = Serial.readString();
    Serial.println(strPedido);

    if(strPedido == "1") return true;
  }
  return false;
}

bool SmartShakeira::checkCadastro(){

  // Executa até conseguir checar o cadastro
  while(1){
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
      // Pega um valor inteiro do caminho do database test/int 
      if (Firebase.RTDB.getInt(&fbdo, "/users/UserID/Saldo")) {
        if (fbdo.dataType() == "int") {
          saldo = fbdo.intData();
          Serial.println(saldo);

          // Checa se o saldo é suficiente 
          if(saldo > 0){
            Serial.print("Saldo suficiente");
            return true;
          }else{
            Serial.print("Saldo insuficiente");
            return false;
          }
            
        }
      }else {
        Serial.println(fbdo.errorReason());
      }
    }
  }
}

// TODO Testar com motor de passo
void SmartShakeira::makeShake(int speedStep, int stepsPerRevolution, int stepTime){
  // Aciona os motores de passo para abrir comporta
  myStepper.setSpeed(speedStep); 

  myStepper.step(2*stepsPerRevolution);
  delay(stepTime);

  myStepper.step(-2*stepsPerRevolution);
  delay(stepTime);
}