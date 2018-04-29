#include "includes.h"

	INT16U	x_jinji_speed_t   = 100;
	INT16U	x_jianxie_speed_t = 100;
	INT16U	x_diandong_speed_t = 100;
	INT16U	x_huicheng_speed_t = 100;
		
	INT16U	w_jianxie_speed_t = 100;
	INT16U	w_lianxu_speed_t = 100;
	INT16U	w_diandong_speed_t = 100;
		
	INT16U	y_shangzhen_speed_t = 100;
	INT16U	y_xiazheng_speed_t = 100;
	INT16U	y_diandong_speed_t = 100;
		
		//手动测试
	INT16U	dingchang_x_t = 0;
	INT16U	dingchang_y_t = 0;
	INT16U	dingchang_w_t = 0;
		
		//单元初始化
	INT16U	danyuan_hangshu_t = 0;
	INT16U	danyuan_lieshu_t = 0;
	INT16U	danyuan_hangjianju_t = 0;
	INT16U	danyuan_liejianju_t = 0;
		
		//样品初始化
	INT16U	yangpin_hangshu_t = 0;
	INT16U	yangpin_lieshu_t = 0;
	INT16U	yangpin_bianhao_t = 0;
		
		//检测窗
	INT16U	jiance_hangshu_t = 0;
	INT16U	jiance_lieshu_t = 0;
	INT16U	jiance_hangjianju_t = 0;
	INT16U	jiance_liejianju_t = 0;
	INT16U	jiance_gaodu_t = 0;
	INT16U	jiance_kuandu_t = 0;
		
		//点阵
	INT16U	dianzhen_hangshu_t = 0;
	INT16U	dianzhen_lieshu_t = 0;
	INT16U	dianzhen_hangjianju_t = 0;
	INT16U	dianzhen_liejianju_t = 0;
	INT16U	dianzhen_bianhao_t = 0;
		
		//点样针参数
	INT16U	delaytime_t = 0;
	INT16U	pulsewidth_t = 0;
	INT16U	dianyang_voltage_t = 0;
	INT16U	dianyang_speed_t = 0;
	INT16U	xiye_speed_t = 0;
	INT16U	tuye_speed_t = 0;
	INT16U	clean_times_t = 0;
	INT16U	dianyang_times_t = 0;
	INT16U	pinshan_freq_t = 0;
		
		//补充点样
	INT16U	sup_dy_hang_t = 0;
	INT16U	sup_dy_lie_t = 0;
	INT16U	sup_jc_hang_t = 0;
	INT16U	sup_jc_lie_t = 0;
	INT16U	sup_yp_t = 0;
	INT16U	sup_dz_t = 0;
		
		//工作位置
	INT16U	gongzuo_x_t = 0;
	INT16U	gongzuo_y_t = 0;
	INT16U	gongzuo_w_t = 0;
		
	INT16U	clean_x_t = 0;
	INT16U	clean_y_t = 0;
	INT16U	clean_w_t = 0;
		
	INT16U	quyang_x_t = 0;
	INT16U	quyang_y_t = 0;
	INT16U	quyang_w_t = 0;
		
	INT16U	zhangan_x_t = 0;
	INT16U	zhangan_y_t = 0;
	INT16U	zhangan_w_t = 0;
		
	INT16U	pingshan_x_t = 0;
	INT16U	pingshan_y_t = 0;
	INT16U	pingshan_w_t = 0;
		
	INT16U	tuye_x_t = 0;
	INT16U	tuye_y_t = 0;
	INT16U	tuye_w_t = 0;
	
	unsigned int jog_status[3] = {0};
	unsigned int jog_monitor_status[3] = {0};
	unsigned int dingchang_status[3] = {0};
	unsigned int dingchang_monitor_status[3] = {0};
	unsigned int get_zero_status[3] = {0};
	unsigned int weitiao_status[3] = {0};	//三根轴微调的标志位
	unsigned int xitong_status[6] = {0};
	unsigned int confirm_status[6] = {0};
	
	unsigned int confirm_monitor_x_status[6] = {0};
	unsigned int confirm_monitor_y_status[6] = {0};
	unsigned int confirm_monitor_w_status[6] = {0};
	
	unsigned int xitong_c_status[6] = {0};	//确认是哪个轴转完之后进行回零
	
	unsigned int weitiao_x_status[6] = {0};	//微调status系统六个位置
	unsigned int weitiao_y_status[6] = {0};
	unsigned int weitiao_w_status[6] = {0};
	
	
	unsigned int gongzuo_flag_x = 0;
	unsigned int gongzuo_flag_y = 0;
	unsigned int gongzuo_flag_w = 0;
	
	unsigned int clean_flag_x = 0;
	unsigned int clean_flag_y = 0;
	unsigned int clean_flag_w = 0;
	
	unsigned int quyang_flag_x = 0;
	unsigned int quyang_flag_y = 0;
	unsigned int quyang_flag_w = 0;
	
	unsigned int zhangan_flag_x = 0;
	unsigned int zhangan_flag_y = 0;
	unsigned int zhangan_flag_w = 0;
	
	unsigned int pingshan_flag_x = 0;
	unsigned int pingshan_flag_y = 0;
	unsigned int pingshan_flag_w = 0;
	
	unsigned int tuye_flag_x = 0;
	unsigned int tuye_flag_y = 0;
	unsigned int tuye_flag_w = 0;

	int gongzuo_position_x = 0;
	int gongzuo_position_y = 0;
	int gongzuo_position_w = 0;
	
	int clean_position_x = 0;
	int clean_position_y = 0;
	int clean_position_w = 0;
	
	int quyang_position_x = 0;
	int quyang_position_y = 0;
	int quyang_position_w = 0;
	
	int zhangan_position_x = 0;
	int zhangan_position_y = 0;
	int zhangan_position_w = 0;
	
	int pingshan_position_x = 0;
	int pingshan_position_y = 0;
	int pingshan_position_w = 0;
	
	int tuye_position_x = 0;
	int tuye_position_y = 0;
	int tuye_position_w = 0;
	
	
	//微调监控按钮 数组中0---X轴 1----Y轴  2-----W轴
	int monitor_gongzuo_flag[3] = {0};
	int monitor_clean_flag[3] = {0};
	int monitor_quyang_flag[3] = {0};
	int monitor_zhangan_flag[3] = {0};
	int monitor_pingshan_flag[3] = {0};
	int monitor_tuye_flag[3] = {0};
	
	
	//运动按钮
	unsigned int start_status[6] = {0};
	
	//上电正常工作标志位
	unsigned int start_b_status = 0;
	
	unsigned int work_zero_x_status = 0;
	unsigned int work_zero_y_status = 0;
	unsigned int work_zero_w_status = 0;
	
	unsigned int work_zero_x_monitor_status = 0;
	unsigned int work_zero_y_monitor_status = 0;
	unsigned int work_zero_w_monitor_status = 0;
	//unsigned int work_zero_x_monitor_status = 0;
	unsigned int work_zero_x_finish = 0;
	unsigned int work_zero_y_finish = 0;
	unsigned int work_zero_w_finish = 0;

	

	unsigned int work_clean_x_status = 0;
	unsigned int work_clean_x_finish = 0;
	
	unsigned int work_clean_y_status = 0;
	unsigned int work_clean_y_finish = 0;
	
	unsigned int work_clean_x_monitor_status = 0;
	unsigned int work_clean_y_monitor_status = 0;
	unsigned int work_clean_back_monitor_status = 0;
	
	
	unsigned int work_cleaning_status = 0;
	unsigned int work_cleaning_finish = 0;
	unsigned int work_clean_back_status = 0;
	unsigned int work_clean_back_finish = 0;
	unsigned int work_clean_start_status = 0;

	
	unsigned int quyang_allow = 0;
	unsigned int quyang_status = 0;
	
	unsigned int work_quyang_x_status = 0;
	unsigned int work_quyang_x_finish = 0;
	
	unsigned int work_quyang_y_status = 0;
	unsigned int work_quyang_y_finish = 0;
	
	unsigned int work_quyang_x_monitor_status = 0;
	unsigned int work_quyang_y_monitor_status = 0;
	unsigned int work_quyang_back_monitor_status = 0;
	
	unsigned int work_quyanging_status = 0;
	unsigned int work_quyanging_finish = 0;
	unsigned int work_quyang_back_status = 0;
	unsigned int work_quyang_back_finish = 0;
	unsigned int work_quyang_start_status = 0;

	
	unsigned int pre_dianyang_allow = 0;
	unsigned int pre_dianyang_status = 0;
	
	unsigned int work_pre_dianyang_x_status = 0;
	unsigned int work_pre_dianyang_x_finish = 0;
	
	unsigned int work_pre_dianyang_y_status = 0;
	unsigned int work_pre_dianyang_y_finish = 0;
	
	unsigned int work_pre_dianyang_x_monitor_status = 0;
	unsigned int work_pre_dianyang_y_monitor_status = 0;
	unsigned int work_pre_dianyang_back_monitor_status = 0;
	
	unsigned int work_pre_dianyanging_status = 0;
	unsigned int work_pre_dianyanging_finish = 0;
	unsigned int work_pre_dianyang_back_status = 0;
	unsigned int work_pre_dianyang_back_finish = 0;
	unsigned int work_pre_dianyang_start_status = 0;
	
	unsigned int work_pre_dianyang_w_status = 0;
	unsigned int work_pre_dianyang_w_finish = 0;
	unsigned int work_pre_dianyang_w_monitor_status = 0;
	
	
	unsigned int zhangan_allow = 0;
	unsigned int zhangan_status = 0;
	
	unsigned int work_zhangan_x_status = 0;
	unsigned int work_zhangan_x_finish = 0;
	
	unsigned int work_zhangan_y_status = 0;
	unsigned int work_zhangan_y_finish = 0;
	
	unsigned int work_zhangan_x_monitor_status = 0;
	unsigned int work_zhangan_y_monitor_status = 0;
	unsigned int work_zhangan_back_monitor_status = 0;
	
	unsigned int work_zhanganing_status = 0;
	unsigned int work_zhanganing_finish = 0;
	unsigned int work_zhangan_back_status = 0;
	unsigned int work_zhangan_back_finish = 0;
	unsigned int work_zhangan_start_status = 0;
	
	unsigned int work_zhangan_w_status = 0;
	unsigned int work_zhangan_w_finish = 0;
	unsigned int work_zhangan_w_monitor_status = 0;
	
	unsigned int work_zhangan_w_back_status = 0;
	unsigned int work_zhangan_w_back_monitor_status = 0;
	unsigned int work_zhangan_w_back_finish = 0;
	
	unsigned int work_zhangan_x_back_status = 0;
	unsigned int work_zhangan_x_back_monitor_status = 0;
	unsigned int work_zhangan_x_back_finish = 0;
	
	unsigned int dianyang_allow = 0;
	
	unsigned int dianyang_status = 0;

	
	unsigned int dianyang_c_status = 0;
	
	unsigned int work_dianyang_x_s_status = 0;
	unsigned int work_dianyang_x_s_finish = 0;
	unsigned int work_dianyang_x_s_monitor_status = 0;
	
	unsigned int work_dianyang_x_m_status = 0;
	unsigned int work_dianyang_x_m_finish = 0;
	unsigned int work_dianyang_x_m_monitor_status = 0;

	unsigned int work_dianyang_x_l_status = 0;
	unsigned int work_dianyang_x_l_finish = 0;
	unsigned int work_dianyang_x_l_monitor_status = 0;
	
	unsigned int work_dianyang_w_s_lie_status = 0;
	unsigned int work_dianyang_w_s_lie_finish = 0;
	unsigned int work_dianyang_w_s_lie_monitor_status = 0;
		
	unsigned int work_dianyang_x_s_hang_status = 0;
	unsigned int work_dianyang_x_s_hang_finish = 0;
	unsigned int work_dianyang_x_s_hang_monitor_status = 0;		
		
	
	unsigned int work_dianyang_w_m_lie_status = 0;
	unsigned int work_dianyang_w_m_lie_finish = 0;
	unsigned int work_dianyang_w_m_lie_monitor_status = 0;

	unsigned int work_dianyang_w_l_lie_status = 0;
	unsigned int work_dianyang_w_l_lie_finish = 0;
	unsigned int work_dianyang_w_l_lie_monitor_status = 0;
	
	unsigned int work_dianyang_y_down_status = 0;
	unsigned int work_dianyang_y_down_finish = 0;	
	unsigned int work_dianyang_y_down_monitor_status = 0;
	
	unsigned int work_dianyang_y_up_status = 0;
	unsigned int work_dianyang_y_up_finish = 0;	
	unsigned int work_dianyang_y_up_monitor_status = 0;
	

	
	unsigned int work_dianyanging_s_status = 0;
	unsigned int work_dianyanging_s_finish = 0;
	unsigned int work_dianyanging_m_status = 0;
	unsigned int work_dianyanging_m_finish = 0;	
	unsigned int work_dianyanging_l_status = 0;
	unsigned int work_dianyanging_l_finish = 0;
	
	
	unsigned int work_dianyang_back_status = 0;
	unsigned int work_dianyang_back_finish = 0;
	unsigned int work_dianyang_start_status = 0;
	
	unsigned int work_dianyang_start_c_status = 0;
	
	unsigned int work_dianyang_w_s_status = 0;
	unsigned int work_dianyang_w_s_finish = 0;
	unsigned int work_dianyang_w_s_monitor_status = 0;
	
	unsigned int work_dianyang_w_m_status = 0;
	unsigned int work_dianyang_w_m_finish = 0;
	unsigned int work_dianyang_w_m_monitor_status = 0;
	
	unsigned int work_dianyang_w_l_status = 0;
	unsigned int work_dianyang_w_l_finish = 0;
	unsigned int work_dianyang_w_l_monitor_status = 0;
	
	
	unsigned int work_dianyang_w_back_status = 0;
	unsigned int work_dianyang_w_back_monitor_status = 0;
	unsigned int work_dianyang_w_back_finish = 0;
	
	unsigned int work_dianyang_x_back_status = 0;
	unsigned int work_dianyang_x_back_monitor_status = 0;
	unsigned int work_dianyang_x_back_finish = 0;
	
	unsigned int work_dianyang_allow = 0;
	
	unsigned int work_dianyang_x_l_dianyang_status = 0;
	unsigned int work_dianyang_x_l_lock_status = 0;
	
	unsigned int work_dianyang_again_status = 0;
	unsigned int work_dianyang_again_finish = 0;
	unsigned int work_dianyang_again_counter = 0;
	//上电回零工作标志位
	unsigned int start_once_status = 0;
	
	unsigned int work_dianyang_x_get_zero_status = 0;
	unsigned int work_dianyang_x_get_zero_finish = 0;
	unsigned int work_dianyang_x_get_zero_monitor_status = 0;

	unsigned int work_dianyang_w_get_zero_status = 0;
	unsigned int work_dianyang_w_get_zero_finish = 0;
	unsigned int work_dianyang_w_get_zero_monitor_status = 0;
	
	
	
	//连续点样标志位_c 即continuous
	unsigned int work_dianyang_c_x_s_status = 0;
	unsigned int work_dianyang_c_x_s_finish = 0;
	unsigned int work_dianyang_c_x_s_monitor_status = 0;
	
	unsigned int work_dianyang_c_x_s_hang_status = 0;
	unsigned int work_dianyang_c_x_s_hang_finish = 0;
	unsigned int work_dianyang_c_x_s_hang_monitor_status = 0;
	
	unsigned int work_dianyang_c_x_m_status = 0;
	unsigned int work_dianyang_c_x_m_finish = 0;
	unsigned int work_dianyang_c_x_m_monitor_status = 0;

	unsigned int work_dianyang_c_x_l_status = 0;
	unsigned int work_dianyang_c_x_l_finish = 0;
	unsigned int work_dianyang_c_x_l_monitor_status = 0;
	
	unsigned int work_dianyang_c_w_s_status = 0;
	unsigned int work_dianyang_c_w_s_finish = 0;
	unsigned int work_dianyang_c_w_s_monitor_status = 0;
	
	unsigned int work_dianyang_c_w_m_status = 0;
	unsigned int work_dianyang_c_w_m_finish = 0;
	unsigned int work_dianyang_c_w_m_monitor_status = 0;
	
	unsigned int work_dianyang_c_w_l_status = 0;
	unsigned int work_dianyang_c_w_l_finish = 0;
	unsigned int work_dianyang_c_w_l_monitor_status = 0;
	
	
	unsigned int work_dianyang_c_w_back_status = 0;
	unsigned int work_dianyang_c_w_back_monitor_status = 0;
	unsigned int work_dianyang_c_w_back_finish = 0;
	
	unsigned int work_dianyang_c_x_back_status = 0;
	unsigned int work_dianyang_c_x_back_monitor_status = 0;
	unsigned int work_dianyang_c_x_back_finish = 0;
	
	unsigned int work_dianyang_c_y_down_status = 0;
	unsigned int work_dianyang_c_y_down_finish = 0;	
	unsigned int work_dianyang_c_y_down_monitor_status = 0;
	
	unsigned int work_dianyang_c_y_up_status = 0;
	unsigned int work_dianyang_c_y_up_finish = 0;	
	unsigned int work_dianyang_c_y_up_monitor_status = 0;
	
	unsigned int work_dianyang_c_w_start_status = 0;
	unsigned int work_dianyang_c_w_start_monitor_status = 0;
	unsigned int work_dianyang_c_w_start_finish = 0;
	
	unsigned int work_dianyang_c_start = 0;
	unsigned int c_m_move_allow = 0;
	unsigned int work_dianyang_c_start_status = 0;
	
	unsigned int c_jiance_lieshu_status = 0;
	unsigned int c_l_move_allow = 0;

	unsigned int work_dianyang_c_working_finish = 0;
	
	unsigned int work_dianyang_c_w_stop_status = 0;
	unsigned int work_dianyang_c_w_stop_status_monitor = 0;
	unsigned int work_dianyang_c_w_stop_finish = 0;
	
	
	unsigned int tmp_dianyang_jiance_hangshu_last_status = 0;
	unsigned int c_s_move_allow = 0;
	
//点样仪函数功能模块实现

void xitong_position_init(void)
{
	gongzuo_x_t = 0;
	gongzuo_y_t = 0;
	gongzuo_w_t = 0;
		
	clean_x_t = 0;
	clean_y_t = 0;
	clean_w_t = 0;
		
	quyang_x_t = 0;
	quyang_y_t = 0;
	quyang_w_t = 0;
		
	zhangan_x_t = 0;
	zhangan_y_t = 0;
	zhangan_w_t = 0;
		
	pingshan_x_t = 0;
	pingshan_y_t = 0;
	pingshan_w_t = 0;
		
	tuye_x_t = 0;
	tuye_y_t = 0;
	tuye_w_t = 0;
	

	
}
void button_huchi(unsigned char* button0, unsigned char* button1, unsigned int* status_record,  unsigned int condition_flag)
{
	
	if(*button0 == 1 || *button1 ==1)
	{
		if(*status_record == 0)
		{
				if(*button1 == 1)
				{
					*button0 =0;
					*status_record = 1;
				}
		}
		
		else 
		{
			if(*button0 == 1)
			{
				*button1 = 0;
				*status_record = 0;
			}
		}
		condition_flag = 1;		//condition_flag用于判断点动同时停和启动条件
	}
	
	else if((*button0 == 0) && (*button1 == 0))		//此处修改= 为== 之前有逻辑小错误。2017.2.7 下午进行测试
	{
		
		*status_record = 0;
		condition_flag = 0;
		
	}
	
	
}

 void button_3_huchi(unsigned char* button0,unsigned char* button1, unsigned char* button2,unsigned int* status_record1,unsigned int* status_record2)
{ 
	if(*button0 ==1 || *button1 == 1 || *button2 == 1)
	{
		if(*status_record1 == 0 && *status_record2 == 0)
		{
			if(*button0 == 1)
			{
				*button1 = 0;
				*button2 = 0;
				*status_record1 = 1;
				*status_record2 = 0;
			}
			
			else if(*button1 == 1 && *button0 ==0)
			{
				*button2 = 0;
				*status_record1 = 0;
				*status_record2 = 1;
			}
			
			else if(*button2 == 1 && *button1 == 0 && *button0 ==0)
			{
				*status_record1 = 1;
				*status_record2 = 1;
			}
			
		}
		
		else if(*status_record1 == 1 && *status_record2 == 0)
		{
			if (*button1 == 1)
			{
				*button0 = 0;
				*button2 = 0;
				*status_record1 = 0;
				*status_record2 = 1;
			}

			else if (*button2 == 1 && *button1 == 0)
			{
				*button0 = 0;
				*status_record1 = 1;
				*status_record2 = 1;
			}
		}	
		
		
		else if(*status_record1 == 0 && *status_record2 == 1)
		{
			if(*button2 == 1)
			{
				*button1 = 0;
				*button0 = 0;
				*status_record1 = 1;
				*status_record2 = 1;
			}
			
			
			else if(*button2 == 0 && *button0 == 1)
			{
				*button1 = 0;
				*status_record1 = 1;
				*status_record2 = 0;
			}
		}
		
		else if(*status_record1 == 1 && *status_record2 == 1)
		{
			if(*button0 == 1)
			{
				*button1 = 0;
				*button2 = 0;
				*status_record1 = 1;
				*status_record2 = 0;
			}
			
			else if(*button1 == 1 && *button0 == 0)
			{
				*button0 = 0;
				*button2 = 0;
				*status_record1 = 0;
				*status_record2 = 1;
			}
		}
		
	  }
	
	  else
	  {
		  *status_record1 = 0;
		  *status_record2 = 0;
	  }
	}

void parameter_init(void)//第一次上电初始化
{
	if (init_flag != 1)
	{
		set_speed_number_tmp = 0;
		set_speed_number = 0;
		
		init_flag = 1;
		
	}
}

