/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* contents of message		*/
	)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	kprintf("send in:%d out:%d\n", prptr->prmsgin, prptr->prmsgout);
	if ((prptr->prstate == PR_FREE) || (prptr->prmsgin >= KMSG)) {
		restore(mask);
		return SYSERR;
	}

	prptr->prmsg[prptr->prmsgin] = msg; /* deliver message		*/
	prptr->prmsgin = ++prptr->prmsgin;
	prptr->prhasmsg = TRUE;

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid, RESCHED_YES);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	restore(mask);		/* restore interrupts */
	return OK;
}
