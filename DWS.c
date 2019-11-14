#include "DWS.h"

int st_info = 0;
int mo_info = TIME_MODE;
int display_command = 0;


void current() {
	current_time = time(NULL);
	current_tm = *localtime(&current_time);
	system("clear");
	printf("현재시간: %d-%d-%d %d:%d:%d\n", current_tm.tm_year + 1900, current_tm.tm_mon + 1, current_tm.tm_mday, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
}

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

void time_mode()
{
	
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info = SEC_SET;
		}
		if (btn == 'c') {
			mo_info = ALARM_MODE;
		}
	}
	display_command = PRINT_TIME_MODE;
	printf("타임모드\n");
}

void sec_set()
{
	//button input
	if (kbhit() == 1) {
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
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			if (current_tm.tm_hour == 23) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c') {
			st_info = MINUTE_SET;
		}
	}
	//display
	display_command = PRINT_HOUR_SET;
	printf("시간\n");
}

void minute_set()
{
	//button input
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			if (current_tm.tm_min == 59) set_min(st_info);
			else plus_one(st_info);
		}
		if (btn == 'c' && mo_info == TIME_MODE) {
			st_info = YEAR_SET;
		}
		if (btn == 'c' && mo_info == ALARM_MODE) {
			st_info = HOUR_SET;
		}


	}
	//display
	display_command = PRINT_MINUTE_SET;
	printf("분\n");
}

void year_set()
{
	//button input
	if (kbhit() == 1) {
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
	if (kbhit() == 1) {
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
	if (kbhit() == 1) {
		if (btn == 'a') {
			st_info = 0;
		}
		if (btn == 'b') {
			//int date = date(current_tm.tm_year, current_tm.tm_mon);
			int date = 28;
			if (current_tm.tm_mday == date) set_min(st_info);
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
		case SEC_SET: current_tm.tm_sec++; break;
		case HOUR_SET: current_tm.tm_hour++; break;
		case MINUTE_SET: current_tm.tm_min++; break;
		case YEAR_SET: current_tm.tm_year++; break;
		case MONTH_SET: current_tm.tm_mon++; break;
		case DAY_SET: current_tm.tm_mday++; break;
		default: break;
		}
	}

	void set_min(int st_info)
	{
		switch (st_info)
		{
		case SEC_SET:
			current_tm.tm_sec = 0;
			current_tm.tm_min--;
			break;
		case HOUR_SET:
			current_tm.tm_hour = 0;
			current_tm.tm_mday--;
			break;
		case MINUTE_SET:
			current_tm.tm_min = 0;
			current_tm.tm_hour--;
			break;
		case YEAR_SET:
			current_tm.tm_year = 119;
			break;
		case MONTH_SET:
			current_tm.tm_mon = 1;
			current_tm.tm_year--;
			break;
		case DAY_SET:
			current_tm.tm_mday = 1;
			current_tm.tm_mon--;
			break;
		default: break;
		}
	}

	void alarm_mode()
	{
		//button input
		if (kbhit() == 1) {
			if (btn == 'a') {
				st_info = HOUR_SET;
			}
			if (btn == 'b') {
				if (current_tm.tm_hour == 23) set_min(st_info);
				else plus_one(st_info);
			}
			if (btn == 'c') {
				st_info = MINUTE_SET;
			}
		}
		//display
		display_command = PRINT_MINUTE_SET;
		printf("알람모드\n");
	}
	void alarm_indicator()
	{
		//alarm_mode일때 indicator를 띄운다.
		printf("indicator");
	}
	void lap_time();
	void stop();
	void start();
	void stopwatch_mode();

	void turn_on();
	void turn_off();

	void turn_yellow();

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

}