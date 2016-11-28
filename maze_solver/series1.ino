#define TRIG_L 3
#define ECHO_L 2
#define TRIG_R 8
#define ECHO_R 7
#define TRIG_F 4
#define ECHO_F 5

long cm_L = 0,cm_R = 0,cm_F = 0;
int last_do = 0, turn_times = 0;

//motor a
#define In1 6
#define In2 9

//motor b
#define In3 10
#define In4 11

void setup() {
  Serial.begin(9700);
  //ultrasonic setup
  pinMode(TRIG_L,OUTPUT);
  pinMode(ECHO_L,INPUT);
  pinMode(TRIG_R,OUTPUT);
  pinMode(ECHO_R,INPUT);
  pinMode(TRIG_F,OUTPUT);
  pinMode(ECHO_F,INPUT);

  //motor setup
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);

  detect_forward();
  detect_right();
  detect_left();
  
}

void detect_left()
{
//  digitalWrite(TRIG_L,LOW);
//  delayMicroseconds(2);
  digitalWrite(TRIG_L,HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_L,LOW);
  cm_L = pulseIn(ECHO_L,HIGH)/29/2;
  Serial.print("L ");
  Serial.print(cm_L);
  Serial.print(" ");
}
void detect_right()
{
//  digitalWrite(TRIG_R,LOW);
//  delayMicroseconds(2);
  digitalWrite(TRIG_R,HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_R,LOW);
  cm_R = pulseIn(ECHO_R,HIGH)/29/2;
  Serial.print("R ");
  Serial.print(cm_R);
  Serial.print(" ");
}
void detect_forward()
{
//  digitalWrite(TRIG_F,LOW);
//  delayMicroseconds(2);
  digitalWrite(TRIG_F,HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIG_F,LOW);
  cm_F = pulseIn(ECHO_F,HIGH)/29/2;
  if (cm_F > 3000) cm_F = 0; 
  Serial.print("F ");
  Serial.print(cm_F);
  Serial.print(" ");
}
void loop() {
  
  detect_left();
  detect_right();
  if (cm_L > cm_R) left(), delay(100);
  else right(), delay(100);

  forward();
  delay(400);

  detect_forward();
  detect_left();
  detect_right();

  // last_do : 0代表還沒轉(一開始) 1代表剛剛是左轉 2代表剛剛是右轉
  // turn_times : 連續轉彎次數 (更改方向就要歸零)   
  // 左轉 : 左邊>30 && 剛剛不是右轉(回頭後) && 沒有轉5次(繞一圈)
  // 右轉 : 右邊>30 && 剛剛不是左轉(回頭後) && 沒有轉5次(繞一圈)
  // 直走 : 不能左邊 && 不能右轉

  if (cm_L > 30 && cm_R < 30){     // 能左 不能右
    left();
    delay(700);
    if (last_do == 1) turn_times++;
    else last_do = 1, turn_times = 1;
  }
  else if (cm_L < 30 && cm_R > 30){ // 能右 不能左
    right();
    delay(700);
    if (last_do == 2) turn_times++;
    else last_do = 2, turn_times = 1;
  }
  else if (cm_L < 30 && cm_R < 30){ // 左右都不能............................
    if (cm_F > 12)
      forward(), delay(400);
    else
      backward(), delay(200), goround(), delay(700), turn_times = 0;  // 死路
  }
  else{   // 左右都可以
    if (turn_times == 0){ // 最一開始 或 死路迴轉
      if (last_do == 1) left(), delay(700);
      else right(), delay(700);
    }
    else {  // 轉過彎 且 不是從死路出來
      if (turn_times >= 5){
          right();
          delay(700);
          last_do = 2;
          turn_times = 1;
      }
      else {
          left();
          delay(700);
          if (last_do == 1) turn_times ++;
          else last_do = 2, turn_times = 1;
      }
    }
  }

}
void forward(){
  analogWrite(In1,200);
  analogWrite(In2,0);
  analogWrite(In3,200);
  analogWrite(In4,0);
}
void backward(){
  analogWrite(In1,0);
  analogWrite(In2,200);
  analogWrite(In3,0);
  analogWrite(In4,200);
}

void motorstop()
{
  analogWrite(In1, 0);
  analogWrite(In2, 0);
  analogWrite(In3, 0);
  analogWrite(In4, 0);
}

// Let right motor keep running, but stop left motor
void right()
{
  analogWrite(In1, 200);
  analogWrite(In2, 0);
  analogWrite(In3, 0);
  analogWrite(In4, 0);
}
void goround()
{
  analogWrite(In1, 0);
  analogWrite(In2, 200);
  analogWrite(In3, 200);
  analogWrite(In4, 0);
}
// Let left motor keep running, but stop right motor
void left()
{
  analogWrite(In1, 0);
  analogWrite(In2, 0);
  analogWrite(In3, 200);
  analogWrite(In4, 0);
}

