#include "header.h"
#include "fileroad.c"
#include "print.c"

int process[10000][10];
// 0 프로세스 ID, 1 도착 시간, 2 실행될 시간, 3 남은 시간, 4 프로세스 상태, 5 첫 실행시간, 6 종료된 시간 7 turnaround time 8 waiting time 9 response time

int pnum=0; // 프로세스의 수

int wait_end=0; // 대기열의 끝

int finish_end=10000; // 종료 리스트의 끝

int cursor=0; // 시간 비교를 위한 커서

int buffer[6]={0};

int time=0; // 현재 시간 초기화

int main()
{

	fileroad(); // 파일 읽기 함수
	FILE *fp;
	fp=fopen("result.txt","w");
	
	finish_end=pnum; // 종료된 프로세스 리스트의 시작을 프로세스의 개수로 지정

	while(1)
	{
		if(time==process[wait_end][1]) // 현재 시간에 들어오는 프로세스가 있다면
		{
			process[wait_end][4]=1; // 그 프로세스의 상태를 대기로 바꾸고 출력
			ps_print(fp, wait_end);

			if(wait_end==0)
			{
				process[0][4]=2;
				ps_print(fp, 0);
			}else 
			{

				for(cursor=0; cursor<wait_end; cursor++) // 대기열에 있는 프로세스를 찾아서
				{
					if(process[cursor][3]>process[wait_end][3]) // 남은 시간이 더 많은 프로세스가 있다면
					{
						for(int j=0; j<6; j++)
						{
							buffer[j]=process[wait_end][j];
							for(int k=wait_end; k>cursor; k--) // 그 프로세스 앞으로 이동
							{
								process[k][j]=process[k-1][j];
							}
							process[cursor][j]=buffer[j];
						}

						if(cursor==0) // 만약 남은 시간이 더 긴 프로세스가 실행중이었다면
						{
							process[1][4]=3; // 밀려난 프로세스를 중단으로 바꾸고 출력
							ps_print(fp, 1);

							process[0][4]=2; // 지금 들어온 프로세스를 실행중으로 바꾸고 출력
							ps_print(fp, 0);

						}
					}
				}
			}
			
			wait_end++; // 대기열의 수를 늘림
		}
		
		time++; // 시간을 증가
		
		if(wait_end>0)
		{
			process[0][3]--; // 실행중인 프로세스의 남은 시간을 감소
			if(process[0][2]==process[0][3]+1) // 만약 처음으로 프로세스가 시작됐다면
			{
				process[0][5]=time-1; // 전 시간을 첫 실행 시간으로 저장
			}
		}
		if(process[0][3]==0) // 만약 남은 시간이 0이라면
		{
			process[0][4]=4; // 프로세스 상태를 종료로 갱신하고 출력
			ps_print(fp, 0);

			for(int m=0; m<6; m++)
			{
				buffer[m]=process[0][m];
		
				for(cursor=0; cursor<finish_end-1; cursor++)
				{		
					process[cursor][m]=process[cursor+1][m]; // 다른 프로세스를 한 칸씩 밀음
				}

				process[finish_end-1][m]=buffer[m]; // 종료된 프로세스를 종료리스트에 넣음
			}

			finish_end--; // 종료 프로세스의 수를 늘림
			wait_end--; // 대기열의 수를 감소

			process[finish_end][6]=time; // 종료 시간에 현재 시간을 넣음
			pr_cal(finish_end); // 종료된 프로세스 계산

			if(wait_end!=0) // 만약 대기 중인 프로세스가 있다면
			{
				process[0][4]=2; // 첫 프로세스를 실행중으로 바꾸고 출력
				ps_print(fp, 0);
			}

			if(finish_end==0) // 만약 모두 종료됐다면
			{
				pr_print(fp);
				tpr_cal(fp);
				break; // 종료
			}
		}
	}

	fclose(fp);

	return 0;
}
