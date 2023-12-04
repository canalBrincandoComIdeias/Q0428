/*
   Q0428
   AUTOR:   BrincandoComIdeias
   LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
   SKETCH:  Sensor distância IR GY-53
   DATA:    31/01/2019
*/

#include <SoftwareSerial.h>
SoftwareSerial portaSerial(8, 9); // RX, TX

byte dadoSensor[11];
byte contador = 0;
bool dadoRecebido = 0;

void setup() {

  Serial.begin(9600);
  portaSerial.begin(9600);
  portaSerial.listen();
  delay(10);

  // ENVIANDO INSTRUÇÃO PARA TIPO DE MEDIDA CONTÍNUA
  portaSerial.write(0XA5); portaSerial.write(0X45); portaSerial.write(0XEA);

  
  // ENVIANDO INSTRUÇÃO PARA MODO DE MEDIDA LONGA DISTÂNCIA
  portaSerial.write(0XA5); portaSerial.write(0X50); portaSerial.write(0XF5);

  // ENVIANDO INSTRUÇÃO PARA MODO DE MEDIDA RÁPIDA
  //portaSerial.write(0XA5); portaSerial.write(0X51); portaSerial.write(0XF6);

  // ENVIANDO INSTRUÇÃO PARA MODO DE MEDIDA ALTA PRECISÃO (PADRÃO)
  //portaSerial.write(0XA5); portaSerial.write(0X52); portaSerial.write(0XF7);

  // ENVIANDO INSTRUÇÃO PARA MODO DE MEDIDA GENÉRICO
  //portaSerial.write(0XA5); portaSerial.write(0X53); portaSerial.write(0XF8);
  
  Serial.println("Setup finalizado");
}

void loop() {

  byte checkSum = 0;
  int distancia = 0;
  byte i = 0;

  while (portaSerial.available()) {
    dadoSensor[contador] = portaSerial.read();
    if (contador == 0 && dadoSensor[0] != 0x5A) {
      return;
    }

    contador++;

    if (contador == 8) {
      contador = 0; // ZERA O CONTADOR PARA RECEBER O PRÓXIMO DADO
      dadoRecebido = true;
    }
  }
  
  if (dadoRecebido == true) {

    dadoRecebido = false;
    for ( i = 0; i < 7; i++) {
      checkSum += dadoSensor[i];
    }

    // VERIFICA SE OS DADOS RECEBIDOS SÃO IGUAIS AO CHECKSUM
    if (checkSum == dadoSensor[i] ) {

      distancia = dadoSensor[4] << 8 | dadoSensor[5];

      Serial.print("distancia: ");
      Serial.print( distancia);
      Serial.println(" mm");
    }
  }
}
