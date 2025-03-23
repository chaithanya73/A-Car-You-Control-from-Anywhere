#include <AFMotor.h>
#include <Servo.h>

#define trigpin A0
#define echopin A1

AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_64KHZ);

Servo myservo;
int distancel, distancef, distancer;
long distance;
int set=20;
int check=1;

void setup() {
    Serial.begin(9600);
    myservo.attach(10);
    myservo.write(68);                      // right 0
    pinMode(trigpin, OUTPUT);               //straight 68
    pinMode(echopin, INPUT );               //left 130
    motor1.setSpeed(200);
    motor2.setSpeed(200);
    motor3.setSpeed(200);
    motor4.setSpeed(200);
}

void loop() {
    myservo.write(68);
    Serial.println(check);
    //delay(100);
                    distancef=sensor();
    if (Serial.available() > 20 || check == 1) {
        String command = Serial.readStringUntil(' ');
        Serial.print("Command received: ");
        Serial.println(command);

        if (command == "/F1234") {
            Serial.println("Moving forward");
            moveforward();
            delay(1000);
            stop();
        } else if (command == "/B1234") {
            Serial.println("Moving backward");
            movebackward();
            delay(1000);
            stop();
        } else if (command == "/L1234") {
            Serial.println("Turning left");
            turnleft();
        } else if (command == "/R1234") {
            Serial.println("Turning right");
            turnright();
        } else if (command == "/A1234") {
            Serial.println("Switching to automatic mode");
            check = 3;
        } else if (command == "/M12341111111111111111111") {
            Serial.println("Switching to manual mode");
            stop();
            check = 1;
        } else {
            Serial.println("Unknown command");
        }
    } else if (distancef > set && check == 3) {
      Serial.println(distancef);
        moveforward();
    } else {
        stop();
        delay(1000);

        myservo.write(0);    //look right
        distancer = sensor();
        delay(1000);
        myservo.write(130);   //look left
        distancef = sensor();
        delay(1000);
        myservo.write(68);

        while (distancer < set && distancel < set) {
            movebackward();
            delay(1000);
            stop();

            myservo.write(0);    //look right
            distancer = sensor();
            delay(1000);
            myservo.write(130);   //look left
            distancel = sensor();
            delay(1000);
        }
                myservo.write(68);
          // Serial.println(distancer);
          // Serial.println(distancel);
          // delay(3000);


        if (distancer > distancel) {
            turnright();
        }

        if (distancel > distancer) {
            turnleft();
        }
    }
}

long sensor() {
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    distance = pulseIn(echopin, HIGH);
    return distance * 0.034 / 2;
}

void moveforward() {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}

void movebackward() {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}

void stop() {
    motor1.run(RELEASE);        
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void turnleft() {
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(600);
    stop();
}

void turnright() {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(600);
    stop();
}
