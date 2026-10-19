#pragma once

#include <stdint.h>

#include "types.h"

typedef struct tTaskMgr
{
    tTaskStruct *tasks; // Storage for data of tasks.
    uint8_t size;       // Maximum number of tasks in the task manager.
} tTaskMgr;

// Initializes the task manager. The library may have only one instance of the task manager.
// This function:
//   - Takes a pointer to the tTaskMgr structure and initializes all elements.
//   - Creates a task with priority 0, ppid -1, uid 0 at first position in the task manager.
// Returns:
//    0  Success.
//   -1  Invalid input parameters.
int init_taskMgr(tTaskMgr *task_mgr);

// Destroys the task manager and releases all resources.
// This function:
//   - Clears stored pointer to the singleton task manager.
void destroy_taskMgr();

// Returns a pointer to the task manager.
// Returns:
//   - Pointer to the task manager.
//   - NULL if the system was not initialized.
const tTaskMgr *get_taskMgr();

// Creates a new task in memory.
// This function:
//   - Finds and fills a tTaskStruct entry in the task manager.
//   - Assigns a PID to the task. Any free pid has to be assigned to the new task.
//   - Sets the parent process ID to the given ppid.
//   - Sets the user ID to the given uid.
//   - Sets the priority to the given priority.
//   - Sets start_time from the current total runtime.
//   - Sets all other fields to default values.
// Returns:
//    PID on success.
//   -1  Not enough resources to create a new task.
//   -2  Invalid input parameters. (ppid < 0, priority > 15)
//   -3  The system was not initialized.
//   -4  Parent process not found or it is a Zombie task.
tPid create_task(uint8_t priority, tPid ppid, uint8_t uid);

// Terminates a task. Standard exit scenario or system call. Creates Zombie task.
// This function:
//   - Marks the corresponding tTaskStruct entry in the task manager TASK_STATE_TERMINATED
//   - Stores exit code to its tTaskStruct entry.
//   - Signals parent process that the child has been destroyed. TASK_SIG_CHILD
//   - Allowed on any task but task 0
// Returns:
//    0  Success.
//   -1  Task does not exist or it is a Zombie task or it is the task 0.
//   -3  The system was not initialized.
int terminate_task(tPid pid, int exit_code);

// Destroys a task. Forced exit scenario without creation of Zombie task.
// This function:
//   - Cleans corresponding tTaskStruct entry in the task manager. Sets PID to -1 marking it free.
//   - Allowed on any task but task 0, even if it is a Zombie task.
// Returns:
//    0  Success.
//   -1  Task does not exist or it is the task 0.
//   -3  The system was not initialized.
int destroy_task(tPid pid);

// Sends a signal to a task.
// This function:
//   - Sends a signal to the corresponding tTaskStruct entry in the task manager.
// Returns:
//    0  Success.
//   -1  Task does not exist or it is a Zombie task.
//   -3  The system was not initialized.
int send_signal(tPid pid, uint8_t signal);

// Blocks a task.
// This function:
//   - Blocks the corresponding tTaskStruct entry in the task manager.
//     This causes the task will not be scheduled until it is unblocked.
// Returns:
//    0  Success.
//   -1  Task does not exist or it is a Zombie task.
//   -3  The system was not initialized.
int block_task(tPid pid);

// Unblocks a task.
// This function:
//   - Unblocks the corresponding tTaskStruct entry in the task manager.
// Returns:
//    0  Success.
//   -1  Task does not exist or it is a Zombie task.
//   -3  The system was not initialized.
int unblock_task(tPid pid);
