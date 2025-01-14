/*
 * $Id: time_itimer_tasks.c,v 1.0 2022-03-15 08:39:45 clib2devs Exp $
*/

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

#ifndef PROTO_TIMER_H
#include <proto/timer.h>
#endif /* PROTO_TIMER_H */

#ifndef _SIGNAL_HEADERS_H
#include "signal_headers.h"
#endif /* _SIGNAL_HEADERS_H */

int itimer_real_task() {
    static int USED *timertype; // Can we manage various timers?
    struct MsgPort *tmr_real_mp = NULL;
    struct TimeRequest *tmr_real_tr = NULL;
    ULONG wait_mask;
    BOOL Success = FALSE;

    struct Process *thisTask = (struct Process *)FindTask(NULL);
    timertype = (int *)thisTask->pr_Task.tc_UserData;
    //Printf("timertype=%ld\n", *timertype);

    /* Create itimer timers and message ports */
    tmr_real_mp = AllocSysObjectTags(ASOT_PORT,
                                     ASOPORT_Action, PA_SIGNAL,
                                     ASOPORT_AllocSig, FALSE,
                                     ASOPORT_Signal, SIGB_SINGLE,
                                     ASOPORT_Target, FindTask(NULL),
                                     TAG_DONE);
    if (!tmr_real_mp) {
        goto out;
    }
    tmr_real_tr = AllocSysObjectTags(ASOT_IOREQUEST, ASOIOR_ReplyPort, tmr_real_mp, ASOIOR_Size, sizeof(struct TimeRequest), TAG_END);
    if (!tmr_real_tr) {
        goto out;
    }
    if (OpenDevice(TIMERNAME, UNIT_VBLANK, (struct IORequest *)tmr_real_tr, 0) != OK)
    {
        goto out;
    }

    tmr_real_tr->Request.io_Command = TR_ADDREQUEST;
    tmr_real_tr->Time.Seconds = __global_clib2->tmr_time.it_value.tv_sec;
    tmr_real_tr->Time.Microseconds = __global_clib2->tmr_time.it_value.tv_usec;

    /* Loop until timer expires and restart or we interrupt it */
    while (TRUE) {
        /* Get current time of day */
        gettimeofday(&__global_clib2->tmr_start_time, NULL);
        /* Set wait mask */
        wait_mask = SIGBREAKF_CTRL_F | SIGBREAKF_CTRL_D | (1L << tmr_real_mp->mp_SigBit);
        /* Reset signals */
        SetSignal(0, wait_mask);
        /* Send timer request */
        SendIO((struct IORequest *) tmr_real_tr);
        /* Wait for signals */
        uint32 signals = Wait(wait_mask);
        /* Check for received signal */
        if (signals & SIGBREAKF_CTRL_F) {
            if (CheckIO((struct IORequest *) tmr_real_tr))  /* If request is complete... */
                WaitIO((struct IORequest *) tmr_real_tr);   /* clean up and remove reply */
            AbortIO((struct IORequest *) tmr_real_tr);      /* Abort request             */
            /* Exit from while */
            break;
        }

        if (signals & SIGBREAKF_CTRL_D) {
            /* This is used to reset the timer with new value without raising the signal */
            if (CheckIO((struct IORequest *) tmr_real_tr))  /* If request is complete... */
                WaitIO((struct IORequest *) tmr_real_tr);   /* clean up and remove reply */
            AbortIO((struct IORequest *) tmr_real_tr);

            tmr_real_tr->Time.Seconds = __global_clib2->tmr_time.it_value.tv_sec;
            tmr_real_tr->Time.Microseconds = __global_clib2->tmr_time.it_value.tv_usec;
        }
        else {
            if (CheckIO((struct IORequest *) tmr_real_tr))
                WaitIO((struct IORequest *) tmr_real_tr);

            tmr_real_tr->Time.Seconds += __global_clib2->tmr_time.it_interval.tv_sec;
            tmr_real_tr->Time.Microseconds += __global_clib2->tmr_time.it_interval.tv_usec;

            /* If SIGALRM is blocked kill the timer */
            if (FLAG_IS_SET(__signals_blocked, (1 << SIGALRM))) {
                break;
            }

            raise(SIGALRM);

            /* Check again if SIGALRM is blocked and then kill the timer */
            if (FLAG_IS_SET(__signals_blocked, (1 << SIGALRM))) {
                break;
            }
        }
    }

    Success = TRUE;

out:
    /* Free itimer objects */
    if (tmr_real_mp) {
        FreeSysObject(ASOT_PORT, tmr_real_mp);
        tmr_real_mp = NULL;
    }
    if (tmr_real_tr) {
        if (tmr_real_tr->Request.io_Device != NULL)
            CloseDevice((struct IORequest *)tmr_real_tr);
        FreeSysObject(ASOT_IOREQUEST, tmr_real_tr);
        tmr_real_tr = NULL;
    }

    if (Success)
        return RETURN_OK;
    else
        return RETURN_FAIL;
}
