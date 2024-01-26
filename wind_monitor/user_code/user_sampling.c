#include "user_sampling.h"
#include "sys.h"
#include "os.h"

#include "gui_history.h"
#include "gui_menu.h"
#include "gui_title.h"

#include "led.h"
#include "adc.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "flash.h"
#include "user_store.h"


static uint8_t __g_single = 1;//单次运行标志
static void __single_update(uint8_t mode);
static void printf_info(uint16_t dire,uint8_t speed);
    
static uint16_t __g_dire = 0;
static uint8_t count = 0;
static uint8_t speed_count = 0; //速度采样计数值，没500ms加一次
static uint8_t dire_count  = 0; //方向采样计数值，没500ms加一次
static uint8_t speed_samp  = 2; //速度采样周期值 = speed_samp * 500ms  默认一秒钟
static uint8_t dire_samp   = 2; //方向采样周期值 = dire_samp  * 500ms  默认一秒钟
    
static uint8_t state = 0;//0：代表着实时显示的界面；1：代表历史数据显示

static uint16_t g_speed_count = 0;
static float __g_speed_temp = 0;
static uint16_t __g_speed = 0;

//flash存储方式：0：数据首页位置，256：数据缓冲开始
static uint8_t *p_data_buf_temp;     //100组数据缓冲区 速度-方向
static uint8_t data_buf_index = 0;  //数据首页位置（以组为单位） 
static uint8_t __g_data_num = 0;    //数据有效组数


static uint8_t buf_show[30];//用于显示最多一页数据的缓存

static uint8_t __g_now_page = 1;
static uint8_t __g_all_page = 1;

static int __sampling_single(void)
{
    if(__g_single == 0) return 0;
    speed_count = 0;
    dire_count = 0;
    count = 0;
    g_speed_count = 0;
    __g_single = 0;
    return 1;
}

//显示指定页的内容
static void __show_data(uint8_t now_page)
{
    uint8_t i = 0;
    uint16_t index = ((data_buf_index == 0) ? 99 :(data_buf_index-1));               //得出当前最新的标志
    uint8_t size = ((now_page < __g_all_page)? 10 : (__g_data_num + 10 - now_page * 10)); //计算出当前页面有的组数
   
    now_page %= __g_all_page + 1;  
    
    if (index >= (now_page * 10 - 10))    //获取指定页数据在buf中的标志
        index = index - (now_page * 10 - 10);
    else 
        index = 100 - ((now_page * 10 - 10) - index);
    for (i = 0; i < size;i++) {
        
        buf_show[i*3] = p_data_buf_temp[index*3];
        buf_show[i*3+1] = p_data_buf_temp[index*3+1];
        buf_show[i*3+2] = p_data_buf_temp[index*3+2];
        
        printf_info((uint16_t)buf_show[i*3+1] * 256 + buf_show[i*3+2],buf_show[i*3]);
        
        if (index == 0) index = 99;
        else index --;
    }
  
    gui_history_dataupdata(buf_show,size, now_page, __g_all_page);    
}

//读取出来eeprom中存储的数据总数量和第一页的数据 
static int __history_single(void)
{
    
    if(__g_single == 0) return 0;
	p_data_buf_temp = store_init(&data_buf_index, &__g_data_num);
    
    __g_all_page = ((__g_data_num%10 == 0)?(__g_data_num/10):(__g_data_num/10+1));  
    if (__g_all_page == 0) __g_all_page = 1;
    
    __g_now_page = 1;
    __show_data(1);
  
    __g_single = 0; 
    return 1;	
}


//持续读取uid并更新到界面
//持续读取是否需要保存数据
//采样
//十秒存储一次数据
static void __sampling_circle(void)
{
    OS_ERR err;
    dire_samp  = gui_dire_time_get() * 2;   //获取方向采样时间
    speed_samp = gui_speed_time_get() * 2;  //获取速度采样时间
    
    
    speed_count++;
    dire_count++;
    count++;
    if (speed_count >= speed_samp) {  
        //代表计数值一到开始速度采样
        __g_speed = (uint16_t)(__g_speed_temp * 10);
        gui_speed_update(__g_speed);
        speed_count = 0;
    }
    
    if (dire_count >= dire_samp) {
        //代表计数值一到开始方向采样
        __g_dire = Get_Adc(14);
        __g_dire = (uint16_t)(__g_dire * 0.116);
        __g_dire %= 360;
        
        gui_dire_update(__g_dire);
        dire_count = 0;
    }
    if (count >= 10) {
        LED0 = 0;
        printf_info(__g_dire,__g_speed);
        p_data_buf_temp[data_buf_index * 3]     = __g_speed;
        p_data_buf_temp[data_buf_index * 3 + 1] = __g_dire / 256;
        p_data_buf_temp[data_buf_index * 3 + 2] = __g_dire % 256;
        
        data_buf_index++;
        data_buf_index %= 100;
        if (__g_data_num < 100) __g_data_num++;
    
        store(data_buf_index, __g_data_num);
        count = 0;
        
        LED0 = 1;
    }
    
    if (count % 2) {
        if (g_speed_count!= 0)
            __g_speed_temp = (float)g_speed_count * 0.0875f + 0.1f;
        else 
            __g_speed_temp = 0.0f;
        g_speed_count = 0;
    }
    
    OSTimeDlyHMSM(0,0,0,450,OS_OPT_TIME_PERIODIC,&err);
}

//持续读取uid并更新到界面
//持续读取是否需要保存数据
static void __history_circle(void)
{
    OS_ERR err;
    uint8_t state = gui_gistory_state_get();
    
    if (state == 1) {
        __g_now_page = ((__g_now_page > 1)? (__g_now_page - 1):__g_all_page);
        __show_data(__g_now_page);
    } else if (state == 2){
        __g_now_page = ((__g_now_page < __g_all_page)? (__g_now_page + 1):1);
        __show_data(__g_now_page);
    }
    
	OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);
}
void sampling_entry(void)
{
	OS_ERR err;
    
      
    speed_count_set(&g_speed_count);
	p_data_buf_temp = store_init(&data_buf_index, &__g_data_num);
    if(KEY0 == 0) {
        printf("111");
        data_buf_index = 0;
        __g_data_num = 0;
        store(data_buf_index, __g_data_num);
    }
	while(1)
	{

        state = gui_state_get();   //更新界面状态
        switch(state) {
            case 0 :                           
                __sampling_single();
				__sampling_circle();
                break;
            case 1 :
                __history_single();
				__history_circle();
                break;
            default:
                break;
        }

        __single_update(state);
		
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_PERIODIC,&err);
	}    
    
}
static void __single_update(uint8_t mode)
{
    static uint8_t pre_mode = 0;
    
    if (pre_mode != mode) {
        __g_single = 1;
        pre_mode = mode;
    }
}
static void printf_info(uint16_t dire,uint8_t speed)
{
    printf("dire:%d,speed:%d\r\n",dire,speed);
}
