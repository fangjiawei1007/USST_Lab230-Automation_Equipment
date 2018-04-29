#include "includes.h"

#define GETBITS(x,n,m)	((x&~(~0U)<<(m-n+1)<<(n-1))>>(n-1))			//n~m位 第一位为0
unsigned int handwheel_position = 0;
void servo_uart_init(void)
{
	rUFCON3 = 0x0;
	rUMCON3 = 0x0;
	rULCON3 = 0x2B;
	rUCON3  = 0x005;
	rUBRDIV3 = ( (int)(SYS_PCLK/16./57600+0.5) -1 );
	//rUBRDIV3 = ( (int)(SYS_PCLK/16./57600+0.5) -1 );
}

char servo_Uart_Getch(void)
{
	//INT8U temp=0;
	INT8U temp=0xff;
	INT16U Flag_Comm = 0;	
	int i;
	U32 ErrorLoop;

	//wdt_feed_dog();main_enter_flag = 1;
	ErrorLoop = ERROR_NUM*19200/g_SystemConf.BaudRates;

	while(!(rUTRSTAT3 & 0x1) && Flag_Comm<ErrorLoop) //Receive data read
	{
		for(i=0;i<50;i++);	// 2000
		Flag_Comm++;
	}
	if(Flag_Comm >= ErrorLoop)
	{
		temp=0xff;
	}
	else
	{
		/*temp=rUERSTAT3;
		if (temp!=0)
			return 0xff;
		else */
		temp=RdURXH3(); 
		g_Timer2Uart.Timer_Cur = 0;
	}
	return temp;
	
}

void SERVO_SET_SPEED(int DevAddress,int speed)
{
	U8 auchMsg[12],SendArray[12]; //,RecArray[12]
	U8 Count,waitTime; 
//	unsigned int check=0;//cc,dd,
	int i;
	U32 ErrorLoop;
	ErrorLoop = ERROR_NUM*19200/g_SystemConf.BaudRates;
	
	//rUBRDIV3 = ( (int)(SYS_PCLK/16./9600+0.5) -1 );
	if (rULCON3!=0x03) 
		rULCON3 =0x03; 								//0x2b=00 000 0 11  普通 无校验（even） 1停止位 8数据位
	auchMsg[0]=0x28;
	auchMsg[1]=DevAddress;		
	auchMsg[2]=0x00;
	auchMsg[3]=0x08;
	auchMsg[4]=0x02;
	auchMsg[5]=0xE8;	//E8表示速度代码
	auchMsg[6]= (speed >> 24) & 0xff;//
	auchMsg[7]= (speed >> 16) & 0xff;
	auchMsg[8]= (speed >> 8) & 0xff;
	auchMsg[9]=  speed & 0xff;
	auchMsg[10]=(crc16(auchMsg,10)) >>8;
	auchMsg[11]=(crc16(auchMsg,10))& 0xff;
	
	for(i=0;i<12;i++)
	{
		  SendArray[i]=auchMsg[i];
	}
	rGPHDAT |= 0x1000;	//GPH12	+Write
	Delay(DELAY_TIME_RTU);
	for(Count=0;Count<12;Count++)         
	{
		while((!(rUTRSTAT3 & 0x4)) && (waitTime<=ErrorLoop)){
			for (i=0;i<50;i++){
				waitTime++;//wdt_feed_dog();main_enter_flag = 1;
			}
		}
		

		waitTime=0;
		WrUTXH3(SendArray[Count]);//wdt_feed_dog();main_enter_flag = 1;
		while((!(rUTRSTAT3 & 0x4)) && (waitTime<=ErrorLoop)){
			for (i=0;i<50;i++){
				waitTime++;//wdt_feed_dog();main_enter_flag = 1;
			}
		}
	}
	
	 
	/* rGPHDAT &= 0xefff;	//GPH12	-Read
	Count = 0;
	while((RecArray[0]=servo_Uart_Getch())!=0x28 && Count<=20) 
	{
		Count++;
	}
	if(RecArray[0]==0x28)
	{
		for (Count=1;Count<12;Count++)
		{
 			RecArray[Count]=servo_Uart_Getch();
			if (RecArray[Count]==SendArray[Count])
			{
				//check++;
			}
		}
	 */
	//上述为读反馈 set速度不需要用到
}

void SERVO_SET_DISTANCE(int DevAddress,int distance)
{
	U8 auchMsg[12],SendArray[12]; //,RecArray[12]
	U8 Count,waitTime; 
//	unsigned int check=0;//cc,dd,
	int i;
	U32 ErrorLoop;
	ErrorLoop = ERROR_NUM*19200/g_SystemConf.BaudRates;
	
	//rUBRDIV3 = ( (int)(SYS_PCLK/16./9600+0.5) -1 );
	if (rULCON3!=0x03) 
		rULCON3 =0x03; 								//0x2b=00 000 0 11  普通 无校验（none） 1停止位 8数据位
	auchMsg[0]=0x28;
	auchMsg[1]=DevAddress;		
	auchMsg[2]=0x00;
	auchMsg[3]=0x08;
	auchMsg[4]=0x02;
	auchMsg[5]=0xE6;
	auchMsg[6]= (distance >> 24) & 0xff;//
	auchMsg[7]= (distance >> 16) & 0xff;
	auchMsg[8]= (distance >> 8) & 0xff;
	auchMsg[9]=  distance & 0xff;
	auchMsg[10]=(crc16(auchMsg,10)) >>8;
	auchMsg[11]=(crc16(auchMsg,10))& 0xff;
	
	for(i=0;i<12;i++)
	{
		  SendArray[i]=auchMsg[i];
	}
	rGPHDAT |= 0x1000;	//GPH12	+Write
	Delay(DELAY_TIME_RTU);
	for(Count=0;Count<12;Count++)         
	{
		while((!(rUTRSTAT3 & 0x4)) && (waitTime<=ErrorLoop)){
			for (i=0;i<50;i++){
				waitTime++;//wdt_feed_dog();main_enter_flag = 1;
			}
		}
		

		waitTime=0;
		WrUTXH3(SendArray[Count]);//wdt_feed_dog();main_enter_flag = 1;
		while((!(rUTRSTAT3 & 0x4)) && (waitTime<=ErrorLoop)){
			for (i=0;i<50;i++){
				waitTime++;//wdt_feed_dog();main_enter_flag = 1;
			}
		}
	}
	
	 
	/* rGPHDAT &= 0xefff;	//GPH12	-Read
	Count = 0;
	while((RecArray[0]=servo_Uart_Getch())!=0x28 && Count<=20) 
	{
		Count++;
	}
	if(RecArray[0]==0x28)
	{
		for (Count=1;Count<12;Count++)
		{
 			RecArray[Count]=servo_Uart_Getch();
			if (RecArray[Count]==SendArray[Count])
			{
				//check++;
			}
		}
	 */
	//上述为读反馈 set速度不需要用到
}

void SERVO_GET_POSITION(int DevAddress)
{
	
	handwheel_position = 100;//此处100应该替换为通讯所获得值
}

