//pins of right motors.
int RT1 = 6;
int RT2 = 7;
//pins of left motors.
int LT1 = 8;
int LT2 = 9;
//pins to enable motors.
int ENR = 5;
int ENL = 11;
//speed of the motor.
int SPD = 115;
//initials for line detection.
int left, mid, right;
//function to move forward.
void moveForward(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,HIGH);
        digitalWrite(RT2,LOW);
        digitalWrite(LT1,LOW);
        digitalWrite(LT2,HIGH);
}
//function to move backward.
void moveBackward(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,LOW);
        digitalWrite(RT2,HIGH);
        digitalWrite(LT1,HIGH);
        digitalWrite(LT2,LOW);
}
//function to turn right.
void turnRight(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,LOW);
        digitalWrite(RT2,HIGH);
        digitalWrite(LT1,LOW);
        digitalWrite(LT2,HIGH);
}
//function to turn left.
void turnLeft(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,HIGH);
        digitalWrite(RT2,LOW);
        digitalWrite(LT1,HIGH);
        digitalWrite(LT2,LOW);
}
//function to stop.
void stop(){
        digitalWrite(ENR,LOW);
        digitalWrite(ENL,LOW);
}
//setup the initials.
void setup(){
        Serial.begin(9600);
        pinMode(RT1,OUTPUT);
        pinMode(RT2,OUTPUT);
        pinMode(LT1,OUTPUT);
        pinMode(LT2,OUTPUT);
        pinMode(ENR,OUTPUT);
        pinMode(ENL,OUTPUT);
        stop();
}
void loop() {
//lable hell.
hell:
        //'1' means detection is true
        right = digitalRead(10);
        mid = digitalRead(4);
        left = digitalRead(2);
        if(mid == 1 && left == 0 && right == 0){
          moveForward();
          goto hell;
        }
        if(left = 1 && right == 0){
          
        }
}
