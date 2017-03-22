//Test code.
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
void moveForward()
{
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
}
//function to move backward.
void moveBackward()
{
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, LOW);
        digitalWrite(RT2, HIGH);
        digitalWrite(LT1, HIGH);
        digitalWrite(LT2, LOW);
}
//function to turn right.
void turnRight()
{
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, LOW);
        digitalWrite(RT2, HIGH);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
}
//function to turn left.
void turnLeft()
{
        analogWrite(ENR, SPD);
        analogWrite(ENL, SPD);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, HIGH);
        digitalWrite(LT2, LOW);
}
//function to stop.
void stop()
{
        digitalWrite(ENR, LOW);
        digitalWrite(ENL, LOW);
}
//function to measure front distance.
int frontDistanceMeasure()
{
        digitalWrite(frontOUT, LOW);
        delayMicroseconds(2);
        digitalWrite(frontOUT, HIGH);
        delayMicroseconds(10);
        digitalWrite(frontOUT, LOW);
        float fDistance = pulseIn(frontIN, HIGH);
        fDistance = fDistance / 58;
        return (int)fDistance;
}
//function to measure left distance.
int leftDistanceMeasure()
{
        digitalWrite(leftOUT, LOW);
        delayMicroseconds(2);
        digitalWrite(leftOUT, HIGH);
        delayMicroseconds(20);
        digitalWrite(leftOUT, LOW);
        float lDistance = pulseIn(leftIN, HIGH);
        lDistance = lDistance / 58;
        return (int)lDistance;
}
//function to measure back distance.
int backDistanceMeasure()
{
        digitalWrite(backOUT, LOW);
        delayMicroseconds(2);
        digitalWrite(backOUT, HIGH);
        delayMicroseconds(20);
        digitalWrite(backOUT, LOW);
        float bDistance = pulseIn(backIN, HIGH);
        bDistance = bDistance / 58;
        return (int)bDistance;
}
//setup the initials.
void setup()
{
        Serial.begin(9600);
        pinMode(RT1, OUTPUT);
        pinMode(RT2, OUTPUT);
        pinMode(LT1, OUTPUT);
        pinMode(LT2, OUTPUT);
        pinMode(ENR, OUTPUT);
        pinMode(ENL, OUTPUT);
        pinMode(frontOUT, OUTPUT);
        pinMode(frontIN, INPUT);
        pinMode(leftOUT, OUTPUT);
        pinMode(leftIN, INPUT);
        pinMode(backOUT, OUTPUT);
        pinMode(backIN, INPUT);
        stop();
}
//loop of the program.
void loop()
{
        //get the detection.
        leftDistance = leftDistanceMeasure();
        frontDistance = frontDistanceMeasure();
        backDistance = backDistanceMeasure();
        if (leftDistance < 10)
        {
                turnLeft() :
        }
        if (frontDistance < 10)
        {
                moveBackward();
        }
        if (backDistance < 10)
        {
                stop();
        }
        if (leftDistance < 10 && frontDistance < 10 && backDistance < 10)
        {
                turnRight() :
        }
        else
        {
                moveForward() :
        }
}
