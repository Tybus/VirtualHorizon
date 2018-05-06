#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler(){
    m_u8OpenSlots = NUMBER_OF_SLOTS;
    m_u8NextSlot = 0;
    m_pMailbox = Mailbox::getMailbox();
    m_fTickms = 1;
    m_lTotalTasks.clear();
    return;
}

// - The attach function, inserts the task into the schedule slots.
uint8_t Scheduler::attach(Task * i_pTask, TaskType i_enTaskType,
                          TaskActive i_enTaskIsActive, uint64_t i_u64TickInterval){
    uint8_t l_ErrorCode = NO_ERR;
    st_TaskInfo l_stTaskInfo;

    l_stTaskInfo.pTask = i_pTask;
    l_stTaskInfo.bTaskIsActive = i_enTaskIsActive;
    l_stTaskInfo.u64ticks = this->m_u64ticks;
    l_stTaskInfo.u64TickInterval = 0;
	l_stTaskInfo.u64TickIntervalInitValue = i_u64TickInterval;
	l_stTaskInfo.enTaskType = i_enTaskType;

	m_lTotalTasks.push_back(l_stTaskInfo);
    return l_ErrorCode;
}
// - Execute the current schedule
uint8_t Scheduler::run(void){
    Task * l_pTask = NULL;
    uint8_t l_u8ReturnCode = NO_ERR;
    list<st_TaskInfo>::iterator l_iTaskInfo = m_lSchedule.begin();
    while(l_iTaskInfo != m_lSchedule.end()){
        l_pTask = l_iTaskInfo->pTask;
        l_pTask->run();
    }

    while(l_u8NextSlot < NUMBER_OF_SLOTS){
        l_pNextTask = m_aSchedule[l_u8NextSlot].pTasks;
        if(l_pNextTask != NULL){
           if(m_aSchedule[l_u8NextSlot].bTaskIsActive){
                // - Execute the task slot
                if(m_aSchedule[l_u8NextSlot].u64TickInterval == 0){
                    l_pNextTask->run();
                }

                // - Depending on the task type, handle the tick count
                switch(m_aSchedule[l_u8NextSlot].enTaskType){
                    case(TaskType_OneShot):
                        m_aSchedule[l_u8NextSlot].bTaskIsActive = TaskActiveFalse;
                        // - Intentional fall-through
                    case(TaskType_Always):
                        m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        break;
                    case(TaskType_Periodic):
                        m_aSchedule[l_u8NextSlot].u64TickInterval ++;
                        if(m_aSchedule[l_u8NextSlot].u64TickInterval > m_aSchedule[l_u8NextSlot].u64TickIntervalInitValue){
                            m_aSchedule[l_u8NextSlot].u64TickInterval = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            // - If we found an uninitialized slot, break from the execution loop
            break;
        }
		l_u8NextSlot++;
    }
    //CalculateNextSchedule(); // TODO

    return l_u8ReturnCode;
    */
    return l_u8ReturnCode;
}
// - Execute the setup function for all tasks
uint8_t Scheduler::setup(void){
    list<st_TaskInfo>::iterator l_iTaskInfo = m_lTotalTasks.begin();
    Task * l_pTask = NULL;
    uint8_t l_u8ReturnCode = NO_ERR;
    // - Run the setup function for all available tasks.
    while(l_iTaskInfo != m_lTotalTasks.end()){
        l_pTask = l_iTaskInfo->pTask;
        l_pTask->setup();
        l_iTaskInfo++;
    }

    CalculateNextSchedule(); //TODO
    return l_u8ReturnCode;
}
bool IsActiveTask(const st_TaskInfo& i_Task) {return i_Task.bTaskIsActive;};
bool IsInactiveTask(const st_TaskInfo & i_Task) {return !i_Task.bTaskIsActive;}; // How to add these into the class?
bool SortScheduleByPriority(const st_TaskInfo& i_TaskOne, const st_TaskInfo& i_TaskTwo){
    return (i_TaskOne.pTask->GetTaskPriority() < i_TaskTwo.pTask->GetTaskPriority());
}
uint8_t Scheduler::CalculateNextSchedule(void){
    m_lSchedule = m_lTotalTasks;                    //Copy the total lists
    m_lSchedule.remove_if(IsInactiveTask);            //Remove the inactive ones
    m_lSchedule.sort(SortScheduleByPriority);       //Sort them by priority.
    SortScheduleByTime();                           //Sort how many will be available in a tick.
    return(NO_ERR);
}

uint8_t Scheduler::SortScheduleByTime(void){
    float l_fTotalTaskTime = 0;
    list<st_TaskInfo>::iterator l_iTask = m_lSchedule.begin();
    float l_fSchedulerTick = getSchedulerTick();
    float l_fTaskTime = 0;
    uint8_t l_taskPriority = 255;
    uint8_t l_currentPriority;

    while(l_iTask != m_lSchedule.end()){ //Iterate the whole array
        if(l_fTotalTaskTime < l_fSchedulerTick){ //
            l_fTaskTime = l_iTask->pTask->getTaskTimems();
            if(l_fTotalTaskTime + l_fTaskTime >= l_fSchedulerTick){
                l_currentPriority = l_iTask->pTask->GetTaskPriority();
                l_taskPriority = (l_currentPriority < l_taskPriority) ?
                        l_currentPriority : l_taskPriority;
                l_iTask = m_lSchedule.erase(l_iTask);
            }
            else if (l_iTask->pTask->GetTaskPriority() > l_taskPriority) {
                l_iTask = m_lSchedule.erase(l_iTask);
                l_fTotalTaskTime += l_fSchedulerTick; // add a tick to ensure you wont enter again
            }
            else
                l_iTask++;
        }
        else{
            l_iTask = m_lSchedule.erase(l_iTask);//Remove the entry, because no more time.
        }
    }
    return(NO_ERR);
}

