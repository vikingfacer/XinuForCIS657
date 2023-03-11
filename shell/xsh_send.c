/*
 * Jacob Montpetit
 *
 * Description:
 */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

shellcmd xsh_send(int nargs, char *args[])
{
	if(nargs > 2){
		pid32 pid = atoi(args[1]);
		int i = 2;
		while(i < nargs){
			umsg32 msg = atoi(args[i++]);
			send(pid, msg);
		}
	}else{
		printf("Bad Number of arguments\n");
	}
}
