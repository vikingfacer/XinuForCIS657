/*
 * Jacob Montpetit
 *
 * Description:
 */
/* xsh_create.c - xsh_create */
#include <xinu.h>
#include <stdio.h>
#include <string.h>
/*------------------------------------------------------------------------
* xsh_create - shell command to createeeeee
*------------------------------------------------------------------------
*/
void runreceiveforever(void) {
	while(TRUE){
		sleep(10);
		int retval = receive();
		printf("Received: %d\n", retval);
	}
};

shellcmd xsh_receive(int32 nargs, char *args[])
{
	pri16 priority;
	char ch;
	char *chprio;
	pid32 pid;
	if (nargs == 1) {
		priority=INITPRIO;
	}
	else if (nargs > 2) {
		priority = atoi(args[1]);
		if (priority < (pri16)MINKEY) {
			kprintf("%s: invalid prioirty\n", args[1]);
			return 1;
		}
	}
	else {
		kprintf("Too many arguments\n");
		return 1;
	}
	pid = create(runreceiveforever, 1024, priority, "test", 0);
	resume(pid);
	return 0;
}
