/*
  Capitulo 40 de Arduino desde cero en Español.
  Programa que obtiene el UID de la tarjeta o llavero del kit RFID RC522, compara con
  valores previos obtenidos de UID y permite acceso con texto en monitor serie de bienvenida
  Cualquier otra tarjeta o llavero no listado muestra texto de No te conozco, es decir,
  acceso denegado. Requiere instalar libreria MFRC522

  Autor: bitwiseAr

*/

#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522

#define RST_PIN  9      // constante para referenciar pin de reset
#define SS_PIN  10      // constante para referenciar pin de slave select
MFRC522 mfrc522(SS_PIN, RST_PIN); // crea objeto mfrc522 enviando pines de slave select y reset


const int elementos_bytes = 4;
byte LecturaUID[elementos_bytes];         // crea array para almacenar el UID leido
byte Usuarios[][elementos_bytes] = { // UID de los usuarios registrados
  {0x7A, 0x71, 0x96, 0x3A},
  {0x09, 0xAE, 0xCC, 0x11},
  {0xBC, 0x57, 0x21, 0x22}
};

int Led_Rojo = 3;
int Led_Verde = 4;
int Led_Azul= 5;
void setup() {
  Serial.begin(9600);     // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();        // inicializa bus SPI
  pinMode(Led_Rojo, OUTPUT);
  pinMode(Led_Verde, OUTPUT);
  pinMode(Led_Azul, OUTPUT);
  mfrc522.PCD_Init();     // inicializa modulo lector
}

void loop() {
  int Elementos = sizeof(Usuarios) / elementos_bytes;
  bool Autenticado = false;

  //elementos_bytes

  if ( ! mfrc522.PICC_IsNewCardPresent())   // si no hay una tarjeta presente
    return;           // retorna al loop esperando por una tarjeta

  if ( ! mfrc522.PICC_ReadCardSerial())     // si no puede obtener datos de la tarjeta
    return;           // retorna al loop esperando por otra tarjeta

  for (byte i = 0; i < mfrc522.uid.size; i++) { // bucle recorre de a un byte por vez el UID     
    LecturaUID[i] = mfrc522.uid.uidByte[i];   // almacena en array el byte del UID leido
  }

  for (int i = 0; i < Elementos; i++ ) {
    for (int j = 0; j < elementos_bytes; j++) {
      if (LecturaUID[j] != Usuarios[i][j])
        Autenticado = false;
      else{
        Autenticado = true;
        break;
        }
    }
    if (Autenticado == true)
      break;
  }
  if (Autenticado == true){
    Serial.println("REGISTRADO");
    digitalWrite(Led_Rojo, LOW);
    digitalWrite(Led_Verde, HIGH);
    delay(1000);
    digitalWrite(Led_Rojo,LOW );
    digitalWrite(Led_Verde,LOW );
    
    lectura();    
  }
  else{
    Serial.println("NO REGISTRADO");
    digitalWrite(Led_Rojo,HIGH );
    digitalWrite(Led_Verde,LOW );
    delay(1000);
    digitalWrite(Led_Rojo,LOW );
    digitalWrite(Led_Verde,LOW );
    }

   


  mfrc522.PICC_HaltA();     // detiene comunicacion con tarjeta
}

void lectura(){
  while (true){
    if (Serial.available()>0) 
   {        
      char option = Serial.read();
      if (option == '9')
      {      
            digitalWrite(Led_Azul, HIGH);
            delay(100);
            digitalWrite(Led_Azul, LOW);
            delay(100);
            digitalWrite(Led_Azul, HIGH);
            delay(100);
            digitalWrite(Led_Azul, LOW);
            delay(100);
            digitalWrite(Led_Azul, HIGH);
            delay(100);
            digitalWrite(Led_Azul, LOW);
            delay(100);
            digitalWrite(Led_Azul, HIGH);
            delay(100);
            digitalWrite(Led_Azul, LOW);
            delay(100);
            digitalWrite(Led_Azul, HIGH);
            delay(300);
            digitalWrite(Led_Azul, LOW);            
            break;
         }
       else
        break;
      }
  }
  
}
