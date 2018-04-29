#ifndef _TEST_485_H_
#define _TEST_485_H_

#define speed_set_number_x		g_InteralMemory.KeepWord[30]
#define speed_set_number_y		g_InteralMemory.KeepWord[31]
#define speed_set_number_z		g_InteralMemory.KeepWord[32]

#define distance_set_number_x	g_InteralMemory.KeepWord[33]
#define distance_set_number_y	g_InteralMemory.KeepWord[34]
#define distance_set_number_z	g_InteralMemory.KeepWord[35]

#define move_x_button			g_InteralMemory.KeepBit[60]
#define move_y_button			g_InteralMemory.KeepBit[61]
#define move_z_button			g_InteralMemory.KeepBit[62]

#define x_zero_confirm_button	g_InteralMemory.KeepBit[16]
#define y_zero_confirm_button	g_InteralMemory.KeepBit[17]
#define z_zero_confirm_button	g_InteralMemory.KeepBit[18]

#define gripper_1_button		g_InteralMemory.KeepBit[22]
#define gripper_2_button		g_InteralMemory.KeepBit[23]
#define cylinder_A_button		g_InteralMemory.KeepBit[24]
#define cylinder_B_button		g_InteralMemory.KeepBit[25]

/************************ÊÖÂÖÄ£Ê½****************************/

#define handwheel_start_button		g_InteralMemory.KeepBit[56]

#define handwheel_x					g_InteralMemory.KeepBit[50]
#define handwheel_y					g_InteralMemory.KeepBit[51]
#define handwheel_z					g_InteralMemory.KeepBit[52]

#define position_x_get				g_InteralMemory.KeepBit[53]
#define position_y_get				g_InteralMemory.KeepBit[54]
#define position_z_get				g_InteralMemory.KeepBit[55]

#define handwheel_x_speed			g_InteralMemory.KeepWord[160]
#define handwheel_y_speed			g_InteralMemory.KeepWord[161]
#define handwheel_z_speed			g_InteralMemory.KeepWord[162]

#define handwheel_x_position		g_InteralMemory.KeepWord[163]
#define handwheel_y_position		g_InteralMemory.KeepWord[164]
#define handwheel_z_position		g_InteralMemory.KeepWord[165]

#define handwheel_x_speed_tmp		g_InteralMemory.KeepWord[166]
#define handwheel_y_speed_tmp		g_InteralMemory.KeepWord[167]
#define handwheel_z_speed_tmp		g_InteralMemory.KeepWord[168]

#define max_length_x				23000
#define min_length_x				0

#define max_length_y				4600
#define min_length_y				0

#define max_length_z				8000
#define min_length_z				0
/**************************************************************/
#define zero_x					g_InteralMemory.KeepWord[46]
#define zero_y					g_InteralMemory.KeepWord[47]
#define zero_z					g_InteralMemory.KeepWord[48]

#define speed_set_number_tmp_x 		g_InteralMemory.KeepWord[102]
#define distance_set_number_tmp_x	g_InteralMemory.KeepWord[103]

#define speed_set_number_tmp_y		g_InteralMemory.KeepWord[104]
#define distance_set_number_tmp_y	g_InteralMemory.KeepWord[105]

#define speed_set_number_tmp_z		g_InteralMemory.KeepWord[106]
#define distance_set_number_tmp_z	g_InteralMemory.KeepWord[107]


void set_speed_test(void);
void set_speed_distance_485(void);
void manual_init(void);
void move_manually(void);
void zero_confirm(void);
void handwheel_init(void);
void handwheel_parament_init(void);
void handwheel_set_speed(void);
void handwheel_x_stop(void);
void handwheel_y_stop(void);
void handwheel_z_stop(void);
#endif