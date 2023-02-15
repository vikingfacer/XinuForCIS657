/*
 * Modify the producer-consumer code in file ex5.c
 * (in the book and lecture not in xinu directory, see below)
 * to use a buffer of 15 slots, and have the producer and consumer synchronize
 * in such a way that the producer can generate up to 15 values
 * before blocking and a consumer can extract all values in the buffer before blocking.
 * That is, arrange for the producer to write 1, 2, ... in successive locations of the buffer,
 * wrapping around to the beginning after filling the last slot,
 * and have the consumer extract values and print them on the console.
 * How many semaphores are needed?
 */

#include <xinu.h>
void prod2(), cons2();
int32 n = 0, bufSize = 15; /* Variable n has inital value zero */
char buffer[15];
sid32 sem;
pid32 ppid, cpid;


/*-------------------------------------------------------------------
* main - Producer and Consumer processes synchronized with semaphores
*--------------------------------------------------------------------
*/
void main(void)
{
	sem = semcreate(bufSize-1);
	cpid = create(cons2, 1024, 20, "cons", 0);
	ppid = create(prod2, 1024, 30, "prod", 0);
	resume(ppid);
	resume(cpid);

}
/*-------------------------------------------------------------------------
* prod2 - Increment n 2000 times, waiting for it to be consumed
*---------------------------------------------------------------------------
*/
//void prod2(sid32 consumed, sid32 produced)
void prod2() // no args since consumed and produced are global
{
	int32 i;

	for (i = 0; i < bufSize*3; i++)
	{
		if(i%15 == 0) kprintf("\n\nProducer working:\n");
		buffer[i%15] = i+1;
		printf("%d ", buffer[i%15]);
		wait(sem);
	}

}
/*-------------------------------------------------------------------------
* cons2 - Print n 2000 times, waiting for it to be produced
*---------------------------------------------------------------------------
*/
//void cons2(sid32 consumed, sid32 produced)
void cons2() // no args since consumed and produced are global
{
	
	int32 i, loops = 0;
	while (loops < 3)
	{
		kprintf("\nConsumer working loop #%d:\n", loops+1);
		for (i = 0; i < bufSize; i++)
		{
			printf("[%d]:%d ", i, buffer[i]);
		}
		loops++;
		signaln(sem, bufSize);

	}

}
