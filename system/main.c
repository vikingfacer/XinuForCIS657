/*  main.c  - main */

#include <xinu.h>

void putcForever(char c);

int main(int argc, char **argv)
{
	resume(create(putcForever, 1024, 40, "Proc A", 1, 'A'));
	resume(create(putcForever, 1024, 20, "Proc B", 1, 'B'));

	return OK;
}

void putcForever(char c)
{
	while(1)
	{
	putc(CONSOLE, c);
	}
}
