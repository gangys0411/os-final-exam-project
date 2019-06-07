#include "header.h"

extern int process[10000][5]; // 외부 변수 참조

extern int pnum;


void fileroad()
{
	FILE *fp;
	
	fp=fopen("process_list_1000.txt","r");
	if(fp==NULL)
	{
		printf("파일이 없습니다.\n");
	}
	else
	{
		fscanf(fp, "%d", &pnum);
		for(int i=0; i<pnum; i++)
		{
			fscanf(fp, "%d %d %d", &process[i][0], &process[i][1], &process[i][2]); // 프로세스 ID, 도착 시간, 실행 시간 저장
			
			process[i][3]=process[i][2]; // 남은 시간에 실행되어야할 시간을 입력
		}
	}

	fclose(fp);
}
