#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    leftPM,         sensorPotentiometer)
#pragma config(Sensor, in3,    rightPM,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  grabberTouch,   sensorTouch)
#pragma config(Sensor, dgtl2,  sight,          sensorSONAR_cm)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftLeft,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           starGrabber,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           hookLift,      tmotorVex393TurboSpeed_MC29, openLoop)

//                                   *********** ACTIONS METHODS *************
//----------------------------------        Movement of the Robot           ----------------------------------------------

void stopMotors()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void move(char direction, float time)
{
	switch (direction)
	{
	case 'F':
	  motor[leftMotor] = 127;
	  motor[rightMotor] = -127;
	  break;
	case 'B':
	  motor[leftMotor] = -127;
	  motor[rightMotor] = 127;
	  break;
	case 'R':
	  motor[leftMotor] = -127;
	  motor[rightMotor] = -127;
	  break;
	case 'L':
	  motor[leftMotor] = 127;
	  motor[rightMotor] = -127;
	  break;
	default:
	  return;
	}

	wait1Msec(time * 1000);

	// time parameter finished so stop
	stopMotors();

	// and now wait a second before next function
	wait1Msec(1000);
}

void turn(char direction, int degrees)
{
	SensorType[in1] = sensorNone;
	wait1Msec(50);
	SensorType[in1] = sensorGyro;
	wait1Msec(1000); // robotC calibrates sensor
	switch (direction)
	{
	case 'R':
		motor[leftMotor] = -127;
		motor[rightMotor] = 127;
	case 'L':
		motor[leftMotor] = 127;
		motor[rightMotor] = -127;
	default:
		return;
	}
	waitUntil(SensorValue[in1] > degrees * 10);
	stopMotors();
}

//------------------------------------      Control Lift Motors     --------------------------------
void putUpLift()
{
	motor[liftLeft] = 127;
	motor[liftRight] = -127;
	wait1Msec(1350);						//change time for actual robot
	motor[liftLeft] = 0;
	motor[liftRight] = 0;
}


void putDownLift()
{
	motor[liftLeft] = -127;
	motor[liftRight] = 127;
	wait1Msec(740);								//change time for actual robot
	motor[liftLeft] = 0;
	motor[liftRight] = 0;
}


//------------------------------------      StarGrabber         -------------------------------------
void openStarGrabber()
{
	motor[starGrabber] = 0;         //CHANGE 0 TO A VALUE
	wait1Msec(250);
	motor[starGrabber] = 0;
}

void closeStarGrabber()
{
	motor[starGrabber] = 0;         //CHANGE 0 TO A VALUE
	wait1Msec(150);
	motor[starGrabber] = 0;
}

//-----------------------------------		Sensors			-------------------------------


//*******************************************************************************************************
//		WE MAY NOT NEED THIS. IF WE HAVE TIME, WE COULD HARD-CODE THE NUMBERS FOR PRECISE MEASUREMENTS!
//*******************************************************************************************************


//to detect an object near them
//ASK WHERE AND HOW THE SONIC-SENSOR IS PLACES
int toSee()					//0 to 255 in cm
{
	return SensorValue(sight);

}

//to detect if an object is in the starGrabber
//0 if not pressed
//1 if pressed
long toGrab()
{
	return SensorValue(grabberTouch);
}

//*******************************************************************************************************************************


task autonomous()
{

	// waitUntil doesn't work even though it should: http://help.robotc.net/WebHelpVEX/Content/Resources/topics/VEX_IQ/Graphical/Program_Flow/waitUntil.htm
	// waitUntil(SensorValue(sight) < 6);				//change the value for the sights to stop the robot to shoot over the fence
	//*******************************************************************************************************
	//		WE MAY NOT NEED THIS. IF WE HAVE TIME, WE COULD HARD-CODE THE NUMBERS FOR PRECISE MEASUREMENTS!
	//*******************************************************************************************************




	//when star is in the grabber (preload)
	putUpLift();
  closeStarGrabber();
	move('F', 2);
	openStarGrabber();

	//to knock off the stars off the fence             NEEDS TO BE CALCULATED TO PRECISE ANGLES
	//goRight();          //find the exact time required to rotate the robot
	//also, the turn might vary on the starting position of the robot

	move('F', 1);

	for(int i=0; i < 5; i++) 						// knocks some stars off the fence
	{
    		move('B', .5); 								// approximations
    		turn('R', 45);
    		move('F', 1);
    		turn('L', 45);
	}



	//if we are under 15 seconds left
	// pick up cube
	move('B', .5);
	openStarGrabber();
	turn('L', 180); // turn around to face cube
	move('F', .5);
	closeStarGrabber();
	putUpLift();
	turn('L', 180); // turn around to face fence
	move('F', 2);
	openStarGrabber();
}
task main()
{
	startTask(autonomous);
}
