#include <SoftwareSerial.h> //Bluetooth (~ ları RX TX olarak kullanmak.)
#include <math.h>

SoftwareSerial BTserial(10, 11); // TX, RX
int bParmak, iParmak, oParmak, yParmak, sParmak; // Flex sensörler.

void FlexDegerOku();
void DegerGonder(char sensor,String deger);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  FlexDegerOku();

}
void FlexDegerOku(){  //Analog pinlerden FlexSensor değerleri okunacak. [For ile okumaya çalış.]
  bParmak = analogRead(A4);
  bParmak = map(bParmak, 590, 790, 0, 120); //600 - 900 yazan yere flex sensörün en az ve en fazla yaptığı direnci yazılacak.
  bParmak = constrain(bParmak, 0, 120); // Değeri 0 ile 180 arasında tutmak için.( Misina ile yapılacagından birkaç tur dönmesi gerekebilir. )
DegerGonder('b',String(bParmak));
  Serial.print(bParmak);
  Serial.print("\t");
  
  iParmak = analogRead(A1);
  iParmak = map(iParmak, 525, 700, 0, 120); //600 - 900 yazan yere flex sensörün en az ve en fazla yaptığı direnci yazılacak.
  iParmak = constrain(iParmak, 0, 120); // Değeri 0 ile 180 arasında tutmak için.
DegerGonder('i',String(iParmak));
  Serial.print(iParmak);
  Serial.print("\t");
  
  oParmak = analogRead(A2);
  oParmak = map(oParmak, 520, 690, 0, 140); //600 - 900 yazan yere flex sensörün en az ve en fazla yaptığı direnci yazılacak.
  oParmak = constrain(oParmak, 0, 140); // Değeri 0 ile 180 arasında tutmak için.
DegerGonder('o',String(oParmak));
  Serial.print(oParmak);
  Serial.print("\t");

  yParmak = analogRead(A3);
  yParmak = map(yParmak, 520, 690, 0, 135); //600 - 900 yazan yere flex sensörün en az ve en fazla yaptığı direnci yazılacak.
  yParmak = constrain(yParmak, 0, 135); // Değeri 0 ile 180 arasında tutmak için.
DegerGonder('y',String(yParmak));
  Serial.print(yParmak);
  Serial.print("\t");
  
  sParmak = analogRead(A0);
  sParmak = map(sParmak, 610, 760, 0, 120); //600 - 900 yazan yere flex sensörün en az ve en fazla yaptığı direnci yazılacak.
  sParmak = constrain(sParmak, 0, 120); // Değeri 0 ile 180 arasında tutmak için.
DegerGonder('s',String(sParmak));
  Serial.print(sParmak);
  Serial.print("\t");
  Serial.println();
  
}
void DegerGonder(char sensor,String deger){ //Okunan değerler BlueTooth modülü ile robot kol'a gönderilecek.
  BTserial.write(sensor);
  for(int i=0;i<deger.length();i++){
    char chr=deger[i];
    BTserial.write(chr);
  }
  BTserial.write('/');
  delay(100);
}
