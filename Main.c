#include "DWS.h"

void* time_routine(void *arg){
	//pthread_t tid;
	//tid=pthread_self();
	while(1){
		current_time =time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %d-%d-%d %d:%d:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}
void* sec_set_routine(){
	while(1){
		current_time =time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %d-%d-%d %d:%d:%c[4m%d%c[0m\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,27,current_tm.tm_sec,27);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
void* hour_set_routine(){
	while(1){
		current_time=time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %d-%d-%d %c[4m%d%c[0m:%d:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,27,current_tm.tm_hour,27,current_tm.tm_min,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
void* min_set_routine(){
	while(1){
		current_time=time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %d-%d-%d %d:%c[4m%d%c[0m:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,27,current_tm.tm_min,27,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
void* year_set_routine(){
	while(1){
		current_time=time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %c[4m%d%c[0m-%d-%d %d:%d:%d\n",27,current_tm.tm_year+1900,27,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
void* year_set_routine(){
	while(1){
		current_time=time(NULL);
		struct tm current_tm=*localtime(&current_time);
		system("clear");
		pthread_mutex_lock(&mutex);
		printf("현재시간: %c[4m%d%c[0m-%d-%d %d:%d:%d\n",27,current_tm.tm_year+1900,27,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
void turn_yellow(){
	printf("%c[1;33m",27);
	sleep(5);
	system("reset");
}
void sec_set(void* arg){
	pthread_create(&time_thread,NULL,sec_set_routine,NULL);
	
	while(1){
		btn=getch();
		if(btn=='a'){
			printf("ddd\n");
		}else if(btn=='c'){
			//alarm_mode();
		}else if(btn=='d'){
			turn_yellow();
		}
	}

}
void main(){
	
	
	pthread_create(&time_thread,NULL,time_routine,NULL);
	
	pthread_mutex_init(&mutex,NULL);

	
	while(1){
		btn=getch();
		if(btn=='a'){
			pthread_cancel(time_thread);
			sec_set(&time_thread);
		}else if(btn=='c'){
			//alarm_mode();
		}else if(btn=='d'){
			turn_yellow();
		}
	}
	pthread_mutex_destroy(&mutex);
}
