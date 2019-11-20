#include "DWS.h"


alarm_information alarm_info;
char* week_day[]={"SU", "MO", "TU", "WE", "TH", "FR", "SA"};



// 월마다 날짜를 구하는 함수
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

// Current 타이머를 만드는 함수
int createCurrent(timer_t *timerID, int sec, int msec){
	struct sigevent te;
	struct itimerspec its;
	struct sigaction sa;
	int sigNo=SIGRTMIN;

	sa.sa_flags=SA_SIGINFO;
	sa.sa_sigaction = current;
	sigemptyset(&sa.sa_mask);

	if(sigaction(sigNo, &sa, NULL)== -1 ){
		printf("sigaction error\n");
		return -1;
	}
	te.sigev_notify = SIGEV_SIGNAL;  
  	te.sigev_signo = sigNo;  
	te.sigev_value.sival_ptr = timerID;  
	timer_create(CLOCK_REALTIME, &te, timerID);  
   
	its.it_interval.tv_sec = sec;
	its.it_interval.tv_nsec = msec * 1000000;  
	its.it_value.tv_sec = sec;
    
	its.it_value.tv_nsec = msec * 1000000;
	timer_settime(*timerID, 0, &its, NULL);  
   
	return 0;
	
	
}

// 현재 시간을 매초 업데이트하는 프로세스
static void current() 
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

// 현재 시간을 보여주는 프로세스
void time_mode()
{
	
		if (btn == 'a') {
		st_info = SEC_SET;
		}
		if (btn == 'c') {
			mo_info = ALARM_MODE;
		}
	display_command = PRINT_TIME_MODE;
	btn = 0;
}

void sec_set()
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

	//display
	display_command = PRINT_SEC_SET;	
	btn = 0;

}

void hour_set()
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

	
	//display
	if(mo_info==TIME_MODE) {display_command = PRINT_HOUR_SET;}
	if(mo_info==ALARM_MODE) {display_command = PRINT_AL_HOUR_SET;}
	btn = 0;

}

void minute_set()
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

	
	//display
	if(mo_info==TIME_MODE) {display_command = PRINT_MINUTE_SET;}
        	if(mo_info==ALARM_MODE) {display_command = PRINT_AL_MINUTE_SET;}
	btn = 0;

}

void year_set()
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
	
	//display
	display_command = PRINT_YEAR_SET;
	btn = 0;

}

void month_set()
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
	
	//display
	display_command = PRINT_MONTH_SET;
	btn = 0;
}

void day_set()
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

	//display
	display_command = PRINT_DAY_SET;
	btn = 0;
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

		if (btn == 'a') {
			st_info =AL_HOUR_SET;
		}
		if (btn == 'b') {
			alarm_indicator();
		}
		if (btn == 'c') {
			mo_info = STOPWATCH_MODE;
		}
	
		//display
		display_command = PRINT_ALARM_MODE;	
		btn = 0;
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
	
}

void stopwatch_mode()
{
		if (btn == 'b') {
			st_info=START;
		}
		if (btn == 'c') {
                       		mo_info = TIME_MODE;
                	}

	
	// Stopwatch에 필요한 기준값 초기화
	gettimeofday(&st_start, NULL);
	stop_milisec = 0;
	stop_sec = 0;
	stop_min = 0;
	display_command = PRINT_STOPWATCH_MODE;
	btn = 0;
}	

void start()
{
		if (btn == 'a') {
			st_info=LAP_TIME;
		}
		if (btn == 'b') {
			st_info=STOP;
		}


	//display
	gettimeofday(&st_tv, NULL);
	st_tv.tv_sec -= st_start.tv_sec;
	st_stop.tv_sec = st_tv.tv_sec;
	st_tm = *localtime(&st_tv.tv_sec);
	stop_milisec = st_tv.tv_usec/10000;
	stop_sec = st_tm.tm_sec;
	stop_min = st_tm.tm_min;
	display_command = PRINT_START;
	

	btn = 0;
}

void lap_time()
{
		if (btn == 'a') {
			lap_time();
		}
		if (btn == 'b') {
			st_info=START;
		}
	
		
		//display
		
		display_command = PRINT_LAP_TIME;
		btn = 0;
}

void stop()
{
		if (btn == 'a') {
			st_info=0;
		}
		if (btn == 'b') {
			st_info=START;
			gettimeofday(&st_tv, NULL);
			st_tv.tv_sec -= st_start.tv_sec;
			st_start.tv_sec += (st_tv.tv_sec-st_stop.tv_sec);
		}

	//display
	display_command = PRINT_STOP;
	btn = 0;
}


void turn_off()
{

	if((alarm_info.alarm_power == true) && (alarm_tm.tm_hour == current_tm.tm_hour) && (alarm_tm.tm_min == current_tm.tm_min)) al_info = TURN_ON;
	
		
}

void turn_on()
{	
	if (btn == 'a' || btn == 'b' || btn == 'c' || btn == 'd' ) {
		alarm_tm = *localtime(&current_time);
		alarm_info.beep_time=0;
		alarm_info.alarm_power=false;
		alarm_info.display_alarm_indicator = ' ';
		al_info = TURN_OFF;
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
	btn = 0;
}

void idle() {
   if (btn == 'd') {
      bl_info=TURN_YELLOW;
   }
   btn = 0;
}

void turn_yellow() {

   display(PRINT_BACKLIGHT);
	
}


void btn_input();

int getch()
{
   int c[4];
   int max = c[0];
   for(int i = 0; i<4;i++){
      if(max>c[i])max=c[i];
   }
   struct termios oldattr, newattr;

   tcgetattr(STDIN_FILENO, &oldattr);
   newattr = oldattr;
   newattr.c_lflag &= ~(ICANON | ECHO);
   newattr.c_cc[VMIN] = 1;
   newattr.c_cc[VTIME] = 0;
   tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  
   max = getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
   return max;
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


void gotoxy(int x, int y) {

     printf("\033[%d;%df",y,x);

     fflush(stdout);

}



void display(int display_command)
{
	//if(bl_info==TURN_YELLOW) printf("%c[1;33m", 27);
	switch(display_command) {

		case PRINT_BACKLIGHT:
         		if(backlight_time<10) {
            			printf("%c[1;33m", 27);
         		   	backlight_time++;
      			}   
      			else {
            			backlight_time = 0;
            			bl_info=0;
		                printf("%c[0m", 27);
       			}   
   			usleep(100000);
         		break;
		case PRINT_TIME_MODE:
			system("clear");
			gotoxy(70,20);
			printf("%s %c %d-%d-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			usleep(100000);
			break;
		case PRINT_SEC_SET:
			system("clear");
			gotoxy(70,20);
			printf("%s %c %d-%d-%d %d:%d:%c[4m%d%c[0m\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, 27, current_tm.tm_sec, 27);
			usleep(100000);
			break;
		case PRINT_HOUR_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){
				printf("%s %c %d-%d-%d %c[4m%d%c[0m:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, 27, current_tm.tm_hour, 27, current_tm.tm_min, current_tm.tm_sec);
			}else{
				printf("%s %c %d-%d-%d %c[4m%d%c[0m", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, 27, current_tm.tm_hour, 27);
				printf("%c[1;33m:%d:%d%c[0m\n",27, current_tm.tm_min, current_tm.tm_sec, 27);
			}
			usleep(100000);			
			break;
		case PRINT_MINUTE_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){
				printf("%s %c %d-%d-%d %d:%c[4m%d%c[0m:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, 27, current_tm.tm_min, 27, current_tm.tm_sec);
			}else{
				printf("%s %c %d-%d-%d %d:%c[4m%d%c[0m", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, 27, current_tm.tm_min, 27);
				printf("%c[1;33m:%d%c[0m\n",27, current_tm.tm_sec, 27);
			}
			usleep(100000);
			break;
		case PRINT_YEAR_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){
				printf("%s %c %c[4m%d%c[0m-%d-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, 27, current_tm.tm_year + 1900, 27, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			}else{
				printf("%s %c %c[4m%d%c[0m", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, 27, current_tm.tm_year + 1900, 27);
				printf("%c[1;33m-%d-%d %d:%d:%d%c[0m\n", 27, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec,27);
			}
			usleep(100000);
			break;
		case PRINT_MONTH_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){
				printf("%s %c %d-%c[4m%d%c[0m-%d %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, 27, current_tm.tm_mon + 1, 27, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			}else{
				printf("%s %c %d-%c[4m%d%c[0m", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, 27, current_tm.tm_mon + 1, 27);
				printf("%c[1;33m-%d %d:%d:%d\n%c[0m",27, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec, 27);
			}
			usleep(100000);
			break;
		case PRINT_DAY_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){
				printf("%s %c %d-%d-%c[4m%d%c[0m %d:%d:%d\n", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, 27, current_tm.tm_mday, 27, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
			}else{
				printf("%s %c %d-%d-%c[4m%d%c[0m", week_day[current_tm.tm_wday], alarm_info.display_alarm_indicator, current_tm.tm_year + 1900, current_tm.tm_mon + 1, 27, current_tm.tm_mday, 27);
				printf("%c[1;33m %d:%d:%d\n%c[0m",27, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec, 27);
			}
			usleep(100000);
			break;
		case PRINT_ALARM_MODE:
			system("clear");
			gotoxy(70,20);
			printf("AL %c %d-%d %d:%d\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, alarm_tm.tm_hour, alarm_tm.tm_min);
			usleep(100000);
			break;
		case PRINT_AL_HOUR_SET:
			system("clear");
			gotoxy(70,20);
			if(backlight_time==0){	
				printf("AL %c %d-%d %c[4m%d%c[0m:%d\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, 27, alarm_tm.tm_hour, 27, alarm_tm.tm_min);
			}else{
				printf("AL %c %d-%d %c[4m%d%c[0m", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, 27, alarm_tm.tm_hour, 27);
				printf("%c[1;33m:%d\n%c[0m",27, alarm_tm.tm_min, 27);
			}
			usleep(100000);			
			break;
		case PRINT_AL_MINUTE_SET:
			system("clear");
			gotoxy(70,20);
			printf("AL %c %d-%d %d:%c[4m%d%c[0m\n", alarm_info.display_alarm_indicator, current_tm.tm_mon + 1, current_tm.tm_mday, alarm_tm.tm_hour, 27, alarm_tm.tm_min, 27);
			usleep(100000);
			break;
		case PRINT_STOPWATCH_MODE:
			system("clear");
			gotoxy(70,20);
			printf("ST %d-%d %d:%d:%d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec%100);
			usleep(100000);
			break;
		case PRINT_START:
			system("clear");
			gotoxy(70,20);
			printf("ST %d-%d %d:%d:%02d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec%100);
			usleep(100000);
			break;
		case PRINT_STOP:
			system("clear");
			gotoxy(70,20);
			printf("ST %d-%d %d:%d:%d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec%100);
			usleep(100000);
			break;
		case PRINT_LAP_TIME:
			system("clear");
			gotoxy(70,20);
			printf("ST %d-%d %d:%d:%02d\n", current_tm.tm_hour, current_tm.tm_min, stop_min, stop_sec, stop_milisec%100);
			usleep(100000);
			break;
		default: break;
	}
}
