#include "DWS.h"


void turn_yellow(){
	printf("%c[1;33m",27);
	sleep(2);
	system("reset");
}

void current(){
	current_time =time(NULL);
	struct tm current_tm=*localtime(&current_time);
	system("clear");
	printf("현재시간: %d-%d-%d %d:%d:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
}
void turn_on(){
	
}
void main(){
	//
	alarm_info alarm;
	alarm.alarm_power = false;
	alarm.info = false;
	// 초기 시간 설정 바꾸기
	current_time =time(NULL);
	struct tm current_tm=*localtime(&current_time);
	
	while(1){
		if(kbhit()==1){
			btn=getch();
		}
		// Beep Controller
		if(alarm.alarm_power==true && alarm.hour==current_tm.tm_hour && alarm.min== current_tm.tm_min){
			
		}else
		// Main Controller
		{
			if(mo_info==0 && btn=='c') { time_mode(); }
			else if(mo_info==TIME_MODE)
			{
				if(st_info==0 && btn=='a') { sec_set(); }
				if(st_info==SEC_SET && btn=='c') { hour_set(); }
				if(st_info==HOUR_SET && btn=='c') { minute_set(); }
				if(st_info==MINUTE_SET && btn=='c') { year_set(); }
				if(st_info==YEAR_SET && btn=='c') { month_set(); }
				if(st_info==MONTH_SET && btn=='c') { day_set(); } 
				if(st_info==DAY_SET && btn=='c') { sec_set(); }
				if(st_info==DAY_SET && btn=='a') { time_mode(); }
				//if(btn=='b' && !max) { plus_one(st_info); }
				//if(btn=='b' && max) { set_min(st_info); }
			}

			else if(mo_info==TIME_MODE && btn=='c') { alarm_mode(); }
			else if(mo_info==ALARM_MODE)
			{
				if(btn=='b') { alarm_indicator(); }
			
			}

		}
		// Backlight Controller
		if(btn=='d'){
			turn_yellow();
		}
	current();
	sleep(1);
	}

}
