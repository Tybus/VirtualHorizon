#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler(){
    m_u8OpenSlots = NUMBER_OF_SLOTS;
    m_u8NextSlot = 0;
    m_pMailbox = Mailbox::getMailbox();
    m_fTickms = 1;
    m_lTotalTasks.clear();
    m_lSchedule.clear();
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
    m_list_size = m_lTotalTasks.size();
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
        l_iTaskInfo++;
    }
    CalculateNextSchedule();

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

    CalculateNextSchedule();
    return l_u8ReturnCode;
}
bool IsActiveTask(const st_TaskInfo& i_Task) {return i_Task.bTaskIsActive;};
bool IsInactiveTask(const st_TaskInfo & i_Task) {return !i_Task.bTaskIsActive;}; // How to add these into the class?
bool SortScheduleByPriority(const st_TaskInfo& i_TaskOne, const st_TaskInfo& i_TaskTwo){
    return (i_TaskOne.pTask->GetTaskPriority() < i_TaskTwo.pTask->GetTaskPriority());
}
bool TickIntervalNotZero(const st_TaskInfo & i_Task) {return (i_Task.u64ticks != 0 );};
uint8_t Scheduler::CalculateNextSchedule(void){
    //Start by looking if you have any message in your mailbox.
    m_lSchedule = m_lTotalTasks;                    //Copy the total lists // There are 3 tasks, there should only be two.
    list<st_TaskInfo>::iterator l_iTask;
    uint8_t taskId;
    uint64_t u64TickInterval;           // - How often the task is executed
    uint64_t u64ticks;                  // - Current tick count
    uint64_t u64TickIntervalInitValue;  // - Value to reset

    for(l_iTask = m_lTotalTasks.begin(); l_iTask != m_lTotalTasks.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    m_lSchedule.remove_if(IsInactiveTask);          //Remove the inactive ones This is clearing all my Stuff. debug from here.
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
        u64TickInterval = l_iTask->u64TickInterval;           // - How often the task is executed
        u64ticks = l_iTask->u64ticks;                  // - Current tick count
        u64TickIntervalInitValue = l_iTask->u64TickIntervalInitValue;  // - Value to reset
    } //Im removing task 1
    m_lSchedule.remove_if(TickIntervalNotZero);     //Remove the tasks if the interval is not zero.
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    m_lSchedule.sort(SortScheduleByPriority);       //Sort them by priority.
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    SortScheduleByTime();                           //Sort how many will be available in a tick.
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    HandleTickCount();
    for(l_iTask = m_lSchedule.begin(); l_iTask != m_lSchedule.end() ; l_iTask++){
        taskId = l_iTask->pTask->m_u8TaskID;
    }
    return(NO_ERR);
}
void Scheduler::HandleTickCount(void){
    list<st_TaskInfo>::iterator l_iTask = m_lSchedule.begin(); //Even those that were not run will be
    st_TaskInfo * l_pOriginalTask;
    while(l_iTask != m_lSchedule.end()){                       //Deleted.
        l_pOriginalTask = l_iTask->GetOriginalAddress(); //2000FF78
        switch(l_pOriginalTask->enTaskType){
            case(TaskType_OneShot):
                l_pOriginalTask->bTaskIsActive = TaskActiveFalse;
            case(TaskType_Always):
                l_pOriginalTask->u64TickInterval = 0;
                break;
            case(TaskType_Periodic):
                l_pOriginalTask -> u64TickInterval++; //Will only increment when its in 0. This is not incrementing the original task.
                if(l_iTask->u64TickInterval > l_iTask->u64TickIntervalInitValue +1)
                    l_iTask->u64TickInterval = 0;
            default:
                break;
        }
        l_iTask++;
    }
    l_iTask = m_lTotalTasks.begin(); //Same originalTask pointer for all. OriginalTask Pointer is wrong.
    while(l_iTask != m_lTotalTasks.end()){ //Reduce the counter in the not executed tasks.
        l_pOriginalTask = l_iTask->GetOriginalAddress(); //See if its the same original task. 2000FF78 Same value for all.
        if(l_iTask->bTaskIsActive && l_iTask->enTaskType == TaskType_Periodic){
            if(l_iTask->u64TickInterval != 0){
                l_iTask->u64TickInterval ++; //Will count twice if 0.
                if(l_iTask->u64TickInterval > l_iTask->u64TickIntervalInitValue +1){ //+1 to fix the bug
                    l_iTask->u64TickInterval = 0;
                }
            }
        }
        l_iTask++;
    }
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

