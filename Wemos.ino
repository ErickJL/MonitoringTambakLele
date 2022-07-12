#define BLYNK_PRINT Serial
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

//WIFI & BLNK
char auth[] = "9gZne1Hg0SLwFFJmmj98qkoHOO-Kpfej";
char ssid[] = "Lele";
char pass[] = "lelelele";

//Arduino & Wemos
SoftwareSerial ganti (2,4);
SoftwareSerial nilai (14,12);

//Pin BLYNK
WidgetLCD Tsuhu_1(V0);
WidgetLCD Tph_1(V1);
WidgetLCD Tsuhu_2(V2);
WidgetLCD Tph_2(V3);

int pilihan;
bool aktif=true;
float suhu_1, suhu_2, ph_1, ph_2;
String infoSuhu_1="Aman", infoPH_1="Aman", infoSuhu_2="Aman", infoPH_2="Aman";

void notif(){
  if(aktif==true){
    Blynk.notify("Tambak Bermasalah");
    aktif=false;
  }
}
void setup()
{
  Serial.begin(9600);
  ganti.begin(9600);
  nilai.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  static unsigned long timepoint = millis();
  //Baca Mode
  ganti.listen();
  if (ganti.available() > 0){
    pilihan = ganti.parseInt();
    Serial.println("Pilihan : ");
    Serial.println(pilihan);
    
    //Baca nilai
    nilai.listen();
    if (nilai.available()){
      if (pilihan == 1){
        ph_1 = nilai.parseFloat();
        Serial.println("nilai ph1: ");
        Serial.println(ph_1);
      }
      else if (pilihan == 2){
        ph_2 = nilai.parseFloat();
        Serial.println("nilai ph2: ");
        Serial.println(ph_2);
      }
      else if (pilihan == 3){
        suhu_1 = nilai.parseFloat();
        Serial.println("nilai suhu1 : ");
        Serial.println(suhu_1);
      }
      else if (pilihan == 4){
        suhu_2 = nilai.parseFloat();
        Serial.println("nilai suhu2: ");
        Serial.println(suhu_2);
      }
    }
  }

  
  //Tampilan BLYNK
  if(millis()-timepoint>1000U){
    timepoint = millis();
    //Suhu tambak 1
    Blynk.virtualWrite(V0, suhu_1);
    Blynk.virtualWrite(V0, infoSuhu_1);
    Tsuhu_1.print(0, 0, "Suhu : ");
    Tsuhu_1.print(7, 0, suhu_1);
    Tsuhu_1.print(0, 1, "Kondisi : ");
    Tsuhu_1.print(10, 1, infoSuhu_1);
    //PH tambak 1
    Blynk.virtualWrite(V1, ph_1);
    Blynk.virtualWrite(V1, infoPH_1);
    Tph_1.print(0, 0, "pH : ");
    Tph_1.print(5, 0, ph_1);
    Tph_1.print(0, 1, "Kondisi : ");
    Tph_1.print(10, 1, infoPH_1);
    //Suhu tambak 2
    Blynk.virtualWrite(V2, suhu_2);
    Blynk.virtualWrite(V2, infoSuhu_2);
    Tsuhu_2.print(0, 0, "Suhu : ");
    Tsuhu_2.print(7, 0, suhu_2);
    Tsuhu_2.print(0, 1, "Kondisi : ");
    Tsuhu_2.print(10, 1, infoSuhu_2);
    //PH tambak 2
    Blynk.virtualWrite(V3, ph_2);
    Blynk.virtualWrite(V3, infoPH_2);
    Tph_2.print(0, 0, "pH : ");
    Tph_2.print(5, 0, ph_2);
    Tph_2.print(0, 1, "Kondisi : ");
    Tph_2.print(10, 1, infoPH_2);
    
    //Notif BLYNK
    if (suhu_1 < 26.0 || suhu_1 > 30.0){
      notif();
      if(suhu_1 < 26.0){
        infoSuhu_1 = "Rendah";
      }
      if(suhu_1 > 30.0){
        infoSuhu_1 = "Tinggi";
      }
    }
    else{
      infoSuhu_1 = "Aman  ";
      aktif=true;
    }
    
    if (ph_1 < 5.5 || ph_1 > 9.0){
      notif();
      if(ph_1 < 5.5){
        infoPH_1 = "Rendah";
      }
      if(suhu_1 > 9.0){
        infoPH_1 = "Tinggi";
      }
    }
    else{
      infoPH_1 = "Aman";
      aktif=true;
    }
    
    if (suhu_2 < 26.0 || suhu_2 > 30.0){
      notif();
      if(suhu_2 < 26.0){
        infoSuhu_2 = "Rendah";
      }
      if(suhu_2 > 30.0){
        infoSuhu_2 = "Tinggi";
      }
    }
    else{
      infoSuhu_2 = "Aman";
      aktif=true;
    }
    
    if (ph_2 < 5.5 || ph_2 > 9.0){
      notif();
      if(ph_2 < 5.5){
        infoPH_2 = "Rendah";
      }
      if(suhu_2 > 9.0){
        infoPH_2 = "Tinggi";
      }
    }
    else{
      infoPH_2 = "Aman";
      aktif=true;
    }
  }
}
