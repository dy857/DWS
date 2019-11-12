#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

#define TIME_MODE 1
#define SEC_SET 2
#define HOUR_SET 3
#define MINUTE_SET 4
#define YEAR_SET 5
#define MONTH_SET 6
#define DAY_SET 7
#define ALARM_MODE 8
#define STOPWATCH_MODE 9
#define START 10
#define STOP 11
#define LAP_TIME 12


typedef struct alarm_information{
	bool alarm_power; // 알람 켜짐 여부
	bool info;	// 알람여부
	int hour;
	int min;
}alarm_info;

int mo_info=0;
int st_info=0;
char btn;
time_t current_time;

void time_mode()
{
	btn=' ';
	mo_info = TIME_MODE;
	st_info = 0;
}

void sec_set()
{
	btn=' ';
	st_info = SEC_SET;
	//깜빡깜빡
	printf("초 바꾸는 중");
}

void hour_set()
{
	btn=' ';
	st_info = HOUR_SET;
	//깜빡깜빡
	printf("시 바꾸는 중");
	
}

void minute_set()
{
	btn=' ';
	st_info = MINUTE_SET;
	//깜빡깜빡
	printf("분 바꾸는 중");
}

void year_set()
{
	btn=' ';
	st_info = YEAR_SET;
	//깜빡깜빡
	printf("년 바꾸는 중");
}

void month_set()
{
	btn=' ';
	st_info = MONTH_SET;
	//깜빡깜빡
	printf("달 바꾸는 중");
}

void day_set()
{
	btn=' ';
	st_info = DAY_SET;
	//깜빡깜빡
	printf("일 바꾸는 중");
}

void plus_one(int st_info);
void set_min(int st_info);

void alarm_mode()
{
	btn=' ';
	mo_info = ALARM_MODE;
}
void alarm_indicator()
{
	btn=' ';
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

int kbhit(void)
{
    	struct termios oldt, newt;
    	int ch;
    	int oldf;
 	
 	tcgetattr(STDIN_FILENO, &oldt);
    	newt = oldt;
    	newt.c_lflag &= ~(ICANON | ECHO);
    	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
    	ch = getchar();
 
    	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
    	if(ch != EOF)
    	{
    		ungetc(ch, stdin);
    		return 1;
    	}
 
    	return 0;
}
