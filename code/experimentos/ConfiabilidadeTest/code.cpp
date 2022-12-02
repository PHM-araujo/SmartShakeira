bool checkCadastro(){

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