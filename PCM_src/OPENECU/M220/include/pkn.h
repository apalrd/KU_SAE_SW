/*****************************************************************************/
/**
 *  \file    pkn.h
 *  \brief   Public interface to the scheduler feature.
 *
 *  Version: $Id: pkn.h 28958 2012-05-05 16:38:33Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pkn/pkn.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PKN_H
#define PKN_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found in a call to the
 * scheduler feature (PKN), the scheduler calls a system error log function
 * with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the scheduler is started under the wrong interrupt
     * conditions (internal error).
     */
    PKN_ERR_KERNEL_STARTED_BELOW_KERNEL_LEVEL       = 1,

    /** Error raised if the scheduler finds the resource does not exist in
     * the internal resource array.
     */
    PKN_ERR_INVALID_RESOURCE_HANDLE                 = 2,

    /** Error raised if the scheduler finds the calling task was not declared
     * as acquiring the resource.
     */
    PKN_ERR_TASK_NOT_DECLARED_AS_ACQUIRING_RESOURCE = 3,

    /** Error raised if the scheduler finds the task handle does not exist in
     * the internal task array.
     */
    PKN_ERR_INVALID_TASK_HANDLE                     = 4,

    /** Error raised if the scheduler finds the task handle does not exist in
     * the internal periodic task array.
     */
    PKN_ERR_INVALID_PERIODIC_TASK_HANDLE            = 5,

    /** Error raised if the scheduler detected a periodic task that has a period
     * of zero milliseconds.
     */
    PKN_ERR_PERIODIC_TASK_HAS_NO_PERIOD             = 6,

    /** Error raised if the scheduler traps an unexpected processor exception.
     */
    PKN_ERR_UNEXPECTED_EXCEPTION                    = 7,

    /** Error raised if the scheduler traps an unexpected processor interrupt.
     */
    PKN_ERR_UNEXPECTED_INTERRUPT                    = 8
}
PKN_ERROR_CODE_T;

/** The type for a group of tasks.
 *
 * A task is a group of functionality that can be run when
 * the task becomes ready. A task can become ready periodically
 * (e.g., scheduled every \e x ms) or sporadically (e.g., when
 * a sporadic interrupt is processed).
 *
 * A task has a fixed priority level and tasks ready to run are
 * executed in a pre-emptive fashion where each task release
 * is single shot (think of nested interrupt levels).
 *
 * A task set is a set of tasks with a common property, e.g.,
 * a set of tasks ready to run, or a set of tasks with priority
 * lower than the currently running task.
 *
 * A task set is represented as a bit set of task bit patterns.
 * Each task is assigned a single bit position in the representation
 * and can be identified by isolating the bit.
 *
 * As the tasks have a priority ordering, the order of the bits
 * assigned to tasks take the same ordering.
 *
 * E.g., the highest priority task takes the MS bit (note:
 * PPC bit numbering):
 *
 * \image html pkn_highest_pri_task_bitpattern.jpg
 *
 * and the second highest priority task takes the second MS bit:
 *
 * \image html pkn_sec_highest_pri_task_bitpattern.jpg
 *
 * and so on.
 *
 * A task set or more than one task is then simply the bitwise OR
 * of each task's bit pattern.
 *
 * E.g., the task set of the second highest task and fourth
 * highest task is represented as:
 *
 * \image html pkn_sec_fourth_pri_task_bitpattern.jpg
 *
 * The bit pattern representation makes finding the highest priority
 * task of a task set easy to find. On the PPC architecture, the count
 * leading zeros machine instruction \c cntlzw returns the bit position
 * of the MS set bit or 32 if no set bits exist.
 *
 * When running a task, pre-emption from another source can cause a
 * higher priority task to become ready. The kernel will pre-empt the
 * running task and start running the higher priority task.
 *
 * To make it easy to determine if a new higher priority task has been
 * make ready to run, the kernel keeps a record of the priority that
 * the current task is running at. This is called the task's ceiling.
 *
 * The ceiling is represented as a task set of the currently running
 * task and all lower priority tasks.
 *
 * E.g., if the fourth highest priority task is running, then the
 * ceiling task set would be:
 *
 * \image html pkn_fourth_pri_ceiling_bitpattern.jpg
 *
 * This representation of the ceiling makes it simple to determine
 * is a higher priority task is ready to run. If the ready taskset
 * is greater is value than the ceiling, then there is at least one
 * task with priority higher than the ceiling.
 *
 * E.g., consider a running task with the fourth highest priority
 * level when the second highest priority task becomes ready to run.
 *
 * This type specifies an atomic word large enough to hold
 * a task set for up to 32 tasks.
 *
 * \ingroup  c_interface
 */
typedef U32 PKN_TASKSET_T;

/** This structure defines a task's priority properties.
 */
typedef struct
{
    /** This is the C function to run when the task is the
     * highest ready task to run.
     */
    void          (*dispatch_fn)(void);

    /** This is the task set representation of the task
     * itself (i.e., single bit representing the task).
     */
    PKN_TASKSET_T ready_taskset;

    /** This is the ceiling task set representation of
     * the task when it is running.
     */
    PKN_TASKSET_T dispatch_ceiling;
}
PKN_TASK_T;

/** This type specifies a task handle. A handle is presented to the
 * kernel API whenever the user requires some action to occur on
 * the handle's object.
 *
 * The implementation of handles uses pointers for efficiency.
 *
 * \ingroup  c_interface
 */
typedef const PKN_TASK_T * const PKN_TASK_HANDLE_T;

/** This structure defines a task's periodic properties.
 */
typedef struct
{
    /** This is a pointer to the task's timer.  When the timer
     * expires, the kernel makes the task ready to run.
     */
    U32*              record;

    /** This is a flag which tells the kernel whether to
     * automatically restart the task's timer when it expired (true) or
     * whether not to (false).
     */
    BOOL              restart_timer;

    /** This is the initial time out for the task when the kernel
     * starts all periodic tasks.
     * Range: [0, 4294967295] milliseconds
     */
    U32               offset;

    /** This is the subsequent time out for the task after the
     * initial time out expires.
     * Range: [0, 4294967295] milliseconds
     */
    U32               period;

    /** This is a pointer to the task's priority properties.
     */
    PKN_TASK_HANDLE_T task;
}
PKN_PERIODIC_TASK_T;

/** This type specifies a periodic task handle. A handle is presented
 * to the kernel API whenever the user requires some action to occur
 * on the handle's object.
 *
 * The implementation of handles uses pointers for efficiency.
 *
 * \ingroup  c_interface
 */
typedef const PKN_PERIODIC_TASK_T* const PKN_PERIODIC_TASK_HANDLE_T;

/** This structure defines a resource's properties.
 */
typedef struct
{
    /** This is a pointer to the resource's priority
     * ceiling level record. It is the ceiling of the
     * task that successfully acquired the resource.
     */
    PKN_TASKSET_T*  record;

    /** This is the task set of task's that can acquire
     * the resource.
     */
    PKN_TASKSET_T   allowed_taskset;

    /** This is the ceiling of the task with the highest
     * priority that acquires this resource.
     */
    PKN_TASKSET_T   ceiling;
}
PKN_RESOURCE_T;

/** This type specifies a resource handle. A handle is presented to
 * the kernel API whenever the user requires some action to occur
 * on the handle's object.
 *
 * The implementation of handles uses pointers for efficiency.
 *
 * \ingroup  c_interface
 */
typedef const PKN_RESOURCE_T* const PKN_RESOURCE_HANDLE_T;

/********* Global Prototypes *********/

/* im[LLR.PLAT.PKN.RESACQ.001] */
extern void pkn_acquire_resource
(
    const PKN_RESOURCE_HANDLE_T
);

/* im[LLR.PLAT.PKN.RESREL.002] */
extern void pkn_release_resource
(
    const PKN_RESOURCE_HANDLE_T
);

/* im[LLR.PLAT.PKN.TASKREADY.009] */
extern void pkn_ready_task
(
    const PKN_TASK_HANDLE_T
);

extern void pkn_restart_periodic_task
(
    const PKN_PERIODIC_TASK_HANDLE_T
);

/* im[LLR.PLAT.PKN.TASKDURATION.001] */
extern U32 pkn_get_task_duration
(
    const PKN_TASK_HANDLE_T
);

extern U32 pkn_get_max_task_duration
(
    const PKN_TASK_HANDLE_T
);

extern void pkn_angular_model_task
(
    void
);

/********* Global Variables *********/

extern volatile U32 pkn_task_start_time[];
extern volatile U32 pkn_task_accum_time[];
extern volatile U32 pkn_task_time[];
extern volatile U32 pkn_max_task_time[];

#endif /* PKN_H */
