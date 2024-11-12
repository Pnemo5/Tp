/*
* Name: clock and temp project
* Author: Elin Wallgren
* Date: 2024-10-22
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <U8glib.h>
#include <RTClib.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;

// Init constants
const int tempPin = A1;
const int ledPin1 = 7;
const int border = 23;
int pos1 = 0;
int pos2 = 180;
bool sparris = true;

// Init global variables

// construct objects

RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC



void setup() {
  // init communication¨
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  pinMode(ledPin1, OUTPUT);
  myservo.attach(8);

  // Init Hardware

  // Settings
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  u8g.setFont(u8g_font_unifont);
}

void loop() {

  oledWrite(0, 20, getTime(), "Temp: " + String(getTemp()));
  Serial.println(getTemp());
  lampa();
  servoMove();
  delay(1000);
}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {
  DateTime now = rtc.now();
  return "Time: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/
float getTemp() {

  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;


  Vo = analogRead(tempPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}



/*
* This function takes a string and draws it to an oled display
*Parameters: - text: String to write to display
*Returns: void
*/
void oledWrite(int x, int y, String text1, String text2) {
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text1.c_str());
    u8g.drawStr(x, y + 20, text2.c_str());
  } while (u8g.nextPage());
}

/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value) {
  Serial.println("The temperature is " + String(value));
}

void lampa(){
  if(getTemp() > 24){
    digitalWrite(ledPin1, HIGH);
  }
  else{
    digitalWrite(ledPin1, LOW);
  }
}

void servoMove(){

  if(sparris == true){
    myservo.write(pos1);
    sparris = false;
  } else {
    myservo.write(pos2);
    sparris = true;
  }
}