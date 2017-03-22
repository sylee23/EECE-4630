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
//function to detect two walls and stop.
void detectWall()
{
        //current distance.
        int current = 0;
        //previous distance.
        int previous = 0;
        //difference of the distance.
        int diff = current - previous;
        int i = 0;
        moveForward();
        Serial.println(diff);
        //detect the wall and stop at the second one.
        while (1)
        {
                //get the distance.
                current = leftDistanceMeasure();
                Serial.println("Current distance: ");
                Serial.println(current);
                Serial.println("Previous distance: ");
                Serial.println(previous);
                //if car meet the second box then stop.
                if (i = 3)
                {
                        break;
                }
                //count every time car meet box.
                else if (diff > 5)
                {
                        moveForward();
                        Serial.println("Old i: ");
                        Serial.println(i);
                        i++;
                        Serial.println("New i: ");
                        Serial.println(i);
                }
                //if car has not meet the seconde box then go forward.
                else
                {
                        moveForward();
                }
                //update previsou distance.
                previous = current;
                Serial.println("New previous distance: ");
                Serial.println(previous);
                Serial.println();
        }
        //stop when function is finished.
        stop();
}
//loop of the program.
void loop()
{
        //get the detection.
        leftDistance = leftDistanceMeasure();
        frontDistance = frontDistanceMeasure();
        backDistance = backDistanceMeasure();
        detectWall();
}
