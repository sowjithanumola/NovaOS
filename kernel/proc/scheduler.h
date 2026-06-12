/*
 * NovaOS Process Scheduler Header
 */

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "../include/types.h"

/* Process states */
#define PROCESS_UNUSED     0
#define PROCESS_READY      1
#define PROCESS_RUNNING    2
#define PROCESS_BLOCKED    3
#define PROCESS_TERMINATED 4

/* Process priorities */
#define PRIORITY_IDLE    0
#define PRIORITY_LOW     1
#define PRIORITY_NORMAL  2
#define PRIORITY_HIGH    3

void init_scheduler(void);
uint32_t create_process(const char *name, void (*entry)(void), uint32_t priority);
void idle_process(void);
uint32_t schedule(void);
void list_processes(void);

#endif
