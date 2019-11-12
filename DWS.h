#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
//#include <conio.h>
#define TIME_MODE 1
#define SEC_SET 2
#define MINUTE_SET 3
#define YEAR_SET 4
#define MONTH_SET 5
#define DAY_SET 6
#define ALARM_MODE 7
#define STOPWATCH_MODE 8
#define START 9
#define STOP 10
#define LAP_TIME 11


typedef struct alarm_information{
	bool alarm_power; // 알람 켜짐 여부
	bool info;	// 알람여부
	int hour;
	int min;
}alarm_info;

int st_info=0;
char btn;
time_t current_time;


void plus_one();
void set_min();
void day_set();
void month_set();
void year_set();
void minute_set();
void hour_set();
void sec_set();
void time_mode();
void alarm_indicator();
void alarm_mode();
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
