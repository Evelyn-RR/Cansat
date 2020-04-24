/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
float datos[5];
RF24 radio(9, 10); // CE, CSN 9,10<<<<<<<<<<<<<<<<<<<<<<<<<
const byte addresses[][6] = {"00001", "00002"};

void setup() {
  pinMode(A0,INPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);

  Wire.begin();


 if (!bme.begin(0X76)){
  Serial.println("Sensor BME280 ERRO!");
  while(1); 
  }
}


void loop() {

float Temperatura = bme.readTemperature();
float Pressao = bme.readPressure();
float Altitude = bme.readAltitude(SEALEVELPRESSURE_HPA); 
float Umidade = bme.readHumidity();
  delay(5);

 // radio.stopListening();
  int resValue = analogRead(A0);
  int bateria = map(resValue, 0, 512, 0, 100);
    Serial.print("Bateria  ");
    Serial.print(bateria);
    Serial.println(" %");
    Serial.print("Altitude: "); 
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" Metros"); 
    Serial.print("Pressão: "); 
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" Pa (Pascal)"); 
    Serial.print("Temperatura: "); 
    Serial.print(bme.readTemperature()); 
    Serial.println(" *C "); 
    Serial.print("Umidade = ");
    Serial.print(bme.readHumidity());
    Serial.println("%");
    Serial.print("****************************"); 
    Serial.println(" ");

    
  datos[0]= bateria;
  datos[1]= Altitude;
  datos[2]= Temperatura;
  datos[3]= Pressao;
  datos[4]= Umidade;

  radio.write(datos, sizeof(datos));


 
 // const char text[] = "Senai CANSAT";
 // radio.write(&text, sizeof(text));
 //
 
 delay(500);
}
