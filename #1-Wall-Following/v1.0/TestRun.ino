//Test Run
//pins of right motors
int RT1 = 6;
int RT2 = 7;
//pins of left motors
int LT1 = 8;
int LT2 = 9;
//pins to enable motors
int ENR = 5;
int ENL = 11;
//speed of the motor
int SPD = 120;
//distance sensor, OUT to send the wave, IN to receive
int frontOUT = A5;
int frontIN = A4;
int leftOUT = A3;
int leftIN = A2;
int rightOUT = A1;
int rightIN = A0;
//initials for the distance
int frontDistance = 0;
int leftDistance = 0;
int rightDistance = 0;
//function to move forward
void MoveForward(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,HIGH);
        digitalWrite(RT2,LOW);
        digitalWrite(LT1,LOW);
        digitalWrite(LT2,HIGH);
}
//function to move backward
void MoveBackward(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,LOW);
        digitalWrite(RT2,HIGH);
        digitalWrite(LT1,HIGH);
        digitalWrite(LT2,LOW);
}
//function to turn right
void TurnRight(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,LOW);
        digitalWrite(RT2,HIGH);
        digitalWrite(LT1,LOW);
        digitalWrite(LT2,HIGH);
}
//function to turn left
void TurnLeft(){
        analogWrite(ENR,SPD);
        analogWrite(ENL,SPD);
        digitalWrite(RT1,HIGH);
        digitalWrite(RT2,LOW);
        digitalWrite(LT1,HIGH);
        digitalWrite(LT2,LOW);
}
//function to stop
void Stop(){
        digitalWrite(ENR,LOW);
        digitalWrite(ENL,LOW);
}
//function to measure right distance
int frontDistanceMeasure(){
        digitalWrite(frontOUT,LOW);
        delayMicroseconds(2);
        digitalWrite(frontOUT,HIGH);
        delayMicroseconds(20);
        digitalWrite(frontOUT,LOW);
        float fDistance = pulseIn(frontIN,HIGH);
        fDistance = fDistance/58;
        return (int)fDistance;
}
//function to measure left distance
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
//function to measure right distance
int rightDistanceMeasure(){
        digitalWrite(rightOUT,LOW);
        delayMicroseconds(2);
        digitalWrite(rightOUT,HIGH);
        delayMicroseconds(20);
        digitalWrite(rightOUT,LOW);
        float rDistance = pulseIn(rightIN,HIGH);
        rDistance = rDistance/58;
        return (int)rDistance;
}
//setup the initials
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
        pinMode(rightOUT,OUTPUT);
        pinMode(rightIN,INPUT);
        Stop();
}
//loop of the program
void loop(){
//main label
main:
        frontDistance = frontDistanceMeasure();
        leftDistance = leftDistanceMeasure();
        rightDistance = rightDistanceMeasure();        
        if(leftDistance < 15) {
                TurnLeft();
                goto main;
        }
        if(rightDistance < 15) {
                TurnRight();
                goto main;
        }
        if(frontDistance < 15) {
                Stop();
                goto main;
        }
        else{
                MoveForward();
                goto main;
        }
}
