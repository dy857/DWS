#include "DWS.h"


void turn_yellow(){
	printf("%c[1;33m",27);
	sleep(5);
	system("reset");
}

void current(){
	system("clear");
	printf("현재시간: %d-%d-%d %d:%d:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
}
void turn_on(){
	
}
void main(){
	//
	alarm_info.alarm_power=false;
	alarm_info.info=false;
	// 초기 시간 설정 바꾸기
	current_time =time(NULL);
	struct tm current_tm=*localtime(&current_time);
	
	while(1){
		if(kbhit()==1){
			btn=getch();
		}
		// Beep Controller
		if(alarm_info.alarm_power==on && alarm_info.hour==current_tm.tm_hour && alarm_info.min== current_tm.tm_min){
			
		}else
		// Main Controller
		{
			
		}
		// Backlight Controller
		if(btn=='d'){
			turn_yellow();
		}
	current();
	sleep(1)
	}

}
