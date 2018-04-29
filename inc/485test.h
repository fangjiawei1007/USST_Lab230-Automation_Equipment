#ifndef _485TEST_H_
#define _485TEST_H_

void servo_uart_init(void);
char servo_Uart_Getch(void);
void SERVO_SET_SPEED(int DevAddress,int Speed);
void SERVO_SET_DISTANCE(int DevAddress,int distance);
void SERVO_GET_POSITION(int DevAddress);

// void SERVO_START_1(int DevAddress);	//内部使能替换外部trigger
// void SERVO_START_2(int DevAddress);	//内部使能替换外部trigger

// void SERVO_STOP_1(int DevAddress);
// void SERVO_STOP_2(int DevAddress);
//void SERVO_START(int DevAddress);
//void SERVO_STOP(int DevAddress);
#endif