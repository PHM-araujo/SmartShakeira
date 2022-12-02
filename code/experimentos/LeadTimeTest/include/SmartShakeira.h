#ifndef SMARTSHAKEIRA
#define SMARTSHAKEIRA

#include <WiFi.h> 
#include "Stepper.h"



class SmartShakeira{
    private:

        // Variáveis do motor de passo 
        Stepper myStepper = Stepper(2048, 19, 5, 18, 17);


        // Variáveis dos pedidos
        String strPedido = "";
        int saldo = -1;
        int requisicao = 0;

        // Variaveis dos testes
        int countConfiabiliade = 0;
        unsigned long leadTime = 0;

        // Variaveis do motor
        int pwmA = 3;
        int in1A = 21;
        int in2A = 4;

    public:
        SmartShakeira();
        void Wificonnection(const char * WIFI_SSID, const char * WIFI_PASSWORD);
        void Init();

        //* Metodos get
        String getPedido();

        //* Se houver a requisição de um pedido retorna True
        bool checkPedido();

        //* Checa se existe um cadastro válido no DB
        bool checkCadastro();

        //* Aciona os motores para iniciar o preparo do shake
        //@param
        // . SpeedStepp = velocidade do motor de passo
        // . stepsPerRevolution = Passos por revolução 
        // . stepTime = Tempo que o motor fica acionado
        void makeShake(int speedStepp, int stepsPerRevolution, int stepTime);

        void resetValues();
};

#endif