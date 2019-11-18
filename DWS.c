#include "DWS.h"

int st_info = 0;
int al_info = TURN_OFF;
int mo_info = TIME_MODE;
int bl_info = 0;

alarm_information alarm_info;

int display_command = 0;
char* week_day[]={"SU", "MO", "TU", "WE", "TH", "FR", "SA"};

int date(int year, int month)
{
	int mdays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))//윤년 판단 
	{
		mdays[1] = 29;//2월달의 날 수를 29로 설정 
	}

	//month는 mdays의 인덱스로 사용해서 실제 출력할 때는 1을더해서 출력합니다. 
	int day = mdays[month];
	return day;
}

void current() 
{
	current_tm.tm_sec++;
	if(current_tm.tm_sec==60){
		current_tm.tm_sec=0;
		current_tm.tm_min++;
	}
	else if(current_tm.tm_min==60){
		current_tm.tm_min=0;
		current_tm.tm_hour++;
	}
	else if(current_tm.tm_hour==24){
		current_tm.tm_hour=0;
		if(current_tm.tm_wday==6){
			current_tm.tm_wday=0;
		}else{
			current_tm.tm_mday++;
			current_tm.tm_wday++;
		}
	}
	else if(current_tm.tm_mday==date(current_tm.tm_year, current_tm.tm_mon)){
		current_tm.tm_mday=0;
		current_tm.tm_mon++;
	}
	else if(current_tm.tm_mon==12){
		current_tm.tm_mon=1;
		current_tm.tm_year++;
	}
	else if(current_tm.tm_year==2099){
		current_tm.tm_year=2019;
	}
}

void time_mode()
{
	//button input
	if (kbhit() == 1) 
	{
		if (btn == 'a') {
			st_info = SEC_SET;
		}
		if (btn == 'c') {
			mo_info = ALARM_MODE;
		}
	}
	display_command = PRINT_TIME_MODE;
}

void sec_set()
{
	//button input
	if (kbhit() == 1) 
	{
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			if (current_tm.tm_sec == 59) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c') {
			st_info = HOUR_SET;
		}

	}
	//display
	display_command = PRINT_SEC_SET;
	printf("초\n");
}

void hour_set()
{
	//button input
	if (kbhit() == 1) 
	{
		//TIME_MODE
		if (btn == 'a' && mo_info == TIME_MODE) {
			st_info = 0;
		}
		if (btn == 'b' && mo_info == TIME_MODE) {
			if (current_tm.tm_hour == 23) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c' && mo_info == TIME_MODE) {
			st_info = MINUTE_SET;
		}

		//ALARM_MODE
		if (btn == 'a' && mo_info == ALARM_MODE) {
                     		st_info = 0;
			alarm_info.alarm_power = true;
			alarm_info.display_alarm_indicator = 'I';
               	}
		if (btn == 'b' && mo_info == ALARM_MODE){
                    		if (alarm_tm.tm_hour == 23) set_min(st_info);
                        		else plus_one(st_info);
                }
		if (btn == 'c' && mo_info == ALARM_MODE) {
              			st_info = AL_MINUTE_SET;
                }

	}
	//display
	if(mo_info==TIME_MODE) {display_command = PRINT_HOUR_SET;}
	if(mo_info==ALARM_MODE) {display_command = PRINT_AL_HOUR_SET;}
	printf("시간\n");
}

void minute_set()
{
	//button input
	if (kbhit() == 1) 
	{
		//TIME_MODE
		if (btn == 'a' && mo_info == TIME_MODE) {
			st_info = 0;
		}
		
		if (btn == 'b' && mo_info == TIME_MODE) {
			if (current_tm.tm_min == 59) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c' && mo_info == TIME_MODE) {
			st_info = YEAR_SET;
		}

		//ALARM_MODE
		if (btn == 'a' && mo_info == ALARM_MODE) {
                        		st_info = 0;
			alarm_info.alarm_power = true;
			alarm_info.display_alarm_indicator = 'I';
               	 }
		if (btn == 'b' && mo_info == ALARM_MODE){
			if (alarm_tm.tm_hour == 59) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c' && mo_info == ALARM_MODE) {
			st_info = AL_HOUR_SET;
		}

	}
	//display
	if(mo_info==TIME_MODE) {display_command = PRINT_MINUTE_SET;}
        	if(mo_info==ALARM_MODE) {display_command = PRINT_AL_MINUTE_SET;}
	printf("분\n");
}

void year_set()
{
	//button input
	if (kbhit() == 1) 
	{
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			if (current_tm.tm_year == 199) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c') {
			st_info = MONTH_SET;
		}
	}
	//display
	display_command = PRINT_YEAR_SET;
	printf("연\n");
}

void month_set()
{
	//button input
	if (kbhit() == 1) 
	{
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			if (current_tm.tm_mon == 12) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c') {
			st_info = DAY_SET;
		}
	}
	//display
	display_command = PRINT_MONTH_SET;
	printf("달\n");
}

void day_set()
{
	//button input
	if (kbhit() == 1) 
	{
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			//달 별로 일 수가 다르기 때문에 date함수를 구현해 맞는 max_day를 넣어주었습니다.
			if (current_tm.tm_mday == date(current_tm.tm_year, current_tm.tm_mon)) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c') {
			st_info = SEC_SET;
		}
	}
	//display
	display_command = PRINT_DAY_SET;
	printf("일\n");
}

void plus_one(int st_info)
{
	switch (st_info)
	{
		case SEC_SET: 
			current_tm.tm_sec++; break;
		case HOUR_SET: 
			current_tm.tm_hour++; break;
		case MINUTE_SET: 
			current_tm.tm_min++; break;
		case YEAR_SET: 
			current_tm.tm_year++; break;
		case MONTH_SET: 
			current_tm.tm_mon++; break;
		case DAY_SET:
			current_tm.tm_mday++;
			if(current_tm.tm_wday==6) current_tm.tm_wday=0;
			else current_tm.tm_wday++;		
			break;
		case AL_HOUR_SET: 
			alarm_tm.tm_hour++; break;
		case AL_MINUTE_SET: 
			alarm_tm.tm_min++; break;
		default: break;
	}
}

void set_min(int st_info)
{
	switch (st_info)
	{
		case SEC_SET:
			current_tm.tm_sec = 0;
			break;
		case HOUR_SET:
			current_tm.tm_hour = 0;
			break;
		case MINUTE_SET:
			current_tm.tm_min = 0;
			break;
		case YEAR_SET:
			current_tm.tm_year = 2019;
			break;
		case MONTH_SET:
			current_tm.tm_mon = 1;
			break;
		case DAY_SET:
			current_tm.tm_mday = 1;
			break;
		case AL_HOUR_SET:
			alarm_tm.tm_hour = 0;
			break;
		case AL_MINUTE_SET:
			alarm_tm.tm_min = 0;
			break;
		default: break;
	}
}

void alarm_mode()
{
	//button input
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info =AL_HOUR_SET;
		}
		if (btn == 'b') {
			alarm_indicator();
		}
		if (btn == 'c') {
			mo_info = STOPWATCH_MODE;
		}
	}
		//display
		display_command = PRINT_ALARM_MODE;
}

void alarm_indicator()
{
	if(alarm_info.alarm_power == true){
		alarm_info.alarm_power=false;
		alarm_info.display_alarm_indicator = ' ';
	}else{
		alarm_info.alarm_power=true;
		alarm_info.display_alarm_indicator = 'I';
	}
	//printf("indicator state : %d\n", alarm_info.alarm_power);
}

void stopwatch_mode()
{
	//button input
	if (kbhit() == 1) {
		if (btn == 'b') {
			st_info=START;
		}
		if (btn == 'c') {
                       		mo_info = TIME_MODE;
                	}
	}
	
	//display
	display_command = PRINT_STOPWATCH_MODE;
	printf("stopwatch\n");
}	

void start()
{
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info=LAP_TIME;
		}
		if (btn == 'b') {
			st_info=STOP;
		}
	}

	//display
	display_command = PRINT_START;
	start_time=clock();
//	stop_sec=start_time/CLOCKS_PER_SEC;
//	stop_min=start_time/CLOCKS_PER_SEC %60;
//	printf("%0.2f,%d",stop_sec, stop_min);
	stop_sec=start_time/CLOCKS_PER_SEC;
	stop_milisec=start_time/1000/CLOCKS_PER_SEC;
	stop_min=stop_sec/60;
}

void lap_time()
{
	//button input
	if (kbhit() == 1) {
		if (btn == 'a') {
			lap_time();
		}
		if (btn == 'b') {
			st_info=START;
		}
	}
		//something to do
		
		//display
		display_command = PRINT_LAP_TIME;
}

void stop()
{
	//button input
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info=0;
		}
		if (btn == 'b') {
			st_info=START;
		}
	}

	//display
	display_command = PRINT_STOP;
}


void turn_off()
{

	if((alarm_info.alarm_power == true) && (alarm_tm.tm_hour == current_tm.tm_hour) && (alarm_tm.tm_min == current_tm.tm_min)) al_info = TURN_ON;
	
		
}

void turn_on()
{	
	//button input
	if(kbhit() == 1) {
		if (btn == 'a' || btn == 'b' || btn == 'c' || btn == 'd' ) {
			alarm_tm = *localtime(&current_time);
			alarm_info.beep_time=0;
			alarm_info.alarm_power=false;
			alarm_info.display_alarm_indicator = ' ';
			al_info = TURN_OFF;
		}
	}

	//display
	if(alarm_info.beep_time<5){
		alarm_info.beep_time++;
		printf("\a");
		sleep(1);
	}

	if(alarm_info.beep_time==5) {
		alarm_tm = *localtime(&current_time);
		alarm_info.beep_time=0;
		alarm_info.alarm_power=false;
		alarm_info.display_alarm_indicator = ' ';
		al_info = TURN_OFF;
	}
	
}

void idle() {
	if (kbhit() == 1) {
		if (btn == 'd') {
			bl_info=TURN_YELLOW;
		}
	}
}

void turn_yellow() {

	if(backlight_time<2) {
		printf("%c[1;33m", 27);
		backlight_time++;
	}
	else {
		backlight_time = 0;
		bl_info=0;
		printf("%c[0m", 27);
	}
}

void btn_input();

int getch()
{
	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}



int kbhit()
{
	struct termios oldt, newt;
	int oldf;	
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	btn = getch();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (btn != EOF){return 1;}
	
	return 0;
}

void display(int display_command)
{
	//if(bl_info==TURN_YELLOW) printf("%c[1;33m", 27);
	switch(display_command) {
		case PRINT_TIME_MODE:
			system("clear");
			printf("%s %c %d-%d-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_SEC_SET:
			system("clear");
			printf("%s %c %d-%d-%d %d:%d:%c[4m%d%c[0m\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, 27, current_tm.tm_sec, 27);
			sleep(1);
			break;
		case PRINT_HOUR_SET:
			system("clear");
			printf("%s %c %d-%d-%d %c[4m%d%c[0m:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, 27, current_tm.tm_hour, 27, current_tm.tm_min, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_MINUTE_SET:
			system("clear");
			printf("%s %c %d-%d-%d %d:%c[4m%d%c[0m:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, 27, current_tm.tm_min, 27, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_YEAR_SET:
			system("clear");
			printf("%s %c %c[4m%d%c[0m-%d-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, 27, current_tm.tm_year + 1900, 27, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_MONTH_SET:
			system("clear");
			printf("%s %c %d-%c[4m%d%c[0m-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, 27, current_tm.tm_mon + 1, 27, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_DAY_SET:
			system("clear");
			printf("%s %c %d-%d-%c[4m%d%c[0m %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, 27, current_tm.tm_mday, 27, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			sleep(1);
			break;
		case PRINT_ALARM_MODE:
			system("clear");
			printf("AL %c %d-%d %d:%d\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, alarm_tm.tm_hour, alarm_tm.tm_min);
			sleep(1);
			break;
		case PRINT_AL_HOUR_SET:
			system("clear");
			printf("AL %c %d-%d %c[4m%d%c[0m:%d\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, 27, alarm_tm.tm_hour, 27, alarm_tm.tm_min);
			sleep(1);
			break;
		case PRINT_AL_MINUTE_SET:
			system("clear");
			printf("AL %c %d-%d %d:%c[4m%d%c[0m\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, alarm_tm.tm_hour, 27, alarm_tm.tm_min, 27);
			sleep(1);
			break;
		case PRINT_STOPWATCH_MODE:
			system("clear");
			printf("ST %d-%d %d:%d:%d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec);
			sleep(1);
			break;
		case PRINT_START:
			system("clear");
			printf("ST %d-%d %d:%d:%d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec);
			sleep(1);
			break;
		case PRINT_STOP:
			system("clear");
			printf("ST %d-%d %d:%d:%d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec);
			sleep(1);
			break;
		case PRINT_LAP_TIME:
			system("clear");
			sleep(1);
			break;
		default: break;
	}
}
