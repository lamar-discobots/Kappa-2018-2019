#pragma config(Sensor, in8,    Lift1_R,        sensorPotentiometer)
#pragma config(Motor,  port1,           LiftR,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Right,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ChainB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LiftL,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define abs(X) ((X < 0) ? -1 * X : X)
#define M_PI acos(-1.0)

float wheelRadiusCM = 10.16;

//define functions
int getStraightGoal(float cm);
int getRotationGoal(float deg);
void moveArm(float deg, int armSpeed);

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

void pre_auton()
{
}

task autonomous()
{
	motor[Left]= 127;
	motor[Right]= 127;
	motor[LiftR]= 127;
	motor[LiftL]= 127;
	motor[ChainB]= -127;
	wait1Msec(2300);
// The robot, lift, and chain go forward for 2.3 seconds

	motor[ChainB]= 15;
	motor[LiftR]= 0;
	motor[LiftL]= 0;
	motor[Left]= 0;
	motor[Right]= 0;
//Then the robot stops and chain slows down

	motor[Right]= -127;
	motor[Left]= -127;
	wait1Msec(250);
	motor[Left]= 0;
	motor[Right]= 0;
// The robot goes backward to the ramp for 0.25 seconds

	motor[ChainB]= 127;
	wait1Msec(1000);
	motor[ChainB]= 0;
// The chain bar goes up

	motor[Left]= 127;
	motor[Right]= 127;
	wait1Msec(150);
	motor[Left]= 0;
	motor[Right]= 0;
// The robot goes forward for 0.15 seconds

	motor[Left]= 127;
	motor[Right]= -127;
	wait1Msec(1700);
	motor[Left]= 0;
	motor[Right]= 0;
// The robot turns around for 1.7 seconds

	motor[Left]= -127;
	motor[Right]= -127;
	motor[LiftL]= 127;
	motor[LiftR]= 127;
	wait1Msec(1000);
	motor[LiftL]= 0;
	motor[LiftR]= 0;
// The robot goes backwards and the lift goes up for 1 second

	motor[LiftL]= -127;
	motor[LiftR]= -127;
	wait1Msec(1000);
	motor[LiftL] = 0;
	motor[LiftR] = 0;
// The lift goes down for 1 second

	wait1Msec(800);
	motor[Left]= 0;
	motor[Right]= 0;
// The robot waits a second and then stops
}

task usercontrol()
{
	while (true)
		{
 			int LiftUp 					 = vexRT(Btn5D);
 			int LiftDown 				 = vexRT(Btn5U);
 			int ChainUp 				 = vexRT(Btn6U);
 			int ChainDown 			 = vexRT(Btn6D);
 			int IntakeForward 	 = vexRT(Btn7U);
 			int IntakeBackward	 = vexRT(Btn7D);
 			int leftstickX;
 			int leftstickY;
 			int deadzone 				 = 10;

 //////////////////Arcade Drive/////////////////
	if (abs(vexRT[Ch3]) > deadzone)
		{leftstickY = vexRT[Ch3];}

	else
		{leftstickY = 0;}

	if (abs(vexRT[Ch4]) > deadzone)
		{leftstickX = vexRT[Ch4];}

	else
		{leftstickX =0 ;}

	motor[Left] = leftstickY - leftstickX;
	motor[Right]= leftstickY + leftstickX;
/////////////////Arcade Drive///////////////////////

//////////////////Lift//////////////////////////////
	if (LiftUp == 1)
		{
			motor[LiftR] = 127;
			motor[LiftL] = 127;
		}

	else if (LiftDown == 1)
		{
			motor[LiftR] = -127;
			motor[LiftL] = -127;
		}

	else
		{
			motor[LiftR] = 0;
			motor[LiftL] = 0;
		}
//////////////////Lift///////////////////////////////

/////////////////Second Lift/////////////////////////
	if (ChainUp == 1)
		{
			motor[ChainB] = 127;
		}
	else if (ChainDown == 1)
		{
			motor[ChainB] = -127;
		}
	else
		{
			motor[ChainB] = 15;
		}
/////////////////Second Lift//////////////////////////

/////////////////Intake//////////////////////////////
	if (IntakeForward == 1)
		{
			motor[Intake] = 127;
		}
	else if (IntakeBackward == 1)
		{
			motor[Intake] = -127;
		}
	else
		{
			motor[Intake] = 0;
		}
/////////////////Intake//////////////////////////////

//////////////////Claw///////////////////////////////
/*	if (ClawR == 1)
		{motor [Claw] = -97;}

	else if (ClawL == 1)
		{motor [Claw] = 97;}

	else
		{motor [Claw] = 0;}
*/
//////////////////Claw///////////////////////////////

    UserControlCodePlaceholderForTesting();
  }
}

///////////////Functions////////////////////////
	int getStraightGoal(float cm)
		{return 392*(cm/(wheelRadiusCM*M_PI));}

	int getRotationGoal(float deg)
		{return 392*(deg/102.9);}

void moveArm(float deg, int armSpeed)
{
	armSpeed = abs(armSpeed);

		if(deg < SensorValue[LiftR])
		{
			while(SensorValue[LiftR] <= deg)
			{motor[LiftR] = motor[LiftL] = armSpeed;}
		}

		else
		{
			while(SensorValue[LiftR] >= deg)
			{motor[LiftR] = motor[LiftL] = -armSpeed;}
		}
}
/////////////End of Functions///////////////////
