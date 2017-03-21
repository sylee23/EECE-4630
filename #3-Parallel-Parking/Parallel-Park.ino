//Test Version of Parallel Park.
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
int SPD = 150;
//distance sensor, OUT to send the wave, IN to receive.
int frontOUT = A5;
int frontIN = A4;
int leftOUT = A3;
int leftIN = A2;
int backOUT = A1;
int backIN = A0;
//initials for the distance.
int frontDistance = 0;
int leftDistance = 0;
int backDistance = 0;
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
//function to measure front distance.
int frontDistanceMeasure(){
        digitalWrite(frontOUT,LOW);
        delayMicroseconds(2);
        digitalWrite(frontOUT,HIGH);
        delayMicroseconds(10);
        digitalWrite(frontOUT,LOW);
        float fDistance = pulseIn(frontIN,HIGH);
        fDistance = fDistance/58;
        return (int)fDistance;
}
//function to measure left distance.
int leftDistanceMeasure(){
        digitalWrite(leftOUT,LOW);
        delayMicroseconds(2);
        digitalWrite(leftOUT,HIGH);
        delayMicroseconds(20);
        digitalWrite(leftOUT,LOW);
        float lDistance = pulseIn(leftIN,HIGH);
        lDistance = lDistance/58;
        return (int)lDistance;
}
//function to measure back distance.
int backDistanceMeasure(){
        digitalWrite(backOUT,LOW);
        delayMicroseconds(2);
        digitalWrite(backOUT,HIGH);
        delayMicroseconds(20);
        digitalWrite(backOUT,LOW);
        float bDistance = pulseIn(backIN,HIGH);
        bDistance = bDistance/58;
        return (int)bDistance;
}
//function to detect two walls and stop.
void detectWall(){
        int range = 10;
        int i = 1;
        //as long as the second wall is not detected, stay in loop.
        while(i != 4) {
                moveForward();
                int g = leftDistanceMeasure();
                switch(i) {
                //detection for the first wall, if detected, go to case 2, else stay in case 1.
                case 1:
                        if(g <= range) {
                                i = 2;
                                moveForward();
                        }
                        else{
                                i = 1;
                                moveForward();
                        }
                        break;
                //detection for the gap between two walls, if dectected, go to case 3, else stay in case 2.
                case 2:
                        if(g >= range) {
                                i = 3;
                                moveForward();
                        }
                        else{
                                i = 2;
                                moveForward();
                        }
                        break;
                //detection for the second wall, if detected, car will stop, else stay in case 3.
                case 3:
                        if(g <= range) {
                                i = 4;
                                stop();
                        }
                        else{
                                i = 3;
                                moveForward();
                        }
                        break;
                }
        }
        stop();
        delay(5000);
}
//an alter logic of wall detection.
void detectWall2(){
        int previous = 0;
        int counter = 0;
        while(counter != 4) {
                int current = leftDistanceMeasure();
                int difference = current - previous;
                difference = abs(difference);
                if (counter = 4) {
                        exit(0);
                }
                else{
                        moveForward();
                        if (difference > 5) {
                                counter++;
                                stop();
                                delay(1000);
                        }
                        if (current - previous != 0) {
                                previous = current;
                        }
                }
        }
}
//third logic of wall detection.
void detectWall3(){
        int range = 10;
        int leftDistance = leftDistanceMeasure();
die:    moveForward();
        if(leftDistance > range) {
hell:           moveForward();
                leftDistance = leftDistanceMeasure();
                if(leftDistance > range) {
                        moveForward();
                        goto hell;
                }
                else if(leftDistance < range) {
school:                 moveForward();
                        leftDistance = leftDistanceMeasure();
                        if(leftDistance < range) {
                                moveForward();
                                goto school;
                        }
                        else if(leftDistance > range) {
work:                           moveForward();
                                leftDistance = leftDistanceMeasure();
                                if(leftDistance > range) {
                                        moveForward();
                                        goto work;
                                }
                                else if (leftDistance < range) {
                                        stop();
                                        delay(5000);
                                }
                        }
                }
        }
        else{
                moveForward();
                leftDistance = leftDistanceMeasure() :
                                       goto die
        }
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
        pinMode(frontOUT,OUTPUT);
        pinMode(frontIN,INPUT);
        pinMode(leftOUT,OUTPUT);
        pinMode(leftIN,INPUT);
        pinMode(backOUT,OUTPUT);
        pinMode(backIN,INPUT);
        stop();
}
//loop of the program.
void loop(){
        //get the detection.
        leftDistance = leftDistanceMeasure();
        frontDistance = frontDistanceMeasure();
        backDistance = backDistanceMeasure();
        //stop at the second box.
        int i = 0;
        int distance = 5;
hell:
        while(1) {
                if(leftDistance > distance) {
                        moveForward();
                        while(1) {
                                leftDistance = leftDistanceMeasure();
                                if(leftDistance < distance) {
                                        moveForward();
                                        while(1) {
                                                leftDistance = leftDistanceMeasure();
                                                if(leftDistance > distance) {
                                                        moveForward();
                                                        while(1) {
                                                                leftDistance = leftDistanceMeasure();
                                                                if(leftDistance < distance) {
                                                                        stop();
                                                                        break hell;
                                                                }
                                                                else{
                                                                        moveForward();
                                                                }
                                                        }
                                                }
                                                else{
                                                        moveForward();
                                                }
                                        }
                                }
                                else{
                                        moveForward();
                                }
                        }
                }
        }
}
//another thought
void loop(){
        //get the detection.
        leftDistance = leftDistanceMeasure();
        frontDistance = frontDistanceMeasure();
        backDistance = backDistanceMeasure();
        //stop at the second box.
        int distance[10000];
        int diff = 0;
        int range = 5;
        int i = 0;
        int g = 0;
        for(i < 10000; i++){
          leftDistance = leftDistanceMeasure();
          distance[i] = leftDistance;
          diff = distance[i] - distance[i-1];
          diff = abs(diff);
          if(diff > 5){
            g++;
          }
          if(g = )
        }
}
