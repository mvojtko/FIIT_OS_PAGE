#pragma once

#include "types.h"

typedef enum tSchedulingAlgorithm
{
    // Round robin scheduling algorithm (no priority).
    SCHEDULING_ALGORITHM_ROUND_ROBIN,

    // Round robin scheduling algorithm with priority (priority based on longer runtime of the task).
    SCHEDULING_ALGORITHM_ROUND_ROBIN_WITH_PRIORITY,

    // Random scheduling algorithm (priority based on multiple tickets assigned to the task).
    SCHEDULING_ALGORITHM_RANDOM_WITH_PRIORITY,

    // Fair share scheduling algorithm with priority Each user gets a fair share of the CPU.
    // (priority based on longer runtime of the task).
    SCHEDULING_ALGORITHM_FAIR_SHARE_WITH_PRIORITY,
} tSchedulingAlgorithm;

typedef struct tScheduler
{
    tPid current_task; // Current running task. -1 if no task is running.
    int32_t task_runtime; // Runtime of the task in current cycle in ticks.
    int32_t total_runtime; // Total system runtime in ticks. -1 at the start.
    const tSchedulingAlgorithm scheduling_algorithm; // Scheduling algorithm.
} tScheduler;

void init_scheduler(tScheduler *scheduler);

void destroy_scheduler();

// Returns the runtime of the system in ticks.
// Returns 0 if the total runtime is not available.
int32_t get_total_runtime();

// Selects the next task to run.
// This function:
//   - adds one to curent task_runtime.
//   - adds one to total_runtime.
//   - Selects the next task to run based on the scheduling algorithm.
//   - The result may be that the curent task is selected again or it is replaced by a new task.
//   - If the current task is not selected again its runtime is added to the tasks runtime.
//   - scheduler ignores blocked or zombie tasks.
//   - scheduler simulates that that resolves task signals.
//      - If task has sig_child it destroys all zombies.
//      - If task has sig_term it terminates itself.
// Returns:
//   - The PID of the next task to run.
//   - -1 if no task is available to run.
// Scheduling algorithms:
tPid schedule();
