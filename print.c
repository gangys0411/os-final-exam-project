#include "header.h"

void ps_print(int time, struct process p)
{
	int c = p.next_pro->pro_status;
	int pid=p.next_pro->pid;
	printf("현재시간 : %d	프로세스 ID : %d	", time, pid);

	switch(c)
	{
		case 0 : printf("not creat\n"); break;
		case 1 : printf("ready\n"); break;
		case 2 : printf("running\n"); break;
		case 3 : printf("finish\n"); break;
	}
}
