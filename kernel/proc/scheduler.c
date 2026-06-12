/*
 * NovaOS Process Scheduler
 * Preemptive multitasking scheduler
 */

#include "scheduler.h"
#include "../include/types.h"
#include "../include/stdio.h"

#define MAX_PROCESSES 256
#define TIME_SLICE 10  /* milliseconds */

typedef struct {
    uint32_t id;
    char name[32];
    uint32_t state;
    uint64_t priority;
    uint64_t time_remaining;
    void *stack;
    uint64_t rsp;
    uint64_t rip;
} process_t;

static process_t processes[MAX_PROCESSES];
static uint32_t process_count = 0;
static uint32_t current_process = 0;

/**
 * Initialize scheduler
 */
void init_scheduler(void)
{
    kprintf("  [SCHED] Initializing process scheduler...\n");
    
    /* Initialize process table */
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].id = i;
        processes[i].state = PROCESS_UNUSED;
    }
    
    /* Create idle process */
    create_process("idle", idle_process, PRIORITY_LOW);
    
    kprintf("  [SCHED] Scheduler initialized with %u process slots\n", MAX_PROCESSES);
}

/**
 * Create new process
 */
uint32_t create_process(const char *name, void (*entry)(void), uint32_t priority)
{
    if (process_count >= MAX_PROCESSES) {
        return -1;
    }
    
    uint32_t pid = process_count++;
    process_t *proc = &processes[pid];
    
    proc->id = pid;
    strncpy(proc->name, name, 31);
    proc->name[31] = '\0';
    proc->state = PROCESS_READY;
    proc->priority = priority;
    proc->time_remaining = TIME_SLICE;
    
    kprintf("  [SCHED] Created process: %s (PID: %u)\n", name, pid);
    
    return pid;
}

/**
 * Idle process
 */
void idle_process(void)
{
    while (1) {
        asm volatile("hlt");
    }
}

/**
 * Schedule next process
 */
uint32_t schedule(void)
{
    current_process = (current_process + 1) % process_count;
    return current_process;
}

/**
 * Get current process
 */
process_t *get_current_process(void)
{
    return &processes[current_process];
}

/**
 * List all processes
 */
void list_processes(void)
{
    kprintf("Process List:\n");
    kprintf("PID | Name              | State\n");
    kprintf("----+-------------------+--------\n");
    
    for (int i = 0; i < process_count; i++) {
        process_t *proc = &processes[i];
        const char *state_str = "Unknown";
        
        switch (proc->state) {
            case PROCESS_READY:      state_str = "Ready"; break;
            case PROCESS_RUNNING:    state_str = "Running"; break;
            case PROCESS_BLOCKED:    state_str = "Blocked"; break;
            case PROCESS_TERMINATED: state_str = "Terminated"; break;
        }
        
        kprintf("%3u | %-17s | %s\n", proc->id, proc->name, state_str);
    }
}
