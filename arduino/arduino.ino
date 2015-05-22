#include <Servo.h> 
 
int upDownServoID = 0,leftRightServoID = 1;
Servo servoUpDown,servoLeftRight;  
               
int servoID=-1;
String inString="";
void setup() 
{ 
  servoUpDown.attach(2);  
  servoLeftRight.attach(3);
  servoUpDown.write(90);  
  servoLeftRight.write(90);
  Serial.begin(9600);
} 
 
int getAngle(int &servoID)
{
   
   while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      String id_string = inString.substring(0,1);
      String val_string = inString.substring(1);
      
      Serial.print("ID:");
      servoID = id_string.toInt();
      Serial.print(servoID);
      
      
      Serial.print("Value:");
      int val = val_string.toInt();
      Serial.println(val);
      
      inString = "";
      return val;
      
    }
  } 
}
void loop(){
  
  int angle = getAngle(servoID);
  
  
  if(servoID == upDownServoID)
  {
    Serial.println("Writing to updown servo");
    servoUpDown.write(angle);  //Set the tilt servo position to the value of the second command byte received on the serial port
  }
  else if(servoID == leftRightServoID)
  { 
    Serial.println("Writing to leftright servo: ");
	Serial.println(angle);
    servoLeftRight.write(angle);   //Set the pan servo position to the value of the second command byte received from the serial port.
  }
  servoID = -1;
  //If the character is not the pan or tilt servo ID, it is ignored.
}

