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
int left2OUT = A1;
int left2IN = A0;
int backOUT = 3;
int backIN = 2;
//initials for the distance
int frontDistance = 0;
int leftDistance = 0;
int left2Distance = 0;
int backDistance = 0;
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
//function to turn left2
void Turnright(){
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
//function to measure left2 distance
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
//function to measure left2 distance
int left2DistanceMeasure(){
        digitalWrite(left2OUT,LOW);
        delayMicroseconds(2);
        digitalWrite(left2OUT,HIGH);
        delayMicroseconds(20);
        digitalWrite(left2OUT,LOW);
        float l2Distance = pulseIn(left2IN,HIGH);
        l2Distance = l2Distance/58;
        return (int)l2Distance;
}
//function to measure back distance
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
        pinMode(left2OUT,OUTPUT);
        pinMode(left2IN,INPUT);
        pinMode(backOUT,OUTPUT);
        pinMode(backIN,INPUT);
        Stop();
}
//loop of the program
void loop(){
//lable hell
hell:
        frontDistance = frontDistanceMeasure();
        leftDistance = leftDistanceMeasure();
        left2Distance = left2DistanceMeasure();
        backDistance = backDistanceMeasure();
        if(leftDistance < 15) {
                TurnLeft();
                goto hell;
        }
        if(left2Distance < 15) {
                Turnright();
                goto hell;
        }
        if(frontDistance < 15) {
                MoveBackward();
                goto hell;
        }
        if(backDistance < 15) {
                Stop();
                goto hell;
        }
        else{
                MoveForward();
                goto hell;
        }
}
