#include <xinu.h>
#include <stdio.h>

void infLoop();

void main(void)
{
	int n = 1, nthr = 10; //nthr is number of threads to execute
	
	for (; n <= nthr; n++)
	{
		resume(create(infLoop, 1024, 20, "proc %d", n, 1, CONSOLE));
	}
	
	printf("|  ID  |  key  |  prev  |  next  |\n");
	printf("|------|-------|--------|--------|\n");
	int i = 0;
	for (; i < NPROC && queuetab[i-1].qnext != NULL; i++)
	{
		printf("| %4d |  %3d  |  %4d  |  %4d  |\n",i, queuetab[i].qkey, queuetab[i].qprev, queuetab[i].qnext);
	}
}

void infLoop()
{
	while (1) ;
}
