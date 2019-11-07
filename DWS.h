#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define SEC_SET 1
#define HOUR_SET 2
#define MINUTE_SET 3
#define YEAR_SET 4
#define MONTH_SET 5
#define DAY_SET 6

typedef struct alarm_information{
	bool alarm_power;
	int hour;
	int min;
} alarm_info;



char btn;
time_t current_time;
pthread_mutex_t mutex;

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


