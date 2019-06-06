#include "header.h"
#include "fileroad.c"
#include "change.c"

int main()
{

	fileroad(); // 파일 읽기 함수


	struct process wait_list; // 대기열 시작 구조체
	wait_list.next_pro=NULL;

	struct process CPU; // 사용중인 프로세스 구조체
	CPU.next_pro=NULL;

	struct process end_list; // 종료된 프로세스 구조체
	end_list.next_pro=NULL;

	struct cursor // 생성된 프로세스를 관리하기 위한 구조체
	{
		struct process *pre_pro;
		struct process *cur_pro;
		struct process * next_pro;
	}cursor;

	int time=0; // 현재 시간 초기화

	printf("%d \n", create_list.next_pro->pid); // 임시 코드

	while(1)
	{
		if(time==create_list.next_pro->arr_time) // 현재 시간과 만들어져야할 프로세스의 도착시간이 같다면
		{
			insert(create_list, wait_list); // 프로세스 생성
			if(wait_list.next_pro!=NULL) // 대기열에 프로세스가 있다면
			{
				cursor.pre_pro=&wait_list;
				cursor.cur_pro=wait_list.next_pro;
				cursor.next_pro=wait_list.next_pro->next_pro; // 새로 생성된 프로세스를 커서로 앞뒤 프로세스를 저장

				while(1)
				{	
					if(cursor.cur_pro->rem_time<cursor.next_pro->rem_time) // 커서의 프로세스보다 남은 실행 시간이 짧으면
					{
						break;
					}else  // 커서의 프로세스 보다 남은 실행 시간이 길면
					{
						cursor.pre_pro->next_pro=cursor.next_pro; 
						cursor.cur_pro->next_pro=cursor.next_pro->next_pro;
						cursor.next_pro->next_pro=cursor.cur_pro; // 새로 생성된 프로세스를 뒤로 옮김

						cursor.pre_pro=cursor.cur_pro;
						cursor.cur_pro=cursor.next_pro;
						cursor.next_pro=cursor.next_pro->next_pro; // 커서 이동
					}
				}
			}
			
			if(CPU.next_pro!=NULL) // 사용 중인 프로세스가 있다면
			{
				if(wait_list.next_pro->rem_time<CPU.next_pro->rem_time) // 다음 프로세스가 그 프로세스보다 남은 시간이 짧다면					
				{
					change(wait_list, CPU); // 다음 프로세스를 실행시키고 사용중이던 프로세스를 대기열로 넣음
				}
			}else // 사용 중인 프로세스가 없다면
			{
				CPU.next_pro=wait_list.next_pro; // 다음 프로세스를 실행시킴
				wait_list.next_pro=wait_list.next_pro->next_pro; // 대기열의 다음 프로세스를 갱신함
			}
		}
		
		CPU.next_pro->rem_time--; // 사용 중인 프로세스의 남은 시간을 1 줄이고
		time++; // 현재 시간을 1 증가

		if(CPU.next_pro->rem_time==0) // 사용중이던 프로세스의 남은 시간이 0이라면
		{
			CPU.next_pro->next_pro=end_list.next_pro;
			end_list.next_pro=CPU.next_pro; // 프로세스를 종료하고 대기열에서 프로세스를 불러옴
			CPU.next_pro=wait_list.next_pro;
			wait_list.next_pro=CPU.next_pro->next_pro;

			if(create_list.next_pro==NULL && wait_list.next_pro==NULL)
			{
				break;
			}
		}
	}

	return 0;
}
