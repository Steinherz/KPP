// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// Ground digital pins 9, 10, 11, and 12 to press the joystick 
// buttons 0, 1, 2, and 3.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick;

int PinOut[4] {5, 4, 3, 2}; // пины выходы 
int PinIn[4] {9, 8, 7, 6}; // пины входа
//int val = 0;
const int value[4][4]{
  {1, 4, 7, 10},
  {2, 5, 8, 0},
  {3, 6, 9, 11},
  {13, 14, 15, 12}
};


void setup() {
  // Initialize Button Pins
  /*pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);*/
  
  
  pinMode (2, OUTPUT); // инициализируем порты на выход (подают нули на столбцы)
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
 
  pinMode (6, INPUT_PULLUP); // инициализируем порты на вход с подтяжкой к плюсу (принимают нули на строках)
  //digitalWrite(6, HIGH);
  pinMode (7, INPUT_PULLUP);
  //digitalWrite(7, HIGH);
  pinMode (8, INPUT_PULLUP);
  //digitalWrite(8, HIGH);
  pinMode (9, INPUT_PULLUP);
  //digitalWrite(9, HIGH);
 
  Serial.begin(9600); // открываем Serial порт

  // Initialize Joystick Library
  Joystick.begin();
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 9;

// Last state of the button
int lastButtonState[9] = {0,0,0,0,0,0,0,0,0};


void matrix () // создаем функцию для чтения кнопок
{
  //int b = 0;
  for (int i = 1; i <=4; i++) // цикл, передающий 0 по всем столбцам
  {
    digitalWrite(PinOut[i - 1], LOW); // если i меньше 4 , то отправляем 0 на ножку
    for (int j = 1; j <=4; j++) // цикл, принимающих 0 по строкам
    {
      int b = value[i - 1][j - 1];  
      if (digitalRead(PinIn[j - 1]) == LOW) // если один из указанных портов входа равен 0, то..
      {       
        lastButtonState[b-1] = 1;
        //Serial.println(b);
        //Serial.println(value[i - 1][j - 1]); // то b равно значению из двойного массива
        //delay(175);       
      } else lastButtonState[b-1] = 0;
    }
    digitalWrite(PinOut[i - 1], HIGH); // подаём обратно высокий уровень
  }
 //return b;
}


void loop() {

  // Read pin values
/*  for (int index = 0; index < 9; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
*/
matrix();

Serial.print(lastButtonState[0]);
Serial.print("\t");
Serial.print(lastButtonState[1]);
Serial.print("\t");
Serial.print(lastButtonState[2]);
Serial.println("\t");

  delay(50);
}



