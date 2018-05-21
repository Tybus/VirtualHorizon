/*
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Task.hpp"
#include "Mailbox.hpp"
#include <stdlib.h>
#include <list>
#include <cstddef>
#include <stdio.h>

#define NUMBER_OF_SLOTS (uint8_t) 255
#define NULL            0
#define ERR_TOO_MANY_TASKS 1

using std::list;

enum TaskType{
    TaskType_OneShot = 0,
    TaskType_Always,
    TaskType_Periodic
};

enum TaskActive{
    TaskActiveTrue = true,
    TaskActiveFalse = false
};

//! Class that contains a the info of a task
class TaskInfo {
public:
    //!Default Constructor
    TaskInfo(){
        m_bTaskExists = 0;
    };
    //! Constructor with parameters
    TaskInfo(Task * i_pTask, TaskType i_enType, TaskActive i_enTaskActive, uint64_t i_u64TickInterval = 0U, uint8_t i_u8TaskPriority = 0){
        m_bTaskExists = 1;
        m_pTask = i_pTask;
        m_TaskType = i_enType;
        m_bTaskIsActive = i_enTaskActive;
        m_u64TickInterval = i_u64TickInterval;
        m_u64ticks = 0;
        m_u64TickIntervalInitValue = i_u64TickInterval;
        m_bTaskWasRun =0;
        m_u8TaskPriority = i_u8TaskPriority;
    };
    //! Returns true if the task exists
    bool TaskExists(void){return m_bTaskExists;};
    //! Return the pointer to the current task
    Task * GetTaskPtr(void){return m_pTask;};
    //! Returns the type of the task
    TaskType GetTaskType(void){return m_TaskType;};
    //! Return wheter the task is active or not.
    bool TaskActive(void) const {return m_bTaskIsActive;};
    //! Returns true if the task is inactive.
    bool TaskInactive(void) const {return !m_bTaskIsActive;};
    //! return the tick interval
    uint64_t GetTickInterval(void) const {return m_u64TickInterval;};
    //!Return the Init Value of the Tick
    uint64_t GetTickIntervalInitValue(void){return m_u64TickIntervalInitValue;};
    //! Return the priority of the Task
    uint8_t GetTaskPriority(void) const {return m_u8TaskPriority;};
    //! Adds a tick to the current task only if it is periodic.
    void AddTick(void){
        if(m_TaskType == TaskType_Periodic){
            if(m_u64TickInterval == m_u64TickIntervalInitValue)
                m_u64TickInterval = 0;
            else if(m_u64TickInterval == 0){
                if(m_bTaskWasRun)
                    m_u64TickInterval++; //It wont add 1 if the task was not run, it stays at the same value of 0
            }
            else
                m_u64TickInterval++;
        }
    };
    void run(void){
        m_pTask->run();
        m_bTaskWasRun = true; //Turn taskwasrun into true only if the task was really run
    }
    //! Deactivates the task based on Task Actives.
    void DeactivateTask(void){ m_bTaskIsActive = false;};
    //! Activates the task
    void ActivateTask(void){ m_bTaskIsActive = true;};
    //! Resets the task was run value of the task.
    void ResetRunValue(void){ m_bTaskWasRun = false;};
private:
	bool m_bTaskExists;               // Does this tas exists?
    Task * m_pTask;                   // - Pointer to the Task
    TaskType m_TaskType;                // - Task type
    bool m_bTaskIsActive;                 // - True when the task is available
    uint64_t m_u64TickInterval;           // - How often the task is executed
    uint64_t m_u64ticks;                  // - Current tick count Not been used
    uint64_t m_u64TickIntervalInitValue;  // - Value to reset
    uint8_t m_u8TaskPriority;               // Task priority
    bool m_bTaskWasRun;                     //Wheter or not the task was run at this tick
};

class Scheduler{
public:
    Scheduler();
    //! Stores ticks
    uint64_t m_u64ticks;
    //! Attaches tasks to the current scheduler
    uint8_t attach(Task * i_pTask, TaskType i_enType, TaskActive i_enTaskActive, uint64_t i_u64TickInterval = 0U, uint8_t i_u8TaskPriority = 0);
    //! Runs all the scheduled tasks.
    uint8_t run(void);
    //!  Setup all the attached tasks
    uint8_t setup(void);
    //! Returns the Tick value in ms of the scheduler
    float getSchedulerTick(void){return m_fTickms;};
    //! setss the scheduler tick in ms
    void setSechedulerTick(float i_fTickms);
    //bool TaskIsActive(const st_TaskInfo& i_Task){return i_Task.bTaskIsActive;};
    //bool TaskInactive(const st_TaskInfo & i_Task){return !i_Task.bTaskIsActive;};
private:
    uint8_t m_u8OpenSlots; // - Available slots
    uint8_t m_u8NextSlot;  // - Next available slot
    uint8_t m_u8TaskCount; // - Number of tasks attached
    TaskInfo m_aTotalTasks[NUMBER_OF_SLOTS]; // Holds all tasks.
    bool m_bTotalTasksFull;
    list<TaskInfo *> m_lSchedule; //Current Schedule to be executed.
    float m_fTickms;
    uint8_t CalculateNextSchedule(void); // - Calculate next schedule tasks (not implemented)
    //bool SortScheduleByPriority(const st_TaskInfo& i_TaskOne, const st_TaskInfo& i_TaskTwo); // - Sorts a schedule based on priority (not implemented)
    void handleTickCount(void); //Handles the tick count operations
    uint8_t SortScheduleByActive(void); // Sorts the schedule by activity.
    uint8_t SortScheduleByTime(void); //Sorts the scheduler by time
    uintptr_t m_pNextSchedule; // - Pointer to the next schedule.
    Mailbox* m_pMailbox; // Pointer to the mailbox
    void HandleTickCount(void); // Handles the tick count in the operations
    void RemoveInactiveTasks(void); //Remove all inactive tasks
    void CheckMailbox(void); //Check its mailbox
    st_Message getMail(void); //Gets its mail

};

#endif /* TASKS_SCHEDULER_HPP_ */
