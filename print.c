#include "header.h"

extern int process[10000][10];

extern int time;

extern int pnum;

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

void pr_cal(int finish_end)
{
	process[finish_end][7]=process[finish_end][6]-process[finish_end][1];
	process[finish_end][8]=process[finish_end][7]-process[finish_end][2];
	process[finish_end][9]=process[finish_end][5]-process[finish_end][1];
}

void tpr_cal(FILE *fp)
{
	double t_tat;
	double t_wt;
	double t_rpt;

	for(int i=7; i<10; i++)
	{
		for(int j=0; j<pnum; j++)
		{
			switch(i)
			{
				case 7 : t_tat+=process[j][i]; break;
				case 8 : t_wt+=process[j][i]; break;
				case 9 : t_rpt+=process[j][i]; break;
			}
		}
	}

	t_tat=t_tat/pnum;
	t_wt=t_wt/pnum;
	t_rpt=t_rpt/pnum;

	fprintf(fp, "\n\n평균 소요 시간 : %.2f	평균 대기 시간 : %.2f	평균 응답 시간 : %.2f\n", t_tat, t_wt, t_rpt);
}

void pr_print(FILE *fp)
{
	fprintf(fp, "\n\n 프로세스 정보 로그\n");
	for(int i=pnum-1; i>-1; i--)
	{
		fprintf(fp, "프로세스 ID : %d	", process[i][0]);
		for(int j=7; j<10; j++)
		{
			switch(j)
			{
				case 7 : fprintf(fp, "소요 시간 : %d	",process[i][j]); break;
				case 8 : fprintf(fp, "대기 시간 : %d	",process[i][j]); break;
				case 9 : fprintf(fp, "응답 시간 : %d	",process[i][j]); break;
			}
		}
		fprintf(fp,"\n");
	}
}
