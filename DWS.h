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

int mo_info;
int st_info;
char btn;
time_t current_time;

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

void turn_yellow();

void btn_input();

int getch();

int kbhit(void);
