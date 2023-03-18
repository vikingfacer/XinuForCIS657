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
		// uncomment line below to test recvtime
		// recvtime(10000);
		int retval = receive();
		if (retval != TIMEOUT){
		printf("Received: %d\n", retval);
		}
	}
};

shellcmd xsh_receive(int32 nargs, char *args[])
{
	if (nargs >= 2) {
		uint32 i = 0;
		while(i++ < nargs){
			pri16 priority = atoi(args[1]);
			if (priority < (pri16)MINKEY) {
				kprintf("%s: invalid prioirty\n", args[1]);
			} else {
			resume(create(runreceiveforever, 1024, priority, "test", 0));
			}
		}
	}
	else {
			resume(create(runreceiveforever, 1024, INITPRIO, "test", 0));
	}
	return 0;
}
