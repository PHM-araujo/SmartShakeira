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

  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
}

String SmartShakeira::getPedido(){
  return strPedido;
}

bool SmartShakeira::checkPedido(){
  // Checa se houve uma requisição no sistema fisico
  if(Serial.available() > 0){
    strPedido = Serial.readString();
    Serial.println(strPedido);

    if(strPedido == "1") return true;
  }

  // Checa se um aplicativo fez uma requisição
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    Serial.println("Checando mudança");
    sendDataPrevMillis = millis();
    // Pega um valor inteiro do caminho do database test/int 
    if (Firebase.RTDB.getInt(&fbdo, "/users/80a9fd301bc2ef2066c6bf4009d0d96b0e37b7e1/Preparar")) {
      if (fbdo.dataType() == "int") {
        requisicao = fbdo.intData();
        Serial.println(requisicao);
        // Checa se o saldo é suficiente 
        if(requisicao == 1){
          leadTime = millis();
          Serial.println("Requisicao do aplicativo");

          if (Firebase.RTDB.setInt(&fbdo, "/users/80a9fd301bc2ef2066c6bf4009d0d96b0e37b7e1/Preparar", 0)){
            Serial.println("PASSED");
          }else {
            Serial.println("FAILED");
          }
          return true;
        }
          
      }
    }else {
      Serial.println(fbdo.errorReason());
    }
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
          countConfiabiliade++;
          Serial.print("Número de testes: ");
          Serial.println(countConfiabiliade);
          saldo = fbdo.intData();
          Serial.println(saldo);

          // Checa se o saldo é suficiente 
          if(saldo > 0){
            Serial.println("Saldo suficiente");
            return true;
          }else{
            Serial.println("Saldo insuficiente");
            return false;
          }
            
        }
      }else {
        Serial.println(fbdo.errorReason());
      }
    }
  }
}

void SmartShakeira::makeShake(int speedStep, int stepsPerRevolution, int stepTime){
  // Aciona os motores de passo para abrir comporta
  myStepper.setSpeed(speedStep); 

  // Abre comporta
  myStepper.step(-2*stepsPerRevolution);
  delay(stepTime);

  // Fecha comporta
  myStepper.step(2*stepsPerRevolution);
  delay(stepTime);

  // Aciona o motor DC pra mexer o shake

  // Configura o motor pra ir pra frente 
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW);

  analogWrite(pwmA, 255);
  delay(10000);

  // Para motores
  analogWrite(pwmA, 0);
  digitalWrite(in1A, LOW); 
	digitalWrite(in2A, LOW); 
  
  // Calcula o tempo de operação
  leadTime = millis() - leadTime;
}

void SmartShakeira::resetValues(){
  strPedido = "";
  saldo = -1;
}