//Line Tracking v1.0
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
void moveForward() {
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
}
//function to move backward.
void moveBackward() {
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, LOW);
        digitalWrite(RT2, HIGH);
        digitalWrite(LT1, HIGH);
        digitalWrite(LT2, LOW);
}
// //function to turn right.
void turnRight() {
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, LOW);
        digitalWrite(RT2, HIGH);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
}
//function to turn left.
void turnLeft() {
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, HIGH);
        digitalWrite(LT2, LOW);
}
//function to stop.
void stop() {
        digitalWrite(ENR, LOW);
        digitalWrite(ENL, LOW);
}
//setup the initials.
void setup() {
        Serial.begin(9600);
        pinMode(RT1, OUTPUT);
        pinMode(RT2, OUTPUT);
        pinMode(LT1, OUTPUT);
        pinMode(LT2, OUTPUT);
        pinMode(ENR, OUTPUT);
        pinMode(ENL, OUTPUT);
        stop();
}
//main loop
void loop() {
        //'1' means detection is true.
        //get detection.
        right = digitalRead(10);
        mid = digitalRead(4);
        left = digitalRead(2);
        //go forward if only mid has detection.
        if (mid == 1 && left == 0 && right == 0) {
                moveForward();
        }
        //discard mid, turn left if left has detection.
        if (left == 1 && right == 0) {
                turnLeft();
                //keep turn left unless left has no detection.
                while (1) {
                        //update detection.
                        right = digitalRead(10);
                        mid = digitalRead(4);
                        left = digitalRead(2);
                        //break the while loop if left has no detecton and go farward a bit.
                        if (left == 0) {
                                moveForward();
                                delay(20);
                                break;
                        }
                        //in case car is confuing when encounter intersection.
                        if(left == 1 && mid == 1 && right == 1) {
                                moveForward();
                                break;
                        }
                        //else keep turn left.
                        else {
                                turnLeft();
                        }
                }
        }
        //dicard mid, turn right if right has detection.
        if (left == 0 && right == 1) {
                turnRight();
                //keep turn right unless left has no detection.
                while (1) {
                        //update detection.
                        right = digitalRead(10);
                        mid = digitalRead(4);
                        left = digitalRead(2);
                        //break the while loop if right has no detecton and go farward a bit.
                        if (right == 0) {
                                moveForward();
                                delay(20);
                                break;
                        }
                        //in case car is confuing when encounter intersection.
                        if(left == 1 && mid == 1 && right == 1) {
                                moveForward();
                                break;
                        }
                        //else keep turn right.
                        else {
                                turnRight();
                        }
                }
        }
        //maybe unnecessary
        //deal with intersection, go forward if all the sensor has detection.
        if(mid == 1 && left == 1 && right == 1) {
                moveForward();
        }
        //maybe unnecessary.
        if(mid == 0 && left == 0 && right == 0) {
                moveForward();
                delay(10);
        }
}
