/*
 * Jacob Montpetit
 *
 * Description:
 */

#include <xinu.h>
#include <stdio.h>
#include <string.h>


shellcmd xsh_prio(int nargs, char *args[])
{
	if(strncmp(args[1], "prio", 5)==0){
		PRIO_SCHED = TRUE;
		printf("Priority Schedule Set\n");
	}else
	if( strncmp(args[1], "fifo", 5)==0){
		PRIO_SCHED = FALSE;
		printf("FIFO Schedule Set\n");
	}else{
		printf("Invalid Schedule Set\n");
	}
}
