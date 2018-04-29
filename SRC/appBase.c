#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "def.h"
#include "2416addr.h"
#include "2416lib.h"
#include "option.h"
#include "LCD.h"
#include "mmu.h"
#include "Nand.h"
#include "..\inc\download.h"
#include "..\inc\systemconf.h"
#include "..\inc\systemmenu.h"
#include "..\inc\function.h"
#include "..\inc\jiema.h"
#include "..\inc\communication.h"
#include "..\inc\test.h"
#include "..\inc\Rtc.h"
#include "..\inc\encrypt.h"

#include "..\inc\appBase.h"
#include "..\inc\app.h"

#include "includes.h"

extern INTERALMEMORY g_InteralMemory;


int InPulseCount[7]={0};		//记录6路高速输入的脉冲数

int OutPulse_PreSet[4]={0};	// 3路脉冲输出的  脉冲预设值
volatile unsigned int OutPulse_Counter[4]={0};	// 3路脉冲输出的  当前输出脉冲数


/* //王德铭师兄制管机
int k_motor,motor_fac;
unsigned char signal1,signal2;
volatile unsigned char backward_status;
volatile int	pulse_get_num;
volatile int	pulse_send_num;
volatile int pulse_send_num_record;//,pulse_knife_record;
unsigned char sebiaojiadingchang_flag=1;
volatile unsigned char error_times;
unsigned char sebiao_status;
volatile int pulse_get_total_num;
volatile unsigned char knife_round_finish_flag; */
///////////////////////////////////////////////////////////////////
////	高速脉冲输入X1 中断服务程序    ///////////////
////	InPulseCount[1] 为X1  输入的脉冲数	//////////////////
///////////////////////////////////////////////////////////////////
void __irq PulseIn_1_Process(void)	   //X轴左
{
	int i;
	for(i=0; i<20; i++);

	if((rGPFDAT >> 1) & 0x1)	//上升沿进行移动
	{
		//此处开始添加中断程序
		//InPulseCount[1]++;	
		
		if(handwheel_x_status == 1)
		{
			Trigger_Move(X_Dev_addr,X_AXIS,max_length_x);
		}
	}

	if(!((rGPFDAT >> 1) & 0x1))	//上升沿进行移动
	{
		//此处开始添加中断程序
		//InPulseCount[1]++;	
		
		if(handwheel_x_status == 1)
		{
			handwheel_x_stop();
		}
	}
	rEINTPEND=(1<<1);
	ClearPending(BIT_EINT1);
}
///////////////////////////////////////////////////////////////////
////	高速脉冲输入X2 中断服务程序    ///////////////
////	InPulseCount[2] 为X2  输入的脉冲数	//////////////////
///////////////////////////////////////////////////////////////////
void __irq PulseIn_2_Process(void)		//X轴向右移动
{
	int i;
	for(i=0; i<20; i++);

	//以下为消抖+中断服务程序
	if((rGPFDAT >> 2) & 0x1)
	{
		//InPulseCount[2]++;
		if(handwheel_x_status == 1)
		{
			Trigger_Move(X_Dev_addr,X_AXIS,min_length_x);
		}
		
	}

	if(!((rGPFDAT >> 2) & 0x1))
	{
		//InPulseCount[2]++;
		if(handwheel_x_status == 1)
		{
			handwheel_x_stop();
		}	
	}
	rEINTPEND=(1<<2);
	ClearPending(BIT_EINT2);
}
///////////////////////////////////////////////////////////////////
////	高速脉冲输入X3 中断服务程序    ///////////////
////	InPulseCount[3] 为X3  输入的脉冲数	//////////////////
///////////////////////////////////////////////////////////////////
void __irq PulseIn_3_Process(void)	//Y轴orZ轴正方向移动
{
	int i;
	for(i=0; i<20; i++);

	if((rGPFDAT >> 3) & 0x1)
	{
		//InPulseCount[3]++;
		if(handwheel_y_status == 1)
		{
			Trigger_Move(Y_Dev_addr,Y_AXIS,max_length_y);
		}
		
		if(handwheel_z_status == 1)
		{
			Trigger_Move(Z_Dev_addr,Z_AXIS,max_length_z);
		}
	}

	if(!((rGPFDAT >> 3) & 0x1))
	{
		//InPulseCount[3]++;
		if(handwheel_y_status == 1)
		{
			handwheel_y_stop();
		}
		
		if(handwheel_z_status == 1)
		{
			handwheel_z_stop();
		}
	}
	rEINTPEND=(1<<3);
	ClearPending(BIT_EINT3);
}


//////////////////////////////////////////////////////////////////////
////	高速脉冲输入X4-X7  中断服务程序     //////////////
////	InPulseCount[4] 为X4  输入的脉冲数	//////////////////
////	InPulseCount[5] 为X5  输入的脉冲数	//////////////////
////	InPulseCount[6] 为X6  输入的脉冲数	//////////////////
////	InPulseCount[7] 为X7  输入的脉冲数	//////////////////
/////////////////////////////////////////////////////////////////////
void __irq PulseIn_4_7_Process(void)
{   
	int i;
	for(i=0; i<20; i++);
	
	if (rEINTPEND & (1<<4))	// Eint4	// 高速输入X4
	{
	 
		if((rGPFDAT >> 4) & 0x1)
		{
			//InPulseCount[4]++;
			if(handwheel_y_status == 1)
			{
				Trigger_Move(Y_Dev_addr,Y_AXIS,max_length_y);
			}
			
			if(handwheel_z_status == 1)
			{
				Trigger_Move(Z_Dev_addr,Z_AXIS,max_length_z);
			}
		}
     
	   
		if(!((rGPFDAT >> 4) & 0x1))
		{
			if(handwheel_y_status == 1)
			{
				handwheel_y_stop();
			}
			
			if(handwheel_z_status == 1)
			{
				handwheel_z_stop();
			}
		}
		
		rEINTPEND=(1<<4);		
	}
	else if (rEINTPEND & (1<<5))	// Eint6	// 高速输入X5
	{ 
		if((rGPFDAT >> 5) & 0x1)
		{
			InPulseCount[5]++;
		}
 
		rEINTPEND=(1<<5);		
	}
	else if (rEINTPEND & (1<<6))	// Eint6	// 高速输入X6
	{
		 
		if((rGPFDAT >> 6) & 0x1)
		{
			InPulseCount[6]++;
		}
		 
		rEINTPEND=(1<<6);		
	}
 
	ClearPending(BIT_EINT4_7);
}


//////////////////////////////////////////////////////////////////////
////	高速脉冲输入X8-X23  中断服务程序     //////////////

////////////////////    缝隙传感器 x8    /////////////////////
/////////////////////////////////////////////////////////////////////
void __irq PulseIn_8_23_Process(void)
{ 
	 
	 // Eint10	 输入X10----零位传感器 ————王德铭
	if ( !( rEINTMASK >>10  & 0x1 )  && (rEINTPEND & (1<<10)) )
	{ 
		//此处开始添加X_10中断的中断函数————注释by方佳伟，原版为王德铭师兄制管机程序
		rEINTPEND=(1<<10);		
	}
	else if ( !( rEINTMASK >>11  & 0x1 )  && (rEINTPEND & (1<<11)) )	// Eint11	// 高速输入X11----- 颜色缝传感器  下降沿触发   
	{ 
		//此处开始添加X_11中断的中断函数————注释by方佳伟
			
		
		rEINTPEND=(1<<11);		
	}
	
	
	/*
	else if (rEINTPEND & (1<<13))	// Eint13	// 高速输入X13-------色标传感器
	{
				 
		rEINTPEND=(1<<13);		
	}
  
   */
	ClearPending(BIT_EINT8_23);

}



///////////////////////////////////////////////////////////////
////	高速脉冲输入X1  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse1_Start(void)
{
	rEINTPEND=(1<<1);
	ClearPending(BIT_EINT1);
	
	rEINTMASK &= ~BIT_EINT1;
	rINTMSK1 &= ~BIT_EINT1;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X1  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse1_Stop(void)
{
	rEINTMASK |=(1<<1);
	rINTMSK1 |=BIT_EINT1;
	
	rEINTPEND=(1<<1);
	ClearPending(BIT_EINT1);
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X2  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse2_Start(void)
{
	rEINTPEND=(1<<2);
	ClearPending(BIT_EINT2);
	
	rEINTMASK &= ~(1<<2);
	rINTMSK1 &= ~BIT_EINT2;
	
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X2  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse2_Stop(void)
{
	rEINTMASK |=(1<<2);
	rINTMSK1 |=BIT_EINT2;
	
	rEINTPEND=(1<<2);
	ClearPending(BIT_EINT2);
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X3  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse3_Start(void)
{
	rEINTPEND=(1<<3);
	ClearPending(BIT_EINT3);

	rEINTMASK &= ~(1<<3);
	rINTMSK1 &= ~BIT_EINT3;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X3  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse3_Stop(void)
{
	rEINTMASK |=(1<<3);
	rINTMSK1 |=BIT_EINT3;
	
	rEINTPEND=(1<<3);
	ClearPending(BIT_EINT3);
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X4  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse4_Start(void)
{
	rEINTPEND=(1<<4);
	ClearPending(BIT_EINT4_7);
	
	rEINTMASK &= ~(1<<4);
	rINTMSK1 &= ~BIT_EINT4_7;
	
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X4  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse4_Stop(void)
{
	rEINTMASK |=(1<<4);
	//rINTMSK1 |=BIT_EINT4_7;
	
	rEINTPEND=(1<<4);
	ClearPending(BIT_EINT4_7);
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X5  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse5_Start(void)
{
	rEINTPEND=(1<<5);
	ClearPending(BIT_EINT4_7);
	
	rEINTMASK &= ~(1<<5);
	rINTMSK1 &= ~BIT_EINT4_7;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X5  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse5_Stop(void)
{
	rEINTMASK |=(1<<5);
	//rINTMSK1 |=BIT_EINT4_7;
	
	
	rEINTPEND=(1<<5);
	ClearPending(BIT_EINT4_7);
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X6  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse6_Start(void)
{
	rEINTPEND=(1<<6);
	ClearPending(BIT_EINT4_7);
	
	rEINTMASK &= ~(1<<6);
	rINTMSK1 &= ~BIT_EINT4_7;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X6  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse6_Stop(void)
{
	rEINTMASK |=(1<<6);
	//rINTMSK1 |=BIT_EINT4_7;
	
	rEINTPEND=(1<<6);
	ClearPending(BIT_EINT4_7);
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X10  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse10_Start(void)
{
	rEINTPEND=(1<<10);
	ClearPending(BIT_EINT8_23);
	
	rEINTMASK &= ~(1<<10);
	rINTMSK1 &= ~BIT_EINT8_23;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X10  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse10_Stop(void)
{
	rEINTMASK |=(1<<10);
	//rINTMSK1 |=BIT_EINT8_23;
	
	rEINTPEND=(1<<10);	
	ClearPending(BIT_EINT8_23);			
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X11  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse11_Start(void)
{
	rEINTPEND=(1<<11);
	ClearPending(BIT_EINT8_23);
	
	rEINTMASK &= ~(1<<11);
	//rINTMSK1 &= ~BIT_EINT8_23;
//	sebiao_status=1;	王德铭师兄制管机
		
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X11  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse11_Stop(void)
{
	rEINTMASK |=(1<<11);
	//rINTMSK1 |=BIT_EINT8_23;
	
	rEINTPEND=(1<<11);	
	ClearPending(BIT_EINT8_23);	
//	sebiao_status=0; 王德铭师兄制管机
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X12  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse12_Start(void)
{
	rEINTPEND=(1<<12);
	ClearPending(BIT_EINT8_23);		

	rEINTMASK &= ~(1<<12);
	rINTMSK1 &= ~BIT_EINT8_23;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X12  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse12_Stop(void)
{
	rEINTMASK |=(1<<12);
	//rINTMSK1 |=BIT_EINT8_23;
	
	rEINTPEND=(1<<12);
	ClearPending(BIT_EINT8_23);		
	 
}

///////////////////////////////////////////////////////////////
////	高速脉冲输入X13  启动//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse13_Start(void)
{	
	rEINTPEND=(1<<13);
	ClearPending(BIT_EINT8_23);		
	
	rEINTMASK &= ~(1<<13);
	rINTMSK1 &= ~BIT_EINT8_23;
}
///////////////////////////////////////////////////////////////
////	高速脉冲输入X13  停止//////////////////////////
///////////////////////////////////////////////////////////////
void InPulse13_Stop(void)
{
	rEINTMASK |=(1<<13);
	//rINTMSK1 |=BIT_EINT8_23;
	
	rEINTPEND=(1<<13);
	ClearPending(BIT_EINT8_23);		
}







/////////////////////////////////////////////////
//////	高速脉冲输入初始化     //////////////
//////	IN 1~6   6路高速输入	    //////////////
/////   IN 7\8 特殊上升沿中断输入 //////////////
////////////////////////////////////////////////
void Pulse_In_Init(void)	
{
	DWORD tmp;

	//步骤：清零，设置
	tmp = rGPFCON & (~(0x3<< 2)) & (~(0x3<< 6)) ; //  & (~(0x3<< 14)) & (~(0x3<< 4))
	rGPFCON = tmp | (0x2<<2) | (0x2<<6);//set GPF1,GPF as EINT	X1  | (0x2<<14) | (0x2<<4)   GPF3也设置为了中断————方佳伟
	
	tmp = rGPFCON & (~(0x3<< 4))  ;//& (~(0x3<< 8))
	rGPFCON = tmp | (0x0<<4)  ;	//set GPF2 as INPUT	| (0x0<<6) | (0x0<<14)
	
   
	tmp = rGPGCON &(~(0x3<< 4)) &(~(0x3<< 6));
	rGPGCON = tmp | (0x2<<4) | (0x2<<6);//SET GPG2 AS EINT X10 X11
	
	rGPFCON &= ((~(0x3<<2)) & (~(0x3<<4)) & (~(0x3<<6)) & (~(0x3<<8)));//清零操作by FJW
	rGPFCON |= ((0x2<<2) | (0x2<<4) | (0x2<<6) | (0x2<<8));	//	配置为中断模式by FJW
	
	
	rGPGUDP &= (~(0x3<< 4)) & (~(0x3<< 6)) & (~(0x3<< 8)); //GPF2~4 up down disable
	//tmp = rGPGUDP & (~(0x1<< 0));
	//rGPGUDP  = tmp | (0x1<<0) ;
	//////GPG0---X10，X11，X12=======GPG 2\3\4\5---外部中断
	///////////////////////
	
	rGPFUDP &=  (~(0x3<< 2)) & (~(0x3<< 4)) & (~(0x3<< 6)) & (~(0x3<< 8)) & (~(0x3<< 10)) & (~(0x3<< 12)) & (~(0x3<< 14)); //GPF1~7 up down disable
	
	//rINTMOD1 |= (1<<1);
	//rEXTINT0 = (rEXTINT0 & (~(0x7<<4))) | (0x4<<4);	// Eint1	Rising edge triggered
	rEXTINT0 = (rEXTINT0 & (~(0x7<<4))) | (0x6<<4);		// Eint1	BOTH edge triggered	送管电机编码器脉冲中断输入
	rEXTINT0 = (rEXTINT0 & (~(0x7<<8))) | (0x6<<8);		// Eint2	BOTH edge triggered	
	rEXTINT0 = (rEXTINT0 & (~(0x7<<12)))| (0x6<<12);	// Eint3	Rising edge triggered	刀架编码器脉冲中断输入
	rEXTINT0 = (rEXTINT0 & (~(0x7<<16)))| (0x6<<16);	// Eint4	Rising edge triggered
	
	
	rEXTINT1 = (rEXTINT1 & (~(0x7<<8))) | (0x2<<8);	    // Eint10	下降沿触发		刀架零位中断输入
	rEXTINT1 = (rEXTINT1 & (~(0x7<<12))) | (0x2<<12);	// Eint11	下降沿触发		色标中断输入
	
	
	rEXTINT0 = (rEXTINT0 & (~(0x7<<20))) | (0x4<<20);	// Eint5	Rising edge triggered	
	rEXTINT0 = (rEXTINT0 & (~(0x7<<24))) | (0x4<<24);	// Eint6	Rising edge triggered	
	rEXTINT0 = (rEXTINT0 & (~(0x7<<28)))| (0x4<<28);	// Eint7	Rising edge triggered	
	rEXTINT1 = (rEXTINT1 & (~(0x7<<0))) | (0x2<<0);   	// Eint8	FALLING edge triggered	
	//
	
	//
	//rEXTINT1 = (rEXTINT1 & (~(0x7<<12))) | (0x4<<12);	// Eint11	上升沿触发	
		
	rEXTINT1 = (rEXTINT1 & (~(0x7<<16))) | (0x2<<16);	// Eint12	下降沿触发	
	//rEXTINT1 = (rEXTINT1 & (~(0x7<<20))) | (0x2<<20);	// Eint13	下降沿触发	
	 
	pISR_EINT1= (U32)PulseIn_1_Process;		// X1
	pISR_EINT2= (U32)PulseIn_2_Process;		// X2
	pISR_EINT3= (U32)PulseIn_3_Process;		// X3
	pISR_EINT4_7= (U32)PulseIn_4_7_Process;	// X4_7

	pISR_EINT8_23= (U32)PulseIn_8_23_Process;	// GPG0---X10，X11，X12，X13=======GPG 2\3\4\5
	
	rEINTPEND = 0xffffff;

	rSRCPND1 |= BIT_EINT1|BIT_EINT2|BIT_EINT3|BIT_EINT4_7|BIT_EINT8_23; //to clear the previous pending states
	rINTPND1 |= BIT_EINT1|BIT_EINT2|BIT_EINT3|BIT_EINT4_7|BIT_EINT8_23;

	//rEINTMASK &= ~((1<<2)|(1<<3)|(1<<4)|(1<<6));
	//rINTMSK1 &= ~(BIT_EINT2|BIT_EINT3|BIT_EINT4_7);
	
	InPulse1_Stop();
	InPulse2_Stop();
	InPulse3_Stop();
	InPulse4_Stop();
	InPulse5_Stop();
	InPulse6_Stop();
	//InPulse7_Stop();
	//InPulse8_Stop();
	InPulse10_Stop();
	InPulse11_Stop();
	InPulse12_Stop();
	//InPulse13_Stop();
	InPulse1_Start();
	InPulse2_Start();
	InPulse3_Start();
	InPulse10_Start();
	InPulse11_Start();
}





///////////////////////////////////////////////////////////////////////////
////	Y1 脉冲发送中断服务程序////////
///////////////////////////////////////////////////////////////////////////
void __irq PulseOut_1_Process(void)   
{
	OutPulse_Counter[1]++;
	
	rGPBDAT ^= (1<<1);
	
 	//从此添加中断程序
	//************点动脉冲数记录************//
	if(OutPulse_Counter[1]%2 == 0)
	{
		
		
	}
	 //按键弹起
	if((OutPulse_PreSet[1] > 0)&&(OutPulse_Counter[1] >= OutPulse_PreSet[1]*2))// 返回发脉冲 Y1  
	{
		
		PulseOut_1_Stop(); 
	
		
		OutPulse_Counter[1] = 0;	//点样仪项目需要 将Pulseout_1_start()中的代码移至此处，用以完成
		
	 	ClearPending((U32)BIT_TIMER1);
	 	return ;
		
	}


	
	
	ClearPending((U32)BIT_TIMER1);

}



///////////////////////////////////////////////////////////////////////////
////	Y1 脉冲输出启动//////////////////////////////
////	 每发送一段脉冲 PulseOut_1_Start 只需启动一次//////
////	frequence: 脉冲频率///////////////////////////////
////	pulse_PreSet: 发送脉冲数 ///////////////////////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_1_Start(unsigned int frequence,   int pulse_PreSet)
{
	DWORD tmp;
	
	/* tmp = rGPBCON & (~(0x3<< 2));
	rGPBCON = tmp | (0x2<<2);	//set GPB1 as TOUT */
	if(0 == pulse_PreSet)
	{
		PulseOut_1_Stop();
		
		
		
		return;
	}
	else
	{
		OutPulse_PreSet[1] = pulse_PreSet;
		//OutPulse_Counter[1] = 0;	// 确保每次启动PulseOut_1_Start ，发送脉冲数 pulse_PreSet	//点样仪将此处移至中断中执行
	}
	
	
	if(0 == frequence)
	{
		frequence = 1;
		PulseOut_1_Stop();
		return;
	}
	rTCNTB1= 300300/frequence;		// 100909  	100K  	100000
	rTCMPB1 = rTCNTB1/2;

	rSRCPND1 = rSRCPND1 | ((U32)0x1<<11);   //清空定时器1源请求
    rINTPND1 = rINTPND1 | ((U32)0x1<<11);    //清空定时器1中断请求
   
	rINTMSK1 &=~(BIT_TIMER1);//打开定时器1中断 
	tmp = rTCON & (~(0xf << 8));	// dead zone Disable
	rTCON = tmp | (2 << 8);		// update TCVNTB0, stop			 
	rTCON = tmp | (9 << 8);		// interval mode,  start	
	/* rTCON |= (1<<9) | (1<<11);
	rTCON &= (~(1<<9));
	rTCON |= (1<<8); */
}

///////////////////////////////////////////////////////////////////////////
////	Y1 脉冲发送停止////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_1_Stop(void)
{
	//DWORD tmp;
	Set_Y_Value(1,0);	//直接拉低电平，避免直接位操作
	
	rTCON &= ~(1 << 8);			/* Timer1, stop							*/
	rINTMSK1 |= BIT_TIMER1;
	ClearPending((U32)BIT_TIMER1);

	//OutPulse_Counter[1] = 0;

}


///////////////////////////////////////////////////////////////////////////
////	Y2 脉冲发送中断服务程序////////
///////////////////////////////////////////////////////////////////////////
void __irq PulseOut_2_Process(void) 
{
	OutPulse_Counter[2]++;
	
	rGPBDAT |= (1<<2);
	
	//发完一个脉冲之后的中断函数
	if(OutPulse_Counter[2]%2 == 0)
	{
		

	
		
		
	}	
	
	//脉冲结束记录
	if((OutPulse_PreSet[2] > 0)&&(OutPulse_Counter[2] >= OutPulse_PreSet[2]*2))
	{
		
		//Beep(1);
		
		PulseOut_2_Stop();
		
		
		OutPulse_Counter[2] = 0;//点样仪需要
		
		ClearPending((U32)BIT_TIMER2);
		return;
		}
		

		
		
		ClearPending((U32)BIT_TIMER2);

	}



///////////////////////////////////////////////////////////////////////////
////	Y2 脉冲输出启动//////////////////////////////
////	 每发送一段脉冲 PulseOut_2_Start 只需启动一次//////
////	frequence: 脉冲频率///////////////////////////////
////	pulse_PreSet: 发送脉冲数 ///////////////////////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_2_Start(unsigned int frequence,  int pulse_PreSet)
{
	DWORD tmp;
	
	if(0 == pulse_PreSet)
	{
		PulseOut_2_Stop();
		
		
			
		return;
	}
	else
	{
		OutPulse_PreSet[2] = pulse_PreSet;
		//OutPulse_Counter[2] = 0;	// 确保每次启动PulseOut_2_Start ，发送脉冲数 pulse_PreSet
	}
	
	/* OutPulse_PreSet[2] = pulse_PreSet;
	OutPulse_Counter[2] = 0;
	InPulseCount[3]=0; */
	
	if(0 == frequence)
	{
		frequence = 1;
		PulseOut_2_Stop();
		return;
	}
	
	rTCNTB2= 300300/frequence;	// 100909  	100K  	100000
	rTCMPB2 = rTCNTB2/2;
	
	rSRCPND1 = rSRCPND1 | ((U32)0x1<<12);   //清空定时器2源请求
    rINTPND1 = rINTPND1 | ((U32)0x1<<12);    //清空定时器2中断请求
  
	rINTMSK1 &=~(BIT_TIMER2);//打开定时器2中断 
	tmp = rTCON & (~(0xf << 12));	// dead zone Disable
	rTCON = tmp | (2 << 12)	;/* update TCVNTB0, stop					*/
	rTCON = tmp | (9 << 12)	;/* interval mode,  start				*/
	/* rTCON |= (1<<13) | (1<<15);
	rTCON &= (~(1<<13));
	rTCON |= (1<<12); */
}

///////////////////////////////////////////////////////////////////////////
////	Y2 脉冲发送停止////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_2_Stop(void)
{
	//DWORD tmp;
	
	Set_Y_Value(2,0);//置零置一直接拉低电平
	
	rTCON &= ~(1 << 12);		/* Timer2, stop	*/
	rINTMSK1 |= BIT_TIMER2;
	//OutPulse_Counter[2] = 0;
}


/////////////高速Y3未配置////////////////////
///////////////////////////////////////////////////////////////////////////
////	Y3 脉冲发送中断服务程序////////
///////////////////////////////////////////////////////////////////////////
void __irq PulseOut_3_Process(void)
{
	
	OutPulse_Counter[3]++; 
	
	rGPBDAT ^= (1<<3);
	
	if(OutPulse_Counter[3]%2 == 0)
	{

	
		
	}
	
	if((OutPulse_PreSet[3] > 0)&&(OutPulse_Counter[3] >= OutPulse_PreSet[3]*2))
	{	
		PulseOut_3_Stop();
		

		OutPulse_Counter[3] = 0;	//点样仪需要 运动完成之后将值置零
		
	  	ClearPending((U32)BIT_TIMER3);
		return;
	}
  	ClearPending((U32)BIT_TIMER3);

}
///////////////////////////////////////////////////////////////////////////
////	Y3 脉冲输出启动//////////////////////////////
////	 每发送一段脉冲 PulseOut_3_Start 只需启动一次//////
////	frequence: 脉冲频率///////////////////////////////
////	pulse_PreSet: 发送脉冲数 ///////////////////////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_3_Start(unsigned int frequence, int pulse_PreSet)
{
	DWORD tmp;
	
	if(0 == pulse_PreSet)
	{
		PulseOut_3_Stop();
		
		
		return;
	}
	else
	{
		OutPulse_PreSet[3] = pulse_PreSet;
		//OutPulse_Counter[3] = 0;	// 确保每次启动PulseOut_3_Start ，发送脉冲数 pulse_PreSet
	}
	
	if(0 == frequence)
	{
		frequence = 1;
		PulseOut_3_Stop();
		return;
	}
	
	rTCNTB3= 300300/frequence;	// // Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
	rTCMPB3 = rTCNTB3/2;
	
	rSRCPND1 = rSRCPND1 | ((U32)0x1<<13);   //清空定时器3源请求
	rINTPND1 = rINTPND1 | ((U32)0x1<<13);    //清空定时器3中断请求
  
	
	rINTMSK1 &=~(BIT_TIMER3);
	tmp = rTCON & (~(0xf << 16));	// dead zone Disable
	rTCON = tmp | (2 << 16);		//update TCVNTB0, stop				
	rTCON = tmp | (9 << 16);		// interval mode,  start
}

///////////////////////////////////////////////////////////////////////////
////	Y3 脉冲发送停止////////
///////////////////////////////////////////////////////////////////////////
void PulseOut_3_Stop(void)
{
	//DWORD tmp;

	Set_Y_Value(3,0);//置零置一将电平拉低
	
	rINTMSK1 |= BIT_TIMER3;
	rTCON &= ~(1 << 16);		// Timer3, stop		

	//OutPulse_Counter[2] = 0;
	
}


/////////////////////////////////////////////////
//////	高速脉冲输出初始化     //////////////
//////	OUT 1~3   3路高速输出 //////////////
////////////////////////////////////////////////
void Pulse_Out_Init()	
{
	DWORD tmp;
	
    //set GPB1 2 3 as TOUT
	// tmp = rGPBCON & (~(0x3<< 2)) & (~(0x3<< 4))& (~(0x3<< 6));
	// rGPBCON = tmp | (0x2<<2) | (0x2<<4) | (0x2<<6);		
	
	//set GPB1 2 3 as 普通输出Output
	tmp = rGPBCON & (~(0x3<< 2)) & (~(0x3<< 4))& (~(0x3<< 6));
	rGPBCON = tmp | (0x1<<2) | (0x1<<4) | (0x1<<6);	

	
	    
	
	// Timer1 Initialize	----HS Out1
	pISR_TIMER1 = (int)PulseOut_1_Process;	// Timer ISR for HS Out1
	rTCFG0 &= ~(0xff << 0); 
	rTCFG0 |= (110 << 0); 	// Dead zone=0, Prescaler0=10(0xff)
	rTCFG1 &= ~(0xf << 4); 
	rTCFG1 |= (0x0 << 4); 	// Interrupt, Mux0=1/2
	//rTCNTB1 = 30;    //30.27273	// Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}	100K
	//rTCMPB1 = 15;
	
	 
	
	
	PulseOut_1_Stop();
	

	
	
	// Timer2 Initialize	----HS Out2
	pISR_TIMER2 = (int)PulseOut_2_Process;	// Timer ISR for HS Out2
	rTCFG0 &= ~(0xff << 8); 
	rTCFG0 |= (110 << 8); 	// Dead zone=0, Prescaler0=110(0xff)   注意注意注意！！！不能变 Timer 2 3 4 共用
	rTCFG1 &= ~(0xf << 8); 
	rTCFG1 |= (0x0 << 8); 	// Interrupt, Mux0=1/2
	
	
 	
	PulseOut_2_Stop(); 
	
	
	
	
	

	// Timer3 Initialize	----HS Out3
 	pISR_TIMER3 = (int)PulseOut_3_Process;	// Timer ISR for HS Out3
	rTCFG0 &= ~(0xff << 8); 
	rTCFG0 |= (110 << 8); 	// Dead zone=0, Prescaler0=110(0xff)   注意注意注意！！！不能变 Timer 2 3 4 共用
	rTCFG1 &= ~(0xf << 12); 
 	rTCFG1 |= (0x0 << 12); 	// Interrupt, Mux0=1/2
 	
 	PulseOut_3_Stop();		//此处增加pulseout_3

}
 

//////////////////////////////////////////////////////////////////////
////	DA 输出中断服务程序///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void __irq DA0_10_Process(void) // 可通过示波器确定频率
{
	if(0xffff == (g_InteralMemory.Word[32] & 0xffff))
	{
		g_InteralMemory.Word[32] = 0;
		g_InteralMemory.Word[33]++;
	}
	else
		g_InteralMemory.Word[32]++;

	ClearPending((U32)BIT_TIMER3);
}


//////////////////////////////////////////////////////////////////////
////	DA 输出启动(只需启动一次)//////////////////////////
////	voltage: 输出电压(0.000~10.000V )  小数点后3 位//////////
//////////////////////////////////////////////////////////////////////
void DA0_10_Start(float voltage)
{
	DWORD tmp;

	if(voltage>10*1000)
		voltage = 10*1000;
	else if(voltage<0)
		voltage = 0;
	
	rTCNTB3= 300;	
	//rTCMPB3 = (rTCNTB3*g_InteralMemory.Word[30])/(10000*1.326);// 最大10V , 小数点后3 位10*1000
	rTCMPB3 = (rTCNTB3*voltage)/(10*1000*1.326);// 最大10V , 小数点后3 位10*1000
	if(rTCMPB3 == rTCNTB3)
		rTCMPB3 -= 1;
	
	tmp = rGPBCON & (~(0x3<< 6));
	rGPBCON = tmp | (0x2<<6);	//set GPB3 as TOUT	

	rINTMSK1 &=~(BIT_TIMER3);
	tmp = rTCON & (~(0xf << 16));	// dead zone Disable
	rTCON = tmp | (2 << 16);		/* update TCVNTB3, stop					*/
	rTCON = tmp | (9 << 16);		/* interval mode,  start				*/	
}

//////////////////////////////////////////////////////////////////////
////	DA 输出停止//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void DA0_10_Stop(void)
{
	DWORD tmp;

	rTCNTB3= 300;	
	rINTMSK1 |= BIT_TIMER3;
	rTCON &= ~(1 << 16);			/* Timer3, stop							*/

	tmp = rGPBCON & (~(0x3<< 6));
	rGPBCON = tmp | (1<<6);	//set GPB3 as OUT	
	rGPBDAT &= ~(1<<3);
}


//////////////////////////////////////////////////////////////////////
////	DA 输出初始化///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void DA0_10_Init(void)
{
	DWORD tmp;

	tmp = rGPBCON & (~(0x3<< 6));
	rGPBCON = tmp | (0x2<<6);	//set GPB3 as TOUT	

	// Timer3 Initialize	----DA
	pISR_TIMER3 = (int)DA0_10_Process;	// Timer ISR for DA
	rTCFG0 &= ~(0xff << 8); 
	rTCFG0 |= (110 << 8); 	// Dead zone=0, Prescaler0=110(0xff)   Timer 2 3 4 共用
	rTCFG1 &= ~(0xf << 12); 
	rTCFG1 |= (0x0 << 12); 	// Interrupt, Mux0=1/2
	rTCNTB3 = 300;    			// Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}	1K
	rTCMPB3 = 150;
	DA0_10_Stop();
}



/////////////////////////////////////////////////
//////	普通输入初始化     //////////////
//////	IN7~IN15 共9 路		//////////////
////////////////////////////////////////////////
void X_In_Init(void)	
{
	DWORD tmp;

	tmp = rGPFCON & (~(0x3<< 14));
	rGPFCON = tmp |(0x0<<14);			//set GPF7 as input
	//////////////
	tmp = rGPGCON & (~(0x3<< 0)) & (~(0x3<< 2)) & (~(0x3<< 4)) & (~(0x3<< 6)) & (~(0x3<< 8))
					 & (~(0x3<< 10)) & (~(0x3<< 12)) & (~(0x3<< 14));
	
	rGPGCON = tmp | (0x0<<0) | (0x0<<2) | (0x0<<4) | (0x0<<6) | (0x0<<8) | (0x0<<10) | (0x0<<12) | (0x0<<14);		//set GPF5 7 as input	
	//////////	
}



/////////////////////////////////////////////////
//////	普通输出初始化     //////////////
//////	Y2~Y15 共14 路	 //////////////
////////////////////////////////////////////////
void Y_Out_Init(void)		
{
	DWORD tmp;

	tmp = rGPECON & (~(0x3<< 0)) & (~(0x3<< 2)) & (~(0x3<< 4)) & (~(0x3<< 6)) & (~(0x3<< 8)) & (~(0x3<< 10)) & (~(0x3<< 12)) & (~(0x3<< 14));
	
	
	rGPECON = tmp | (0x1<<0) | (0x1<<2) | (0x1<<4) | (0x1<<6) | (0x1<<8) | (0x1<<10) | (0x1<<12) | (0x1<<14);	//set GPB4 5 9 10 as output	
	// 输入输出都反向
	rGPEDAT |= (1<<0);	// OUT4		
	rGPEDAT |= (1<<1);	// OUT5		
	rGPEDAT |= (1<<2);	// OUT6		
	rGPEDAT |= (1<<3);	// OUT7		
	rGPEDAT &= ~(1<<4);	// OUT8	白总需要将Y8上电拉低	
	rGPEDAT |= (1<<5);	// OUT9		
	rGPEDAT |= (1<<6);	// OUT10	
	rGPEDAT |= (1<<7);	// OUT11	


}





////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////	输入   IN7-IN15//////////////////////
////	返回: 端口状态
////////////////////////////////////////////////////////////////
unsigned char Get_X_Value(unsigned char X_num)
{
	unsigned char X_value=0xff;

	switch(X_num)
	{	
		case 1:
			X_value = (rGPFDAT >> 1) & 0x1;	// X1
			break;
			
		case 2:
			X_value = (rGPFDAT >> 2) & 0x1;	// X2
			break;
			
		case 3:
			X_value = (rGPFDAT >> 3) & 0x1;	// X3
			break;
			
		case 4:
			X_value = (rGPFDAT >> 4) & 0x1;	// X4
			break;
				
		case 5:
			X_value = (rGPFDAT >> 5) & 0x1;	// X5
			break;
				
		case 6:
			X_value = (rGPFDAT >> 6) & 0x1;	// X6
			break;

		case 7:
			X_value = (rGPFDAT >> 7) & 0x1;	// X7
			break;
		case 8:
			X_value = (rGPGDAT >> 0) & 0x1;	// X8	
			break;
		case 9:
			X_value = (rGPGDAT >> 1) & 0x1;	// X9
			break;
		case 10:
			X_value = (rGPGDAT >> 2) & 0x1;	// X10
			break;
		case 11:
			X_value = (rGPGDAT >> 3) & 0x1;	// X11
			break;
		case 12:
			X_value = (rGPGDAT >> 4) & 0x1;	// X12
			break;
		case 13:
			X_value = (rGPGDAT >> 5) & 0x1;	// X13
			break;
		case 14:
			X_value = (rGPGDAT >> 6) & 0x1;	// X14
			break;
		case 15:
			X_value = (rGPGDAT >> 7) & 0x1;	// X15
			break;
	}

	return X_value;// xuzhiqin tixing xiugai
}


////////////////////////////////////////////////////////////////
////	输出   Y4~Y15    /////////////////////////
////	Y_num:4~15		Value:   0或1   //////  高速y1 、 y2 
////////////////////////////////////////////////////////////////
void Set_Y_Value(unsigned char Y_num, unsigned char Value)
{
	Value = Value;// xuzhiqin tixing xiugai
	
	switch(Y_num)
	{
	case 1:
		(Value) ? (rGPBDAT |= (1<<1)) : (rGPBDAT &= ~(1<<1));	// Y1	需先配置输出模式
		break;
	case 2:
		(Value) ? (rGPBDAT |= (1<<2)) : (rGPBDAT &= ~(1<<2));	// Y2	需先配置输出模式
		break;
	case 3:
		(Value) ? (rGPBDAT |= (1<<3)) : (rGPBDAT &= ~(1<<3));	// Y3	需先配置输出模式
		break;
	case 4:
		(Value) ? (rGPEDAT |= (1<<0)) : (rGPEDAT &= ~(1<<0));	// Y4	
		break;
	case 5:
		(Value) ? (rGPEDAT |= (1<<1)) : (rGPEDAT &= ~(1<<1));	// Y5	
		break;
	case 6:
		(Value) ? (rGPEDAT |= (1<<2)) : (rGPEDAT &= ~(1<<2));	// Y6	
		break;
	case 7:
		(Value) ? (rGPEDAT |= (1<<3)) : (rGPEDAT &= ~(1<<3));	// Y7	
		break;
	case 8:
		(Value) ? (rGPEDAT |= (1<<4)) : (rGPEDAT &= ~(1<<4));	// Y8	
		break;
	case 9:
		(Value) ? (rGPEDAT |= (1<<5)) : (rGPEDAT &= ~(1<<5));	// Y9	
		break;
	case 10:
		(Value) ? (rGPEDAT |= (1<<6)) : (rGPEDAT &= ~(1<<6));	// Y10	
		break;
	case 11:
		(Value) ? (rGPEDAT |= (1<<7)) : (rGPEDAT &= ~(1<<7));	// Y11	
		break;
	}
}





