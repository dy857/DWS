#include "DWS.h"

void turn_yellow(){
	printf("%c[1;33m",27);
	sleep(2);
	system("reset");
}

void current(){
	current_time =time(NULL);
	struct tm current_tm=*localtime(&current_time);
	system("clear");
	printf("현재시간: %d-%d-%d %d:%d:%d\n",current_tm.tm_year+1900,current_tm.tm_mon+1,current_tm.tm_mday,current_tm.tm_hour,current_tm.tm_min,current_tm.tm_sec);
}

void turn_on(){
	
}

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
