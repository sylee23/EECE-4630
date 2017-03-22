//Wall Following v1.0
//In this version, three sensor are enabled(front, left and right). This version is finished a week ahead our due, and we choosed v2.0 to be our final version. Note that we move to v2.0 since v1.0 have some bugs.
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
int rightOUT = A1;
int rightIN = A0;
//initials for the distance.
int frontDistance = 0;
int leftDistance = 0;
int rightDistance = 0;
//value need later.
int max = 50;
int mid = 15;
int min = 10;
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
        delayMicroseconds(20);
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
//function to measure right distance.
int rightDistanceMeasure()
{
        digitalWrite(rightOUT, LOW);
        delayMicroseconds(2);
        digitalWrite(rightOUT, HIGH);
        delayMicroseconds(20);
        digitalWrite(rightOUT, LOW);
        float rDistance = pulseIn(rightIN, HIGH);
        rDistance = rDistance / 58;
        return (int)rDistance;
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
        pinMode(rightOUT, OUTPUT);
        pinMode(rightIN, INPUT);
        stop();
}
//loop of the program.
void loop()
{
//lable hell.
hell:
        frontDistance = frontDistanceMeasure();
        leftDistance = leftDistanceMeasure();
        rightDistance = rightDistanceMeasure();
        //when there's no wall in front.
        if (frontDistance > 20)
        {
                //if there's a wall on the left.
                if (leftDistance < max)
                {
                        //if car is too close to the wall.
                        if (leftDistance < min)
                        {
                                turnRight();
                                delay(100);
                                moveForward();
                                delay(100);
                                goto hell;
                        }
                        //if car is at right distacnce.
                        else if (leftDistance > min && leftDistance < mid)
                        {
                                moveForward();
                                goto hell;
                        }
                        //if car is too far to the wall.
                        else if (leftDistance > mid)
                        {
                                turnLeft();
                                delay(100);
                                moveForward();
                                delay(100);
                                goto hell;
                        }
                }
                //if the first left sensor has move out of the left wall.
                else if (leftDistance > max)
                {
                        //if the second left sensor have move out of the left wall.
                        if (rightDistance > max)
                        {
                                turnLeft();
                                delay(600);
                                moveForward();
                                delay(500);
                                goto hell;
                        }
                        //if the second left snsor can still detect the wall.
                        else if (rightDistance < max)
                        {
                                moveForward();
                                goto hell;
                        }
                }
        }
        //if there's a wall in front.
        else if (frontDistance <= 20)
        {
                turnRight();
                goto hell;
        }
        //if nothing happen.
        else
        {
                moveForward();
                goto hell;
        }
}
