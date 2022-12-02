#include "Firebase_ESP_Client.h" // Iinterface entre firebase e ESP
#include "addons/TokenHelper.h"   //Provide the token generation process info.
#include "addons/RTDBHelper.h"    //Provide the RTDB payload printing info and other helper functions.

// Insert Firebase project API Key
#define API_KEY "AIzaSyBgQoHaucClHj4wIdEk_3Y9lthRfa1flYA"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://dbsmartshaikeira-default-rtdb.firebaseio.com" 

// Define o objeto firebase 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


void setFirebase(){
    // Configiração do Firebase 
    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", "")){
        Serial.println("ok");
        signupOK = true;
    }
    else{
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    //-----------------------------------
}