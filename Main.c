#include "DWS.h"


void turn_yellow() {
	printf("%c[1;33m", 27);
	sleep(2);
	system("reset");
}

void turn_on() {

}


void main() {
	//
	alarm_info alarm;
	alarm.alarm_power = false;
	alarm.info = false;
	// 초기 시간 설정 바꾸기
	current_time = time(NULL);
	struct tm current_tm = *localtime(&current_time);

	while (1) {
		
		// Beep Controller
		if (alarm.alarm_power == true && alarm.hour == current_tm.tm_hour && alarm.min == current_tm.tm_min) {

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

			}
			else if (mo_info == ALARM_MODE) {

				if(st_info == 0){alarm_mode();}
				if (st_info == HOUR_SET) { hour_set(); }
				if (st_info == MINUTE_SET ) { minute_set(); }
				if (btn == 'b') { alarm_indicator(); }

			}
			else if (mo_info == STOPWATCH_MODE && btn == 'c') { time_mode(); }

		}
		// Backlight Controller
		if (btn == 'd') {
			turn_yellow();
		}
		display(display_command);
		sleep(1);
	}

}