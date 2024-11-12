#Clock and Temp Project
##Author: Elin Wallgren
##Date: 2024-10-22
##Project Overview
Detta projekt använder en DS3231 RTC (real-time clock) modul för att hålla och visa tid på en 1306 OLED-display. Dessutom mäter den temperaturen via en analog temperatursensor och visar den mätta temperaturen som en korresponderande vinkel på en 9g-servomotor.

Funktioner
Tidvisning: Läser aktuell tid från DS3231 och visar den på OLED-displayen.
Temperaturmätning: Läser temperatur från en analog temperatursensor, omvandlar resistansvärdet till Celsius och skriver ut detta i OLED-displayen.
Temperaturstyrd servo: Mappar temperaturvärdet till en servo-rotation för att indikera temperaturförändringar visuellt.
LED-indikator: Tänder en LED-lampa när temperaturen överstiger en specifik gräns.
Installation
Krävda bibliotek
Se till att du har installerat följande bibliotek i Arduino IDE:

U8glib.h för OLED-displayen
RTClib.h för att hantera DS3231 RTC
Wire.h för I2C-kommunikation
Servo.h för att styra servomotorn
Hårdvaruuppsättning

OLED-display: Anslut I2C-pinnarna på OLED-displayen till rätt pinnarna på din mikrokontroller.
DS3231 RTC: Anslut också denna modul via I2C.
Temperatursensor: Anslut sensorn till A1-pinnen för att läsa analoga temperaturvärden.
Servo-motor: Anslut servon till pinne 8.
LED: Anslut en LED till pinne 7 för visuell indikering.
Ladda upp koden
Anslut din mikrokontroller till datorn och ladda upp koden via Arduino IDE.

Användning
När koden har laddats upp och hårdvaran är korrekt ansluten, fungerar projektet automatiskt och visar tid samt temperatur på OLED-displayen. Temperaturen visas också genom att servon flyttas till olika positioner, och LED-lampan tänds när temperaturen överstiger 24°C.

Funktioner i koden
getTime()
Läser den aktuella tiden från DS3231 och returnerar den i formatet hh:mm:ss.

getTemp()
Läser en analog signal från temperatursensorn, räknar om denna till Celsius och returnerar temperaturvärdet.

oledWrite(int x, int y, String text1, String text2)
Skriver två rader med text på OLED-displayen med angiven position.

servoWrite(float value)
Skriver ut temperaturen i seriekommunikationen. Anpassad för potentiell utveckling där servon styrs mer exakt efter temperaturvärde.

lampa()
Tänder LED-lampan när temperaturen överstiger 24°C.

servoMove()
Växlar servons position mellan två fördefinierade lägen (pos1 och pos2) för att indikera förändringar i temperatur.

Felsökning
Om OLED-displayen inte visar något, kontrollera I2C-anslutningen och adressen i koden.
Om temperaturen inte visas korrekt, kontrollera att sensorn är rätt ansluten till A1.
Om RTC-modulen inte håller tiden rätt, prova att justera tiden med rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); i setup().
