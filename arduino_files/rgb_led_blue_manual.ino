#include <SoftwareSerial.h>

//uno,nanoのPWMピンは3,5,6,9,10,11

const int RTSPin = 2;
const int CTSPin = 3;

const int RedPin = 9;
const int GreenPin = 10;
const int BluePin = 11;

const int ButtonPin = 6;
//const int VibePin = 5;
//const int SpeakerPin = 7;

//チャタリング防止変数
unsigned long prev = 0;
bool osw = HIGH;

//int val = 0; //振動モータPWM用

int R = 0;
int G = 0;
int B = 0;

//状態変数
int serial = 0;
int manual = 1;
int state = manual; //初期はマニュアルモード
///////////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  pinMode(RTSPin, INPUT);
  pinMode(CTSPin, OUTPUT);
  prev = millis();
    
  //シリアルポート初期化
  Serial.begin(9600);
  Serial.println("Ready");
}
////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  unsigned long cur = millis();
  
  //チャタリング防止      
  if (cur - prev > 20) { //無視する時間[ms]
    bool sw = digitalRead(ButtonPin);
    prev = prev;
    if (osw == LOW && sw == HIGH) {
      if (state == serial) {
        state = manual;
        //digitalWrite(CTSPin, HIGH);
        Serial.println("changed manual mode");
      }else if (state == manual) {
        state = serial;
        //digitalWrite(RTSPin, LOW);
        //digitalWrite(CTSPin, LOW);
        Serial.println("changed serial mode");
      }
    }
     osw = sw;
  }
  
  //マニュアルモード/////////////////////////////////
  if (state == manual) 
  {  
    int r = analogRead(5) ;           // アナログ５番ピンから値を読み取り
    r = constrain(r, 0, 1023) ;       // 0-1023の範囲で切取り（デフォ）
    int H0 = map(r,0,1023,360,0) ;    // H値(360-0)にスケール変換
    //Serial.print(H0);
    
    //Hの値で色分け
    if (0 <= H0 && H0 <= 120) {        //H：0→120 ⇔ 赤→黄→緑 
      R = map(H0,0,120,255,0) ;
      G = map(H0,0,120,0,255) ;
      B = 0 ;
    }else if (120 < H0 && H0 <= 240) { //H：121→240 ⇔ 緑→水色→青
      G = map(H0,120,240,255,0) ;
      B = map(H0,120,240,0,255) ;
      R = 0 ;
    }else if (240 < H0 && H0 <= 360) { //H：241→360 ⇔ 青→紫→赤
      B = map(H0,240,360,255,0) ;
      R = map(H0,240,360,0,255) ;
      G = 0 ;
    }else { //Hが0-360以外の場合は無視
    }
  }
  
 //シリアルモード/////////////////////////////////
  if (state == serial) 
  {
    if (Serial.available() > 0){ 
      char c = 0;        
      char str[10] = {}; //文字格納配列
      int i = 0;         
      
      //入力順に配列に格納
      while(i < 10) {
        if (Serial.available() > 0){  
          c = Serial.read();
            if(c >= '0' && c <= '9') { //入力が数字の場合
              str[i] = c;
              i++;
            } else { //数字以外を入力した場合
              str[i] = '\0';
              break; //ループ終了
            }
        } else {
        }
      }
   
      int H1 = atoi(str);     //配列をint数値に変換
      Serial.print("H1 = ");
      Serial.print(H1);      //シリアルモニタにH値表示
     
      //Hの値で色分け
      if (0 <= H1 && H1 <= 120) {        //H：0→120 ⇔ 赤→黄→緑
        R = map(H1,0,120,255,0) ;
        G = map(H1,0,120,0,255) ;
        B = 0 ;
      }else if (120 < H1 && H1 <= 240) { //H：121→240 ⇔ 緑→水色→青
        G = map(H1,120,240,255,0) ;
        B = map(H1,120,240,0,255) ;
        R = 0 ;
      }else if (240 < H1 && H1 <= 360) { //H：241→360 ⇔ 青→紫→赤
        B = map(H1,240,360,255,0) ;
        R = map(H1,240,360,0,255) ;
        G = 0 ;
      }else { //Hが0-360以外の場合は消灯
        R = 0;
        G = 0;
        B = 0;
      }
    }
  }
 ///////////////////////////////////////////////////////////////////////////// 
  //LEDに出力
  analogWrite(RedPin, R);     //  9番ピンから赤LEDの出力
  analogWrite(GreenPin, G);   // 10番ピンから緑LEDの出力
  analogWrite(BluePin, B);    // 11番ピンから青LEDの出力
}

/*
   //振動モータ駆動
   for (val = 0; val<160; val+=20) {
    analogWrite(VibePin, val);
    delay(200);
  }
  for (val = 160; val>-1; val-=20) {
    analogWrite(VibePin, val);
    delay(200);
  };
*/


