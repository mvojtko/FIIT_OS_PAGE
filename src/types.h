#pragma once

#include <stdint.h>

#define TASK_STATE_READY 0x0
#define TASK_STATE_BLOCKED 0x1
#define TASK_STATE_TERMINATED 0x2

#define TASK_SIG_TERM 0x1
#define TASK_SIG_CHILD 0x2

typedef int16_t tPid;

typedef struct tTaskStruct
{
    tPid pid;              // Process ID of the task.
    tPid ppid;             // Parent process ID of the task.
    uint8_t priority : 4;  // Priority of the task.
    uint8_t signals : 2;   // Signals of the task.
    uint8_t state : 2;     // State of the task.
    uint8_t uid;           // User ID of the task.
    int32_t runtime;       // total runtime of the task in ticks.
    int32_t start_time;    // start time of the task in ticks.
    int exit_code;         // Exit code of the task.
} tTaskStruct;