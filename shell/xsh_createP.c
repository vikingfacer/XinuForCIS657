/*
 * Jacob Montpetit
 *
 * Description:
 */
/* xsh_create.c - xsh_create */
#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*------------------------------------------------------------------------
* xsh_create - shell command to createeeeee
*------------------------------------------------------------------------
*/
void runforever(void) {
	while(TRUE){
		printf("hello from PID: %d\n", getpid());
		sleep(5);
	}
};

shellcmd xsh_create(int nargs, char *args[])
{
	if (nargs == 1){
		pid32 pid = create(runforever, 1024, 20, "test", 0);
		resume(pid);
	} else {
		pri16 priority;
		char ch;
		char *chprio;
		pid32 pid;
		int i = 1;
		while(i < nargs){
			priority = atoi(args[i]);
			if (priority < (pri16)MINKEY) {
				kprintf("%s: invalid prioirty\n", args[i]);
				break;
			}
			pid = create(runforever, 1024, priority, "test", 0);
			resume(pid);
			i++;
		}
	}
}
