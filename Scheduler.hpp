/*
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_
#include "msp.h"
#include "Task.hpp"
#include "Mailbox.hpp"
#include <stdlib.h>
#include <list>
#include <cstddef>
#include <stdio.h>

#define NUMBER_OF_SLOTS (uint8_t) 255
#define NULL            0
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

// - This structure defines the Task Information
class st_TaskInfo {
public:
	Task * pTask;                       // - Pointer to the Task
	TaskType enTaskType;                // - Task type
	bool bTaskIsActive;                 // - True when the task is available
	uint64_t u64TickInterval;           // - How often the task is executed
	uint64_t u64ticks;                  // - Current tick count
	uint64_t u64TickIntervalInitValue;  // - Value to reset
    st_TaskInfo(){ pOriginalAddress = this; } // -Saves a pointer to the original task
    st_TaskInfo * GetOriginalAddress(){return this->pOriginalAddress;}

private:
    st_TaskInfo * pOriginalAddress; //Saves the origin address;

};

class Scheduler{
public:
    Scheduler();
    uint64_t m_u64ticks;
    uint8_t attach(Task * i_pTask, TaskType i_enType, TaskActive i_enTaskActive, uint64_t i_u64TickInterval = 0U);
    uint8_t run(void);
    uint8_t setup(void);
    float getSchedulerTick(void){return m_fTickms;};
    void setSechedulerTick(float i_fTickms);
    bool TaskIsActive(const st_TaskInfo& i_Task){return i_Task.bTaskIsActive;};
    bool TaskInactive(const st_TaskInfo & i_Task){return !i_Task.bTaskIsActive;};
    int m_list_size;
private:
    uint8_t m_u8OpenSlots; // - Available slots
    uint8_t m_u8NextSlot;  // - Next available slot
    uint8_t m_u8TaskCount; // - Number of tasks attached
    list<st_TaskInfo> m_lTotalTasks; // Holds all tasks.
    list<st_TaskInfo> m_lSchedule; //Current Schedule to be executed.
    float m_fTickms;
    uint8_t CalculateNextSchedule(void); // - Calculate next schedule tasks (not implemented)
    //bool SortScheduleByPriority(const st_TaskInfo& i_TaskOne, const st_TaskInfo& i_TaskTwo); // - Sorts a schedule based on priority (not implemented)
    void handleTickCount(void); //Handles the tick count operations
    uint8_t SortScheduleByActive(void); // Sorts the schedule by activity.
    uint8_t SortScheduleByTime(void);
    uintptr_t m_pNextSchedule; // - Pointer to the next schedule.
    Mailbox* m_pMailbox;
    void HandleTickCount(void);

};

#endif /* TASKS_SCHEDULER_HPP_ */
