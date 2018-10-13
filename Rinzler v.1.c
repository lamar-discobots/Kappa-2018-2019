#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in8,    Lift1_R,        sensorPotentiometer)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LiftR,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Left,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Right,         tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           LiftR2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LiftL2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,            ,             tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Claw,          tmotorVex393_MC29, openLoop)
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
}

task usercontrol()
{
	while (true)
		{
 			int ClawR = vexRT(Btn8D);
 			int ClawL = vexRT(Btn8R);
 			int LiftUp = vexRT(Btn5D);
 			int LiftDown = vexRT(Btn5U);
 			int LiftUp2 = vexRT(Btn6D);
 			int LiftDown2 = vexRT(Btn6U);
 			int leftstickX;
 			int leftstickY;
 			int deadzone = 5;

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
	if (LiftUp2 == 1)
		{
			motor[LiftR2] = 127;
			motor[LiftL2] = 127;
		}
	else if (LiftDown2 == 1)
		{
			motor[LiftR2] = -127;
			motor[LiftL2] = -127;
		}
	else
		{
			motor[LiftR2] = 0;
			motor[LiftL2] = 0;
		}
/////////////////Second Lift//////////////////////////

//////////////////Claw///////////////////////////////
	if (ClawR == 1)
		{motor [Claw] = -97;}

	else if (ClawL ==1)
		{motor [Claw] = 97;}

	else
		{motor [Claw] = 0;}
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
