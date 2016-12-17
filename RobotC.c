#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    leftPM,         sensorPotentiometer)
#pragma config(Sensor, in3,    rightPM,        sensorPotentiometer)
#pragma config(Sensor, dgtl1,  grabberTouch,   sensorTouch)
#pragma config(Sensor, dgtl2,  sight,          sensorSONAR_cm)
#pragma config(Sensor, dgtl4,  jump3,          sensorDigitalIn)
#pragma config(Sensor, dgtl5,  bumper,         sensorDigitalIn)
#pragma config(Motor,  port1,           leftFrontMotor, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           starGrabber,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           hookLift,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Caitlin wrote 99% of this class. Rich only made 1% of changes to this class.

/*---------------------------------------------------------------------------*/

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	bDisplayCompetitionStatusOnLcd = true;

	// All activities that occur before the competition starts

	//set the value of each potentiometer to a certain value...

}


//*******************************************************************************************************************************



//                                   *********** ACTIONS METHODS *************
//----------------------------------        Movement of the Robot           ----------------------------------------------

void stopMotors()
{
	motor[leftFrontMotor] = 0;
	motor[leftBackMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightBackMotor] = 0;
}

void move(char direction, float time, bool useBumper)
{
	switch (direction)
	{
	case 'F':
	  motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
	  break;
	case 'B':
	  motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	  break;
	case 'R':
	  motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	  break;
	case 'L':
	  motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
	  break;
	default:
	  return;
	}

	int countRunTimeMsec = 0;
	if (useBumper) // use bumper if 0 is passed as the time parameter
	{
		// just in case the sensor is never pushed
	 	// 1 means not pushed
		while (SensorValue[bumper] == 1 && countRunTimeMsec < time * 1000.0)
		{
			wait1Msec(10);
			countRunTimeMsec += 10;
		} // stopped because max time exceeded or bumper value is 1
	} // not bumper
	else
	{
		wait1Msec(time * 1000);
	}

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
	wait1Msec(1000); 																// robotC calibrates sensor
	switch (direction)
	{
	case 'R':
		motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	case 'L':
		motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
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
	motor[starGrabber] = 0;         				//CHANGE 0 TO A VALUE
	wait1Msec(250);
	motor[starGrabber] = 0;
}

void closeStarGrabber()
{
	motor[starGrabber] = 0;         				//CHANGE 0 TO A VALUE
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
	// 															 AUTONOMOUS
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//		HARD CODING FOR 15 SEC AUTONOMOUS, SENSORS FOR 60 SECOND PROGRAMMING SKILLS CHALLENGE
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ------------------------------------------15 SECOND AUTONOMOUS------------------------------------------------

void auto15()
{
	//when star is in the grabber (preload)
  closeStarGrabber();
	putUpLift();
	move('F', 2, false);
	openStarGrabber();
	//to knock off the stars off the fence             NEEDS TO BE CALCULATED TO PRECISE ANGLES
	//goRight();          //find the exact time required to rotate the robot
	//also, the turn might vary on the starting position of the robot

	move('F', 1, false);

	for(int i=0; i < 5; i++) 						// knocks some stars off the fence
	{
    		move('B', .5, false); 								// approximations
    		turn('R', 45);
    		move('F', 1, false);
    		turn('L', 45);
	}



	//if we are under 15 seconds left
	// pick up cube
	move('B', .5, false);
	openStarGrabber();
	turn('L', 180); // turn around to face cube
	move('F', .5, false);
	closeStarGrabber();
	putUpLift();
	turn('L', 180); // turn around to face fence
	move('F', 2, true);
	openStarGrabber();
}

// ---------------------------------------60 SECONDS AUTONOMOUS--------------------------------------------------

void auto60()
{
	// 3 preloaded stars, 2 preloaded cubes-- go back to starting box to load objects

	// will claw will have game object in it
	closeStarGrabber();
	putUpLift();
	// waitUntil(SensorValue(sight) < 6);				//change the value for the sights to stop the robot to shoot over the fence

	float timeToMid = 6; // make longer than actual time that it takes. This is just in case the robot never triggers the bumper!!!
	float timeToStart = 4;
	move('F', timeToMid, true); // move for 4 sec (or however long it takes) to the fence
	openStarGrabber();

	move('B', timeToStart, false);
	wait1Msec(1000); // wait 1 second to load star/cube
	closeStarGrabber();
	move('F', timeToMid, true);
	openStarGrabber();

	// load cube, heavier than star --> needs more power to lift
	move('B', timeToStart, false);
	wait1Msec(1000); // wait 1 second to load star/cube
	closeStarGrabber();
	// lift here
	move('F', timeToMid, true);
	openStarGrabber();

	// add more to fill 60 seconds
}

task autonomous()
{
	if (SensorValue[jump3] == 0) // jumper is in --> 15 second autonomous
	{
		auto15();
	}
	else // jumper is out --> 60 second autonomous
	{
		auto60();
	}
}


//*******************************************************************************************************************************


task usercontrol()
{
	while (true)
	{
		//To control the left side using channel 3
		if (vexRT[Ch3] != 0)
		{
			motor[leftFrontMotor] = vexRT[Ch3];
			motor[leftBackMotor] = vexRT[Ch3];
		}
		else
		{
			motor[leftFrontMotor] = 0;
			motor[leftBackMotor] = 0;
		}


		//To control the right side using channel 2
		if (vexRT[Ch2] != 0)
		{
			motor[rightFrontMotor] = vexRT[Ch2];
			motor[rightBackMotor] = vexRT[Ch2];

		}
		else
		{
			motor[rightFrontMotor] = 0;
			motor[rightBackMotor] = 0;
		}

		//lift using Button 5
		if (vexRT[Btn5D] == 1) {							//moving lift down
			motor[liftLeft] = -127;							//one of these lifts has to be reversed.... change values if neccessary
			motor[liftRight] = 127;
		}
		else if (vexRT[Btn5U] == 1) {					//moving lift up
			motor[liftLeft] = 127;
			motor[liftRight] = -127;
		}
		else
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}


		//To grab the star using Button 6
		if (vexRT[Btn6D] == 1)
		{
			motor[starGrabber] = -70;					//may want to make this faster...
		}
		else if (vexRT[Btn6U] == 1)
		{
			motor[starGrabber] = 70;
		}
		else
		{
			motor[starGrabber] = 0;
		}
	}
}
