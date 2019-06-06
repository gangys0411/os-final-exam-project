#include "header.h"

struct process
{
	int pid; //프로세스 id
	int arr_time; // 도착시간
	int ser_time; // 실행될 시간
	int rem_time; // 남은 시간
	struct process *pro // 다음 프로세스 포인터
};

void fileroad()
{
	int pnum=0;
	FILE *fp;

	fp=fopen("test.txt","r");
	if(fp==NULL)
	{
		printf("파일이 없습니다.\n");
	}
	else
	{
		fscanf(fp, "%d", &pnum);
		struct process *pro[pnum];
	
		for (int i=0; i<sizeof(pro)/sizeof(struct process*);i++) // 구조체 포인터 배열 전체 크기를 구조체 포인터의 크기로 나눠 구조체 포인터의 개수를 구한 후 그 수만큼 반복
		{
			pro[i]=malloc(sizeof(struct process));
		}
		for(int j=0; j<pnum; j++)
		{
			fscanf(fp, "%d %d %d", &pro[j]->pid, &pro[j]->arr_time, &pro[j]->ser_time);
			printf("%d %d %d \n", pro[j]->pid, pro[j]->arr_time, pro[j]->ser_time);
		}
	}
}
