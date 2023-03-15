/* recvclr.c - recvclr */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  recvclr  -  clear incoming message, and return message if one waiting
 *------------------------------------------------------------------------
 */
umsg32	recvclr(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prmsgout == prptr->prmsgin) {
		msg = OK;
	} else {
		msg = prptr->prmsg[prptr->prmsgout];	/* retrieve message		*/
	}
	prptr->prmsgout = 0;
	prptr->prmsgin = 0;
	prptr->prhasmsg = FALSE;/* reset message flag		*/

	restore(mask);
	return msg;
}
