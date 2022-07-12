#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Pin Sensor
#define pHpin_1 A7
#define pHpin_2 A6
#define suhuPin_1 A5
#define suhuPin_2 A4

//Arduino & Wemos
SoftwareSerial ganti (2,3);
SoftwareSerial nilai (4,5);

//Deklarasi Sensor Suhu
OneWire oneWire_1(suhuPin_1);
OneWire oneWire_2(suhuPin_2);
DallasTemperature sensor_1(&oneWire_1);
DallasTemperature sensor_2(&oneWire_2);

int samples = 10;
float adc_resolution = 1024.0;
float tegangan, hasil;
float ph_1, ph_2;
float suhu_1, suhu_2;
int pilihan = 1;

//Fungsi Hitung PH
float hitungPH_1 (){
  int measuring=0;
  for (int i = 0; i < samples; i++){
    measuring += analogRead(pHpin_1);
  }
  tegangan = 5 / adc_resolution * measuring/samples;
  ph_1 = -5.9565*tegangan + 21.827;
  return ph_1;
}
float hitungPH_2 (){
  int measuring=0;
  for (int i = 0; i < samples; i++){
    measuring += analogRead(pHpin_2);
  }
  tegangan = 5 / adc_resolution * measuring/samples;
  ph_2 = -5.8299*tegangan + 21.5557;
  return ph_2;
}

void setup()
{
  Serial.begin(9600);
  ganti.begin(9600);
  nilai.begin(9600);
  sensor_1.begin();
  sensor_2.begin();
}

void loop()
{
  static unsigned long timepoint = millis();
  if(millis()-timepoint>500U){
    timepoint = millis();

    //Kirim Data
    Serial.println(pilihan);
    ganti.println(pilihan);
    if(data == 1){
      hasil = hitungPH_1();
      pilihan = 2;
    }
    else if(pilihan == 2){
      hasil = hitungPH_2();
      pilihan = 3;
    }
    else if(pilihan == 3){
      sensor_1.requestTemperatures();
      hasil = sensor_1.getTempCByIndex(00);
      pilihan = 4;
    }
    else if(pilihan == 4){
      sensor_2.requestTemperatures();
      hasil = sensor_2.getTempCByIndex(00);
      pilihan = 1;
    } 
    Serial.println(hasil);
    nilai.println(hasil);
  }
}
