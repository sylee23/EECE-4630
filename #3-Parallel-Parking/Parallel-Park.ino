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
int SPD = 120;
int SPD1 = 150;
//distance sensor, OUT to send the wave, IN to receive.
int leftOUT = A3;
int leftIN = A2;
int backOUT = A1;
int backIN = A0;
//initials for the distance.
int leftDistance = 0;
int backDistance = 0;
//initial counter for wall detection.
int counter = 0;
int previous = 0;
int current = 0;
void moveForward2()
{
        analogWrite(ENR, SPD1);
        analogWrite(ENL, SPD1);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
}
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
void turnRight2()
{
        analogWrite(ENR, SPD1);
        analogWrite(ENL, SPD1);
        digitalWrite(RT1, LOW);
        digitalWrite(RT2, HIGH);
        digitalWrite(LT1, LOW);
        digitalWrite(LT2, HIGH);
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
void turnLeft2()
{
        analogWrite(ENR, SPD1);
        analogWrite(ENL, SPD1);
        digitalWrite(RT1, HIGH);
        digitalWrite(RT2, LOW);
        digitalWrite(LT1, HIGH);
        digitalWrite(LT2, LOW);
}
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

//setup the initials
void setup()
{
        Serial.begin(9600);
        pinMode(RT1, OUTPUT);
        pinMode(RT2, OUTPUT);
        pinMode(LT1, OUTPUT);
        pinMode(LT2, OUTPUT);
        pinMode(ENR, OUTPUT);
        pinMode(ENL, OUTPUT);
        pinMode(leftOUT, OUTPUT);
        pinMode(leftIN, INPUT);
        pinMode(backOUT, OUTPUT);
        pinMode(backIN, INPUT);
        stop();
}

//function to detect two walls and stop.
void detectWall()
{
        //detect approach to box or far away from it
        /*counter = 0; Initial status
           counter = 1; Start moving forward, approach 1st box
           counter = 2; reached 1st box, passing
           counter = 3; exit 1st box, passing
           current = 4; reach second box, stop*/
        while (counter != 4)
        {

                current = leftDistanceMeasure();
//                Serial.print("Current: ");
//                Serial.println(current);
                delay(10);

                int difference = abs(current - previous);
//                Serial.print("difference: ");
//                Serial.println(difference);
                delay(10);
                // reach the box, exit box, and initially status
                if (difference > 10)
                {
                        previous = current;
                        counter++;
                        moveForward();
                }
                else
                {
                        previous = current;
                        moveForward();
                }
//                Serial.print("Counter: ");
//                Serial.println(counter);
//                delay(10);
        }
}
//function to move for more space to make turn.
void back()
{
        moveBackward();
        delay(50);
}
//fucntion to make a right turn.
void adjustright()
{
        turnRight();
        delay(450);
}
//function to make a left turn.
void adjustleft()
{
        turnLeft();
        delay(350);
}
//function to move into the spot.
void park()
{
        moveBackward();
        delay(100);
        while (1)
        {
                backDistance = backDistanceMeasure();
                //stop if there's no spcace in back.
                if (backDistance < 11)
                {
                        stop();
                        //delay(1000);
                        break;
                }
                else
                {
                        moveBackward();
                }
        }
}
//loop of the program
void loop()
{
        detectWall();
        back();
        adjustright();
        park();
        stop();
        delay(10);
        adjustleft();
        //stay in the spot for 1000ms.
        stop();
        delay(100);
        //move out of the spot.
        turnRight2();
        delay(400);
        moveForward2();
        delay(500);
        turnLeft2();
        delay(300);
        moveForward2();
        delay(2000);
        stop();
        delay(50000);
}
