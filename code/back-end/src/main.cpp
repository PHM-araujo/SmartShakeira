#include <Arduino.h>
#include "SmartShakeira.h"

SmartShakeira shakeira = SmartShakeira();

void setup() {
  Serial.begin(115200);
  shakeira.Init();
}

void loop(){
  // Checa se há requisição de um pedido 
  if(shakeira.checkPedido()){ 
    
    Serial.println("Iniciei Checagem");

    // Executa até conseguir checar o pedido - Garantir confiabilidade
    if(shakeira.checkCadastro()){

      Serial.println("Inicia preparo do Shake");
      
      // Prepara o shake
      shakeira.makeShake(15, 2048, 1000);

      // Reseta os valores para uma nova checagem 
      shakeira.resetValues();
    }

  }

}