#include <xinu.h>
#include <stdio.h>

void signaler(void);
void waiter(void);
sid32 sem;
pid32 spid, wpid;

void main(void)
{
	sem = semcreate(20);
	wpid = create(waiter, 1024, 40, "waiter", 0);
	resume(wpid);
	spid = create(signaler, 1024, 20, "signaler", 0);
	resume(spid);
	return OK;
}

void signaler(void)
{
	while(1)
	{
		printf("\nSignaler is running \n");
		int32 i;
		signaln(sem,5);
	}
}

void waiter(void)
{
	int32 i;
	for (i = 1; i <= 2000; i++)
	{
		printf("%d ", i);
		wait(sem);
	}
	kill(spid);
	kill(wpid);
}
