#include <TFT_eSPI.h>

#include "bg_sub_wifi.h"
#include "menuSlide.h"



TFT_eSPI tft = TFT_eSPI();
TFT_eSprite bglayer2 = TFT_eSprite(&tft);
TFT_eSprite iconSprite = TFT_eSprite(&tft);


//button
const int8_t btnUp = 16;
const int8_t btnDown = 5;
const int8_t btnLeft = 17;
const int8_t btnRight = 0;
const int8_t btnOk = 33;
const int8_t btnBack = 25;


// warna
unsigned int orange = 0xEA60;
unsigned int black = TFT_BLACK;
unsigned int grey = 0x9492;
unsigned int green = 0x0F92;


void setup() {
  tft.init();
  tft.setSwapBytes(true);
  iconSprite.setSwapBytes(true);
  bglayer2.setSwapBytes(true);

  Serial.begin(9600);

  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
  pinMode(btnOk, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);


  
}



// variabel
int layer = 1;


String listMenuWifi[4] = {"Scan WiFi", "Ganti Password", "Ganti SSID", "Disable Wifi"};
int menuWifiIndex = 0;


void loop() {

  // cek tombol OK kondisi layer 1
  if(digitalRead(btnOk) == 0 && layer == 1){
    iconSprite.deleteSprite();
    layer=2;
    while(digitalRead(btnOk)){}
  }

  // menu utama
  if(layer == 1){
    createMenu1();
  }

  // menuwifi
  if(layer == 2){
    if(digitalRead(btnRight) == 0){
      menuWifiIndex++;
      if(menuWifiIndex > 3){
        menuWifiIndex = 0;
      }
      while(digitalRead(btnRight) == 0){}
    }else if(digitalRead(btnLeft) == 0){
      menuWifiIndex--;
      if(menuWifiIndex < 0){
        menuWifiIndex = 3;
      }
      while(digitalRead(btnLeft) == 0){}
    }
    
    createMenu2(listMenuWifi[menuWifiIndex]);
  }


  // kembali dari layer 2 ke layer 1
  if((digitalRead(btnBack) == 0 && layer == 2)){
    bglayer2.deleteSprite();
    layer=1;
    menuWifiIndex = 0;
    while(digitalRead(btnBack)){}
  }

}





void createMenu1(){
  iconSprite.setColorDepth(8);
  iconSprite.createSprite(240,240);
  iconSprite.pushImage(0,0,240,240,wifiIcon);
  iconSprite.pushSprite(0,0);
}

void createMenu2(String list){
  bglayer2.setColorDepth(8);
  bglayer2.createSprite(240,240);
  bglayer2.pushImage(0,0,240,240,sub_wifi);
  bglayer2.drawString(list.c_str(),30,105,4);
  bglayer2.setTextColor(TFT_WHITE,orange);
  bglayer2.pushSprite(0,0);
}






