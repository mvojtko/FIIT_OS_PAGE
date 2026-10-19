#pragma once

#include "types.h"

typedef enum tSchedulingAlgorithm
{
    // Round robin scheduling algorithm (no priority). Order of tasks is determined by storage order in tTaskMgr.tasks.
    // Each ready task receives one quantum per round.
    // One quantum is one tick.
    SCHEDULING_ALGORITHM_ROUND_ROBIN,

    // Round robin scheduling algorithm with priority.
    // A task receives priority + 1 consecutive quantums per round.
    // One quantum is one tick.
    SCHEDULING_ALGORITHM_ROUND_ROBIN_WITH_PRIORITY,

    // Lottery scheduling algorithm with priority.
    // A task receives priority + 1 tickets in each scheduling lottery.
    SCHEDULING_ALGORITHM_RANDOM_WITH_PRIORITY,

    // Fair share scheduling algorithm with priority.
    // Each user with a ready task gets an equal share of the CPU.
    // Inside that user's share, priority + 1 is the number of quantums the task
    // runs before yielding and the task's share of the user's CPU.
    // One quantum is one tick.
    SCHEDULING_ALGORITHM_FAIR_SHARE_WITH_PRIORITY,
} tSchedulingAlgorithm;

typedef struct tScheduler
{
    tPid current_task; // Current running task. -1 if no task is running.
    int32_t task_runtime; // Runtime of the task in current cycle in ticks.
    int32_t total_runtime; // Total system runtime in ticks. -1 at the start.
    const uint32_t seed; // Seed for the random scheduling algorithm. Set by the caller and never changed.
    const tSchedulingAlgorithm scheduling_algorithm; // Scheduling algorithm.
} tScheduler;

// Initializes the scheduler. Does not modify seed.
void init_scheduler(tScheduler *scheduler);

void destroy_scheduler();

// Returns the runtime of the system in ticks.
// Returns 0 if the total runtime is not available.
int32_t get_total_runtime();

// Selects the next task to run.
// This function:
//   - adds one to current task_runtime. Once a new task is selected it is reset to 0.
//   - adds one to total_runtime.
//   - adds one to the current task's runtime.
//   - Selects the next task to run based on the scheduling algorithm.
//   - The result may be that the current task is selected again or it is replaced by a new task.
//   - scheduler ignores blocked or zombie tasks.
//   - scheduler simulates resolution of task signals.
//      - If a task has sig_child it destroys only the zombie children of that task.
//      - If a task has sig_term it terminates itself. task 0 cannot be terminated.
// Returns:
//   - The PID of the next task to run.
//   - -1 if no task is available to run.
// Scheduling algorithms:
tPid schedule();
