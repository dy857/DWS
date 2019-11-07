#include "DWS.h"

void* time_routine(void *arg){
	pthread_t tid;
	tid=pthread_self();
	while(1){
		current_time =time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %d-%d-%d %d:%d:%d\n ",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}

void turn_yellow(){
	printf("\033[1;33m");
	fflush(stdout);
}
void main(){
	pthread_t time_thread;
	
	pthread_create(&time_thread,NULL,time_routine,NULL);
	
	pthread_mutex_init(&mutex,NULL);

	btn=getchar();
	while(1){
		switch(btn){
			case 'a':
				//sec_set();
				break;
			case 'c':
				//alarm_mode();
				break;
			case 'd':
				turn_yellow();
				break;
			default:
				exit(1);
		}
	}
	pthread_mutex_destroy(&mutex);
}
