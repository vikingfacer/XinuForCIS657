/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	kprintf("recv in:%d out:%d\n", prptr->prmsgin, prptr->prmsgout);
	if (prptr->prmsgin == prptr->prmsgout) {
		prptr->prmsgin = 0;
		prptr->prmsgout = 0;
		prptr->prstate = PR_RECV;
		prptr->prhasmsg = FALSE;
		resched();		/* block until message arrives	*/
	} else {
		msg = prptr->prmsg[prptr->prmsgout];		/* retrieve message		*/
		prptr->prmsgout = ++prptr->prmsgout;
		prptr->prhasmsg = TRUE;
	}

	restore(mask);
	return msg;
}
