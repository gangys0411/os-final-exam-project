#include "header.h"

typedef struct process
{
	int pid; //프로세스 id
	int arr_time; // 도착시간
	int ser_time; // 실행될 시간
	int rem_time; // 남은 시간
	struct process *next_pro; // 다음 프로세스 포인터
};

int pnum=0;

struct process create_list; // 만들어야할 프로세스를 연결하기 위한 시작 구조체

void fileroad()
{
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
			pro[j]->rem_time=pro[j]->ser_time; // 남은 시간에 실행되어야할 시간을 입력
			pro[j]->next_pro=pro[j+1]; // 현재 프로세스에 다음 프로세스 주소를 저장
			if(j+1==pnum)
			{
				pro[j]->next_pro=NULL; // 마지막 프로세스라면 NULL 저장
			}
			printf("%d %d %d %d\n", pro[j]->pid, pro[j]->arr_time, pro[j]->ser_time, pro[j]->rem_time); // 구조체 생성 확인을 위한 임시 코드
		}

		create_list.next_pro=pro[0]; // 프로세스 연결
	}
}
