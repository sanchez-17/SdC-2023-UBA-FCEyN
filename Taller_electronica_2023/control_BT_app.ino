#include <Arduino.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial BT1(9, 10); // TX | RX en modulo BT

const byte numChars = 29;
char receivedChars[numChars];
boolean newData = false;

void recvWithStartEndMarkers(){
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    if (BT1.available() > 0){
        rc = BT1.read();
        if (recvInProgress == true){
            if (rc != endMarker){
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) ndx = numChars - 1;
            }else{
                receivedChars[ndx] = '\0';
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }else if (rc == startMarker) recvInProgress = true;
    }
}

void parseData(){
    newData = false;
    if (receivedChars[0]=='T'){
        delayMicroseconds(100);
        Serial.println("3DstuffsNL Slider Firmware V0.3");
        Serial.println("Waiting for command to process...\n");
    }else if (receivedChars[0]=='M'){
        delayMicroseconds(100);
        Serial.println("M gotten");//M_F_5
        AF_DCMotor motor1(1); // create motor #1, 64KHz pwm
        AF_DCMotor motor2(2);// create motor #2, 64KHz pwm

        int Mspeed = (receivedChars[4]-'0') * 25.5;
        motor1.setSpeed(255);     // set the speed to 200/255
        motor2.setSpeed(255);     // set the speed to 200/255

        if (receivedChars[2]=='F')     {motor1.run(FORWARD);motor2.run(FORWARD);}
        else if (receivedChars[2]=='B'){motor1.run(BACKWARD);motor2.run(BACKWARD);}
        else if (receivedChars[2]=='L'){motor1.run(BACKWARD);motor2.run(FORWARD);}
        else if (receivedChars[2]=='R'){motor1.run(FORWARD);motor2.run(BACKWARD);}

        Serial.print("SpeedChar:");
        Serial.println(receivedChars[4]);


        Serial.print("Speed:");
        Serial.println(Mspeed);

        Serial.print("DIR:");
        Serial.println(receivedChars[2]);

        //Serial.println("Speed:");
        //Serial.println(Mspeed);
    }else Serial.println("Unknow Command !!");
          
}
void setup(){
    Serial.begin(9600);
    delayMicroseconds(200);
    BT1.begin(38400);
}

void loop(){
		if (BT1.available() > 0) recvWithStartEndMarkers();
		if (newData)             parseData();
}
