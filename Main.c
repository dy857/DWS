#include "DWS.h"

void main() {

	//alarm information
	alarm_information alarm_info;
	alarm_info.alarm_power = false;
	alarm_info.display_alarm_indicator = ' ';
	alarm_info.beep_time = 0;
	alarm_time = 1546268400;
	alarm_tm = *localtime(&alarm_time);

	// stopwatch
	stop_min=0;
	stop_sec=0;
	stop_milisec=0;
	
	// backlight
	backlight_time = 0;

	// 초기 시간 설정 바꾸기
	current_time = 1546268400;
	current_tm = *localtime(&current_time);


	while (1) {

		// Beep Controller
		if (al_info == TURN_OFF) turn_off(); 
		if (al_info == TURN_ON) turn_on(); 
			

		// Main Controller
		if (mo_info == TIME_MODE) {
			
			if (st_info == 0 ) time_mode();
			if (st_info == SEC_SET) sec_set();
			if (st_info == HOUR_SET) hour_set();
			if (st_info == MINUTE_SET) minute_set();
			if (st_info == YEAR_SET) year_set();
			if (st_info == MONTH_SET) month_set();
			if (st_info == DAY_SET) day_set();

		}
		if (mo_info == ALARM_MODE) {

			if (st_info == 0) alarm_mode();
			if (st_info == AL_HOUR_SET) hour_set();
			if (st_info == AL_MINUTE_SET ) minute_set();

		}
		if (mo_info == STOPWATCH_MODE){
			
			if(st_info == 0) stopwatch_mode();
			if(st_info == START) start();	
			if(st_info == LAP_TIME) lap_time();
			if(st_info == STOP) stop();

		}


		// Backlight Controller
		if (bl_info == 0) idle(); 
		if (bl_info == TURN_YELLOW) turn_yellow();
		
		display(display_command);
	}

}
