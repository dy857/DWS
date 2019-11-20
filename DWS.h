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
#include <signal.h>

//status
#define TIME_MODE 1
#define SEC_SET 2
#define HOUR_SET 3
#define MINUTE_SET 4
#define YEAR_SET 5
#define MONTH_SET 6
#define DAY_SET 7
#define ALARM_MODE 8
#define AL_HOUR_SET 9
#define AL_MINUTE_SET 10 
#define STOPWATCH_MODE 11
#define START 12
#define STOP 13
#define LAP_TIME 14
#define TURN_ON 15
#define TURN_OFF 16
#define TURN_YELLOW 17

//display command
#define PRINT_TIME_MODE 20
#define PRINT_SEC_SET 21
#define PRINT_HOUR_SET 22
#define PRINT_MINUTE_SET 23
#define PRINT_YEAR_SET 24
#define PRINT_MONTH_SET 25
#define PRINT_DAY_SET 26
#define PRINT_ALARM_MODE 27
#define PRINT_AL_HOUR_SET 28
#define PRINT_AL_MINUTE_SET 29
#define PRINT_STOPWATCH_MODE 30
#define PRINT_START 31
#define PRINT_STOP 32
#define PRINT_LAP_TIME 33
#define PRINT_BACKLIGHT 34


typedef struct _alarm_information{
   bool alarm_power; // 알람 켜짐 여부
   char display_alarm_indicator; // Alarm indicator on/off 여부
   int beep_time;
}alarm_information;

// Data storage
int st_info; //Status information
int al_info; //Alarm information
int mo_info; //mode information
int bl_info; //backlight information


int backlight_time; // 2sec
int display_command;
int btn; // button input storage

time_t current_time;
time_t alarm_time;

struct tm current_tm;
struct tm alarm_tm;
struct tm st_tm;
struct timeval st_tv;
struct timeval st_start;
struct timeval st_stop;

// 스톱워치 변수
unsigned int stop_min;
unsigned int stop_sec;
unsigned int stop_milisec;




// 함수 및 프로세스
int createCurrent(timer_t *timerID, int sec, int msec);
int date(int year, int month);
static void current();
void time_mode();
void sec_set();
void hour_set();
void minute_set();
void year_set();
void month_set();
void day_set();
void plus_one(int st_info);
void set_min(int st_info);
void alarm_mode();
void alarm_indicator();
void lap_time();
void stop();
void start();
void stopwatch_mode();
void turn_on();
void turn_off();
void idle();
void turn_yellow();
void btn_input();
int getch();
int kbhit();
void gotoxy(int x, int y);
void display(int display_command);
