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
    uint8_t priority : 4;  // Priority of the task. 0 lowest, 15 highest. (priority + 1) defines how many ticks to run before yielding.
    uint8_t signals : 2;   // Signals of the task.
    uint8_t state : 2;     // State of the task.
    uint8_t uid;           // User ID of the task.
    int32_t runtime;       // runtime of the task in ticks.
    int32_t start_time;    // start time of the task in ticks. initialized with create_task with tScheduler.total_runtime.
    int exit_code;         // Exit code of the task.
} tTaskStruct;