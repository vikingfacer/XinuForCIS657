/*
 * Jacob Montpetit
 *
 * Description: ad priority tab
 */

#include <xinu.h>
#include <stdio.h>

void printQEntry(const struct qentry* entry);
/*------------------------------------------------------------------------
 * xsh_pqtab - shell command to print the queue table
 *------------------------------------------------------------------------
 */
shellcmd xsh_pqtab(int nargs, char *args[])
{
	printf("xsh ps cmd\n");
	printf("|  ID  |  key  |  prev  |  next  |\n");
	printf("|------|-------|--------|--------|\n");
	int i = 0;
	for (; i < NPROC && queuetab[i-1].qnext != NULL; i++)
	{
		printf("| %4d |  %3d  |  %4d  |  %4d  |\n",i, queuetab[i].qkey, queuetab[i].qprev, queuetab[i].qnext);
	}

}

void printQEntry(const struct qentry* entry)
{
	printf("Key: 0x%x, Prev: %d, Next: %d\n", entry->qkey, entry->qprev, entry->qnext);
}

