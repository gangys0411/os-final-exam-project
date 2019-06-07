#include "header.h"

extern int process[10000][5];

extern int time;

void ps_print(FILE *fp, int i)
{
	fprintf(fp, "현재 시간 : %d 	프로세스 ID : %d 	", time, process[i][0]);
	
	switch(process[i][4])
	{
		case 0 : fprintf(fp, "프로세스 상태 : 미생성\n"); break;
		case 1 : fprintf(fp, "프로세스 상태 : 대기중\n"); break;
		case 2 : fprintf(fp, "프로세스 상태 : 실행중\n"); break;
		case 3 : fprintf(fp, "프로세스 상태 : 중단됨\n"); break;
		case 4 : fprintf(fp, "프로세스 상태 : 종료됨\n"); break;
	}
}
