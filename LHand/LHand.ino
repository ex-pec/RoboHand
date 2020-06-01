#include <Servo.h>
#include <SoftwareSerial.h>

Servo bParmakServo, iParmakServo, oParmakServo, yParmakServo, sParmakServo, bilekServo;
int bParmakINT=0, iParmakINT=0, oParmakINT=0, yParmakINT=0, sParmakINT=0, bilekINT=0;
char script[]={'1','2','3','4','5','6','7','8','9','a','b','f','ı','l','s','v','w','y','z','x'};
String script2[20][5] ={
                      "150","0","125","125","100",
                      "150","0","0","125","100",
                      "0","0","0","125","100",
                      "150","0","0","0","0",
                      "0","0","0","0","0",
                      "150","0","0","0","100",
                      "150","0","0","125","0",
                      "150","0","125","0","0",
                      "150","140","0","0","0",
                      "0","140","125","125","100",
                      "150","0","0","0","0",
                      "150","80","0","0","0",
                      "150","140","125","125","0",
                      "0","0","125","125","100",
                      "150","140","125","125","100",
                      "150","0","0","125","100",
                      "150","0","0","0","100",
                      "0","140","125","125","0",
                      "150","70","125","125","100",
                      "0","0","125","125","0"
                      };
SoftwareSerial BTserial(10, 11);

String str = "";
int count=0;
String degerler[6]={"0","0","0","0","0","0"};
void setup() {
  // initialize digital pin 8 as an output.
  bParmakServo.attach(3);
  iParmakServo.attach(4);
  oParmakServo.attach(5);
  yParmakServo.attach(6);
  sParmakServo.attach(7);
  reServo();
  Serial.begin(9600);
  BTserial.begin(9600);

}
void loop() {

  if (BTserial.available() > 0) { // Checks whether data is comming from the serial port
    while(BTserial.available()){
      str += (char)BTserial.read(); // Reads the data from the serial port
    }
    bool kontrol=true;
    int konum1=0, konum2=0; // String parçalamak için gerekli.
    while(kontrol){
      if((str.indexOf('/',konum1)) != -1){
        konum1=str.indexOf('/',konum1++);
        String subSTR = str.substring(konum2, konum1);
        konum1++;
        konum2=konum1;
        degerler[count]=subSTR;
        count++;
      }else{
        kontrol=false;
        count=0;
      }
    }
    for(int i=0;i<6;i++){ // Gelen stringi parçalayıp gerekli değerleri çekiyoruz.
      if(degerler[i][0] == 'b'){
        String bParmakSTR;
        for(int j=1;j<degerler[i].length();j++){
          bParmakSTR += degerler[i][j];
        }
        int b=bParmakINT-bParmakSTR.toInt();
        if(b<-5 || b>5){
            bParmakServo.write(bParmakSTR.toInt());
          
            bParmakINT=bParmakSTR.toInt();
        }Serial.print("b"+bParmakSTR + " | "); // Gerekli değer alınıyor. Servoda toInt() ile kullanılacak.
      }else if(degerler[i][0] == 'i'){
        String iParmakSTR;
        for(int j=1;j<degerler[i].length();j++){
          iParmakSTR += degerler[i][j];
        }
        int i=iParmakINT-iParmakSTR.toInt();
        if(i<-5 || i>5){
          iParmakServo.write(iParmakSTR.toInt());
          
          iParmakINT=iParmakSTR.toInt();
        }Serial.print("i"+iParmakSTR + " | "); // Gerekli değer alınıyor. Servoda toInt() ile kullanılacak.
      }else if(degerler[i][0] == 'o'){
        String oParmakSTR;
        for(int j=1;j<degerler[i].length();j++){
          oParmakSTR += degerler[i][j];
        }
        int o=oParmakINT-oParmakSTR.toInt();
        if(o<-5 || o>5){
          oParmakServo.write(oParmakSTR.toInt());
          
          oParmakINT=oParmakSTR.toInt();
        }Serial.print("o"+oParmakSTR + " | "); // Gerekli değer alınıyor. Servoda toInt() ile kullanılacak.
      }else if(degerler[i][0] == 'y'){
        String yParmakSTR;
        for(int j=1;j<degerler[i].length();j++){
          yParmakSTR += degerler[i][j];
        }
        int y=yParmakINT-yParmakSTR.toInt();
        if(y<-5 || y>5){
          yParmakServo.write(yParmakSTR.toInt());
          
          yParmakINT=yParmakSTR.toInt();
        }Serial.print("y"+yParmakSTR + " | "); // Gerekli değer alınıyor. Servoda toInt() ile kullanılacak.
      }else if(degerler[i][0] == 's'){
        String sParmakSTR;
        for(int j=1;j<degerler[i].length();j++){
          sParmakSTR += degerler[i][j];
        }
        int s=sParmakINT-sParmakSTR.toInt();
        if(s<-5 || s>5){
          sParmakServo.write(sParmakSTR.toInt());
          
          sParmakINT=sParmakSTR.toInt();
        }Serial.print("s"+sParmakSTR + " | "); // Gerekli değer alınıyor. Servoda toInt() ile kullanılacak.
      }else{
        // Geçersiz veriler.
      }
    }
    Serial.println();
    str=""; // Yeni string için boşaltıldı.
  }else{
    //Serial.print("Baglantı Yok!");
  }
  if (Serial.available() > 0) {
    //while(Serial.available()){
      char str2 = (char)Serial.read(); // Reads the data from the serial port
    //}
    for(int i=0;i<20;i++){
      if(script[i]==str2){
        bParmakServo.write(script2[i][0].toInt());delay(500);
        iParmakServo.write(script2[i][1].toInt());
        oParmakServo.write(script2[i][2].toInt());
        yParmakServo.write(script2[i][3].toInt());
        sParmakServo.write(script2[i][4].toInt());
        delay(2000);
        break;
      }
    }
    reServo();
  } 
  delay(100);
}
void reServo(){
  bParmakServo.write(0);
  iParmakServo.write(0);
  oParmakServo.write(0);
  yParmakServo.write(0);
  sParmakServo.write(0);
}
