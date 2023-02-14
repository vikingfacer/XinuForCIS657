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
void prod2(sid32, sid32);
void cons2(sid32, sid32);
int32 n = 0; /* Variable n has inital value zero */
/*-------------------------------------------------------------------
* main - Producer and Consumer processes synchronized with semaphores
*--------------------------------------------------------------------
*/
void main(void)
{
	sid32 produced, consumed;
	consumed = semcreate(0);
	produced = semcreate(1);
	resume( create(cons2, 1024, 20, "cons", 2, consumed, produced) );
	resume( create(prod2, 1024, 20, "prod", 2, consumed, produced) );
}
/*-------------------------------------------------------------------------
* prod2 - Increment n 2000 times, waiting for it to be consumed
*---------------------------------------------------------------------------
*/
void prod2(sid32 consumed, sid32 produced)
{
	int32 i;
	for(i=1; i<=2000; i++)
	{
		wait(consumed);
		n++;
		signal(produced);
	}
}
/*-------------------------------------------------------------------------
* cons2 - Print n 2000 times, waiting for it to be produced
*---------------------------------------------------------------------------
*/
void cons2(sid32 consumed, sid32 produced)
{
	int32 i;
	for(i=1; i<=2000; i++)
	{
		wait(produced);
		printf("n is %d \n", n);
		signal(consumed);
	}
}
