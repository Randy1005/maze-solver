#define motorIn1 5
#define motorIn2 6
#define motorIn3 10
#define motorIn4 9
#define trig_right 3
#define echo_right 4
#define trig_left 7
#define echo_left 8
#define trig_front 11
#define echo_front 12

void motorStop();
void forward();
void backward();
void turnRight(int delayTime);
void turnLeft(int delayTime);
void testMotor();
int left_dist();
int front_dist();
int right_dist();

void setup() {
  Serial.begin(9600);
  /*MOTOR*/
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);

  /*SENSOR*/
  pinMode(trig_right, OUTPUT);
  pinMode(echo_right, INPUT);
  pinMode(trig_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trig_front, OUTPUT);
  pinMode(echo_front, INPUT);
  delay(1000);
}

void loop() {

  Serial.print("left:");
  Serial.print(left_dist());
  Serial.print("cm\n");
  Serial.print("right:");
  Serial.print(right_dist());
  Serial.print("cm\n");
  Serial.print("front:");
  Serial.print(front_dist());
  Serial.print("cm\n");
  delay(1000);

  /*Here we try to make the robot go straight*/
  if (front_dist() >= 8)
  {
    forward();
    if (abs(right_dist() - left_dist()) <= 4) //to go straight
    {
      forward();
    }
    if (right_dist() - left_dist() > 4) //if we have enough room on the right side, too close to left, turn right
    {
      backward();
      turnRight(150);
      forward();
    }
    if (left_dist() - right_dist() > 4) //too close to right wall, then turn left
    {
      backward();
      turnLeft(150);
      forward();
    }
  } 

  else
  {
      backward();
      if(right_dist() <= 7 && left_dist() > 15)
      {
        backward();
        turnLeft(150);
      }
      else if(left_dist() <= 7 && right_dist() > 15)
      {
        backward();
        turnLeft(150);
      }
        
  }
}

void motorStop()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  delay(100);
}

void forward()
{
  analogWrite(motorIn1, 160);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, 160);
  analogWrite(motorIn4, 0);
  delay(300);
}


void backward()
{
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 160);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 160);
  delay(250);
}


void turnRight(int delayTime)
{
  analogWrite(motorIn1, 180);
  analogWrite(motorIn2, 0);
  analogWrite(motorIn3, 0);
  analogWrite(motorIn4, 180);
  delay(delayTime);
}

void turnLeft(int delayTime)
{
  analogWrite(motorIn1, 0);
  analogWrite(motorIn2, 180);
  analogWrite(motorIn3, 180);
  analogWrite(motorIn4, 0);
  delay(delayTime);
}


void testMotor()
{
  forward();
  delay(1000);
}


int left_dist()
{
  float duration, dist_left;
  digitalWrite(trig_left, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_left, LOW);
  duration = pulseIn(echo_left, HIGH);
  dist_left = (duration / 2) / 29;
  return dist_left;
}

int right_dist()
{
  float duration, dist_right;
  digitalWrite(trig_right, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_right, LOW);
  duration = pulseIn(echo_right, HIGH);
  dist_right = (duration / 2) / 29;
  return dist_right;
}

int front_dist()
{
  float duration, dist_front;
  digitalWrite(trig_front, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_front, LOW);
  duration = pulseIn(echo_front, HIGH);
  dist_front = (duration / 2) / 29;
  return dist_front;
}


