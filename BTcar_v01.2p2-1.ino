//This is a modification of the sketch BTcar_v01.2.  The 2p1 stands for 2.1.  This version is meant to work with an Android App developed by Jonathan DeWitt. Current version of App Tested with "RCCarControlRev1Trial". In this version the motors work fine when their buttons are held down.  The front lights, back lights, and horn work the same way.  You have to hold down the button for them to function.  There is no toggle on and toggle off feature
//This is a modification of the sketch BTcar_v01.2p1 to incorporate a toggle on and off with each push of the headlights and taillights.  It has been tested to work with the app "RCCarControlRev4". Created by Jonathan DeWitt on 10/20/2022
#define light_FR  A0    //LED Front Right   pin A0 for Arduino Uno
#define light_FL  A1    //LED Front Left    pin A1 for Arduino Uno
#define light_BR  A2    //LED Back Right    pin A2 for Arduino Uno
#define light_BL  A3    //LED Back Left     pin A3 for Arduino Uno
#define horn_Buzz A4    //Horn Buzzer       pin A4 for Arduino Uno

#define ENA_m1 5        // Enable/speed motor Front Right 
#define ENB_m1 6        // Enable/speed motor Back Right
#define ENA_m2 10       // Enable/speed motor Front Left
#define ENB_m2 11       // Enable/speed motor Back Left

#define IN_11  2    		// L298N #1 in 1 motor Front Right
#define IN_12  3    		// L298N #1 in 2 motor Front Right
#define IN_13  4    		// L298N #1 in 3 motor Back Right
#define IN_14  7    		// L298N #1 in 4 motor Back Right

#define IN_21  8    		// L298N #2 in 1 motor Front Left
#define IN_22  9    		// L298N #2 in 2 motor Front Left
#define IN_23  12   		// L298N #2 in 3 motor Back Left
#define IN_24  13   		// L298N #2 in 4 motor Back Left

int command; 			      //Int to store app command state.
int speedCar = 100; 		// 50 - 255.
int speed_Coeff = 4;
int lightFState=0, lightBState=0; //Stores the state of the front and back lights

void setup()
{   
	  pinMode(light_FR, OUTPUT);
    pinMode(light_FL, OUTPUT);
    pinMode(light_BR, OUTPUT);
    pinMode(light_BL, OUTPUT);
    pinMode(horn_Buzz, OUTPUT);
    
	  pinMode(ENA_m1, OUTPUT);
  	pinMode(ENB_m1, OUTPUT);
	  pinMode(ENA_m2, OUTPUT);
	  pinMode(ENB_m2, OUTPUT);
  
    pinMode(IN_11, OUTPUT);
    pinMode(IN_12, OUTPUT);
    pinMode(IN_13, OUTPUT);
    pinMode(IN_14, OUTPUT);
    
    pinMode(IN_21, OUTPUT);
    pinMode(IN_22, OUTPUT);
    pinMode(IN_23, OUTPUT);
    pinMode(IN_24, OUTPUT);

	  Serial.begin(9600); //Begins serial communication
}//End of void setup 

void loop()
{ 
  if (Serial.available() > 0) {//Checks to see if serial data is being received from the HC-05/06 Module
    	command = Serial.read(); //Reads in Bluetooth data from the HC-05/06 module one character at a time and stores to command variable
    	stopRobot();	//Initialize with motors stopped.
      stopPeriph();  //Initialize with all of the peripherals off
      
      switch (command) 
      {
      case 'F':goAhead();break;
      case 'B':goBack();break;
      case 'L':goLeft();break;
      case 'R':goRight();break;
      case 'I':goAheadRight();break;
      case 'G':goAheadLeft();break;
      case 'J':goBackRight();break;
      case 'H':goBackLeft();break;
      case '0':speedCar = 100;break;
      case '1':speedCar = 115;break;
      case '2':speedCar = 130;break;
      case '3':speedCar = 145;break;
      case '4':speedCar = 160;break;
      case '5':speedCar = 175;break;
      case '6':speedCar = 190;break;
      case '7':speedCar = 205;break;
      case '8':speedCar = 220;break;
      case '9':speedCar = 235;break;
      case 'q':speedCar = 255;break;
      case 'D':
        lightFState++; //Add 1 to the lightFState which was initialized to 0
        if(lightFState>1) //When lightFState tries to go to 2 this will set it back to 0
        {
          lightFState=0;  //variable toggles between 0 and 1
        }
        break; //Breaks out of case 'D' condition
      case 'O':
        lightBState++; //Add 1 to the lightBState which was initialized to 0
        if(lightBState>1) //When lightBState tries to go to 2 this will set it back to 0
        {
          lightBState=0;  //variable toggles between 0 and 1
        }
      break; //Breaks out of case 'O' condition
      case 'U':hornH();break;
      }//End of Switch Statement
    
      evalLights(); //Calls the evalLights function to evaluate the light state variables and take action depending on the state of the lights
  
  }//End of if Serial.available if statement
}//End of Void Loop


//Beginning of Function Definitions
void goAhead()
{ 
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);

      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
}//End of goAhead function

void goBack()
{ 
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);

      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);
}//End of goBack function

void goRight()
{ 
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);

      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);

}//End of goRight function

void goLeft()
{
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);
        
      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);
}//End of goLeft function

void goAheadRight()
{   
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar/speed_Coeff);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar/speed_Coeff);

      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar); 
}//End of goAheadRight function

void goAheadLeft()
{    
      digitalWrite(IN_11, HIGH);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, HIGH);
      analogWrite(ENB_m1, speedCar);

      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, HIGH);
      analogWrite(ENA_m2, speedCar/speed_Coeff);

      digitalWrite(IN_23, HIGH);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar/speed_Coeff);
}//End of goAheadLeft function

void goBackRight()
{ 
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar/speed_Coeff);

      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar/speed_Coeff);

      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);

      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar);
}//End of goBackRight function

void goBackLeft()
{ 
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, HIGH);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, HIGH);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);

      digitalWrite(IN_21, HIGH);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar/speed_Coeff);

      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, HIGH);
      analogWrite(ENB_m2, speedCar/speed_Coeff);
}//End of goBackLeft function

void stopRobot()
{  
      digitalWrite(IN_11, LOW);
      digitalWrite(IN_12, LOW);
      analogWrite(ENA_m1, speedCar);

      digitalWrite(IN_13, LOW);
      digitalWrite(IN_14, LOW);
      analogWrite(ENB_m1, speedCar);
  
      digitalWrite(IN_21, LOW);
      digitalWrite(IN_22, LOW);
      analogWrite(ENA_m2, speedCar);
      
      digitalWrite(IN_23, LOW);
      digitalWrite(IN_24, LOW);
      analogWrite(ENB_m2, speedCar);
}//End of stopRobot function

void lightsFrontH() //Function turns the front lights on
{
  digitalWrite(light_FR, HIGH);
  digitalWrite(light_FL, HIGH);
} //End of lightsFrontH function

void lightsFrontL() //Function turns the front lights off
{
  digitalWrite(light_FR, LOW);
  digitalWrite(light_FL, LOW);
} //End of lightsFrontL function

void lightsBackH() //Function turns the back lights on
{
  digitalWrite(light_BR, HIGH);
  digitalWrite(light_BL, HIGH);
} //End of lightsBackH function

void lightsBackL() //Function turns the back lights off
{
  digitalWrite(light_BR, LOW);
  digitalWrite(light_BL, LOW);
} //End of lightsBackL function

void hornH() //Function turns the horn on
{
  digitalWrite(horn_Buzz, HIGH);
} //End of hornH function

void hornL() //Function turns the horn off
{
  digitalWrite(horn_Buzz, LOW);
} //End of hornL function

void stopPeriph() //Function turns off all of the peripherals at once (i.e. front lights, back lights, and horn)
{
  lightsFrontL(); //Turns front lights output low
  lightsBackL(); //Turns back lights output low
  hornL(); //Turns horn output low
} //End of stopPeriph function

void evalLights() //Evaluates state of the light state variables
{
  //Code for Front Lights
  if(lightFState==1)
  {
    lightsFrontH(); //Turns the lights on
  }
  else if(lightFState==0)
  {
    lightsFrontL(); //Turn the lights off
  }

  //Code for Back Lights
  if(lightBState==1)
  {
    lightsBackH(); //Turns the lights on
  }
  else if(lightBState==0)
  {
    lightsBackL(); //Turn the lights off
  }
} //End of evalLights function
