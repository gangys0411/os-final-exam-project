#include "header.h"

void insert(struct process p1, struct process p2)
{
	struct process buffer; // 버퍼

	buffer.next_pro=p2.next_pro; // 버퍼에 p2의 다음 프로세스를 저장
	p2.next_pro=p1.next_pro; // p2의 다음 프로세스에 p1의 다음 프로세스를 저장
	p1.next_pro=p1.next_pro->next_pro; // p1의 다음 프로세스에 p1의 다음 프로세스의 다음 프로세스를 저장
	p2.next_pro->next_pro=buffer.next_pro; // p2의 다음 프로세스의 다음 프로세스에 버퍼값을 저장
}

void change(struct process p1, struct process p2)
{
}

