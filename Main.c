#include "DWS.h"




void main() {
	// alarm
	alarm_information alarm_info;
	alarm_info.alarm_power = false;
	alarm_info.info = false;
	alarm_info.hour=0;
	alarm_info.min=0;

	// stopwatch
	stop_min=0;
	stop_sec=0;
	stop_milisec=0;
	
	// backlight
	bl_flag==false;
	// 초기 시간 설정 바꾸기
	current_time = 1546268400;
	current_tm = localtime(&current_time);

	while (1) {
		current();
		// Beep Controller
		if (alarm_info.alarm_power == true && alarm_info.hour == current_tm->tm_hour && alarm_info.min == current_tm->tm_min) {
		}
		else {

			// Main Controller

			if (mo_info == TIME_MODE) {

				if(st_info == 0 ){time_mode();}
				if (st_info == SEC_SET) {  sec_set(); }
				if (st_info == HOUR_SET) { hour_set(); }
				if (st_info == MINUTE_SET) { minute_set(); }
				if (st_info == YEAR_SET) { year_set(); }
				if (st_info == MONTH_SET) { month_set(); }
				if (st_info == DAY_SET) { day_set(); }
				sleep(1);

			}
			else if (mo_info == ALARM_MODE) {

				if(st_info == 0){alarm_mode();}
				if (st_info == AL_HOUR_SET) { hour_set(); }
				if (st_info == AL_MINUTE_SET ) { minute_set(); }
				sleep(1);

			}
			else if (mo_info == STOPWATCH_MODE){
				
				if(st_info == 0){stopwatch_mode();}
				if(st_info == START){start();}	
				if(st_info == LAP_TIME){lap_time();}
				if(st_info == STOP){stop();}
				sleep(1);
			}

		}
		// Backlight Controller
		if (btn == 'd'|| bl_flag == true) {
			turn_yellow();
		}
		
		display(display_command);
}

}
