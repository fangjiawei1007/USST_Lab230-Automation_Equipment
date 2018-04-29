#ifndef _PERIPHERAL_H_
#define _PERIPHERAL_H_

#define FASTENING					1
#define RELAXING 					0
	
#define BLOWING_ON 					0
#define BLOWING_OFF 				1

#define MACHINE_HIGH				1
#define MACHINE_LOW					0
// #define MACHINE_TRIGGER_TIME		10000000

#define LAMP_ON 					0
#define LAMP_OFF 					1

#define gripper1_port				4
#define gripper2_port				5

#define gripper1_confirm_port		4
#define gripper2_confirm_port		5

#define cylinder_A_port				6
#define cylinder_B_port				7

#define cylinder_A_confirm_port		6
#define cylinder_B_confirm_port		7

#define give_machine_signal_port 	8
#define signal_from_machine_port	8

#define blowing_port				9

#define lamp_port					10

void Alarm_Lamp_On(void);
void Alarm_Lamp_Off(void);

void everythig_get_zero(void);
void cylinder_get_zero(void);
void gripper_get_zero(unsigned int gripper_number);


unsigned char gripper_relaxing_confirm(unsigned int gripper_confirm_port);
void gripper_fastening(unsigned int gripper_number);
void gripper_relaxing(unsigned int gripper_number);

void cylinder_A_posix(void);
void cylinder_B_posix(void);

unsigned char cylinder_A_posix_confirm(void);
unsigned char cylinder_B_posix_confirm(void);

unsigned char signal_from_machine(unsigned char machine_port);
void give_machine_signal(void);

void gassing_start(void);
void gassing_off(void);

void manual_gripper_1(void);
void manual_gripper_2(void);

void manual_cylinder_A(void);
void manual_cylinder_B(void);
#endif