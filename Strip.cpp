#include "Arduino.h"
#include "Strip.h"

Strip::Strip(int r, int g, int b)
{
  this->_pin[0] = r;
  this->_pin[1] = g;
  this->_pin[2] = b;
  for (int i = 0; i <=2; i++){
    pinMode(this->_pin[i], OUTPUT);
    digitalWrite(this->_pin[i], LOW);
  }
};

void Strip::setColor(byte r, byte g, byte b)
{
  this->_color[0] = r;
  this->_color[1] = g;
  this->_color[2] = b;
};

bool Strip::setAlpha(int alpha)
{
  this->_alpha = alpha;
};

void Strip::setPir(int pir)
{
  this->_pir = pir;
  pinMode(pir, INPUT);
};

void Strip::test()
{
    this->setAlpha(100);
    // red
    Serial.println("RED");
    this->setColor(255, 0, 0);
    this->display();
    delay(2000);

    // green
    Serial.println("GREEN");
    this->setColor(0, 255, 0);
    this->display();
    delay(2000);

    // blue
    Serial.println("BLUE");
    this->setColor(0, 0, 255);
    this->display();
    delay(2000);

    // dark
    Serial.println("WHITE alpha=0");
    this->setColor(255, 255, 255);
    this->setAlpha(0);
    this->display();
    delay(2000);

    // all
    Serial.println("WHITE alpha=100");
    this->setColor(255, 255, 255);
    this->setAlpha(100);
    this->display();
    delay(2000);

    // reset
    this->setAlpha(0);
    this->display();

};

bool Strip::checkPir()
{
  if (digitalRead(this->_pir)) {
    this->_timeOff = millis() + LIGHT_TIME;
    this->setAlpha(100);
  } else {
    if (NULL != this->_timeOff && this->_timeOff < millis()){
      this->setAlpha(0);
      this->_timeOff = NULL;
    }
  }
};

bool Strip::loop(){
  if (this->_alpha != this->_currentAlpha){
    int sh = this->_alpha > this->_currentAlpha? 1: -1;
    this->_currentAlpha += sh * ALPHA_SH;
    this->display();
  }
}

void Strip::display()
{
  for (int i = 0; i <= 2; i++){
      analogWrite(this->_pin[i], int(this->_color[i] * this->_currentAlpha / 100));
  }
}

