#include "ch.h"
#include "hal.h"
#include "datetime.h"
#include "chrtclib.h"
#include <string.h>
#define  DEVICE_STM32_RTC_EN 1
#if (DEVICE_STM32_RTC_EN > 0)
#define DEV_NAME "rtc_stm32"

RTC_Device stm32rtc;

RTCTime rt;
static bool_t stm32_get_datetime(TDateTime *dt)
{
	if(dt){

		rtcGetTime(&RTCD1,&rt);
		
		datetime_convert(rt.tv_sec,dt);
		#if 0
		dt->sec  = mytime.tm_sec;
		dt->min  = mytime.tm_min;
		dt->hour = mytime.tm_hour;
		dt->day  = mytime.tm_mday;
		dt->mon  = mytime.tm_mon;
		dt->year = mytime.tm_year;
		#endif
		return TRUE;
	}
	return FALSE;
}
static bool_t stm32_set_datetime(TDateTime *dt)
{
	if(dt){	
		rt.tv_sec = datetime_mktime(dt);			
		rtcSetTime(&RTCD1,&rt);
		return TRUE;
	}
	return FALSE;
}

int stm32_rtc_init()
{
		
	memset(&stm32rtc, 0 , sizeof(RTC_Device));
	
	strncpy(stm32rtc.name,DEV_NAME,MAX_RTC_DEV_NAME);
	
	stm32rtc.get_datetime = stm32_get_datetime;
	stm32rtc.set_datetime = stm32_set_datetime;
	
	register_rtc(&stm32rtc);
	
	return 1;
}
//device_initcall(stm32_rtc_init);
#endif
