#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler(){
    m_u8OpenSlots = NUMBER_OF_SLOTS;
    m_u8NextSlot = 0;
    m_pMailbox = Mailbox::getMailbox();
    m_fTickms = 1;
    m_bTotalTasksFull = 0;
    return;
}

// - The attach function, inserts the task into the schedule slots.
uint8_t Scheduler::attach(Task * i_pTask, TaskType i_enTaskType,
                          TaskActive i_enTaskActive, uint64_t i_u64TickInterval,
                          uint8_t i_u8TaskPriority){
    uint8_t l_ErrorCode = NO_ERR;
    if(!m_bTotalTasksFull){
        TaskInfo l_TaskInfo = TaskInfo(i_pTask, i_enTaskType, i_enTaskActive, i_u64TickInterval, i_u8TaskPriority);
        m_aTotalTasks[m_u8NextSlot] = l_TaskInfo;
        m_u8NextSlot++;
        if(m_u8NextSlot == 255){
            m_bTotalTasksFull = 1;
            l_ErrorCode = ERR_TOO_MANY_TASKS;
        }

    }
    return l_ErrorCode;
}
// - Execute the current schedule
uint8_t Scheduler::run(void){
    list<TaskInfo *>::iterator l_iTaskInfo;
    TaskInfo * l_pTaskInfo;
    uint8_t l_u8ReturnCode = NO_ERR;
    for(l_iTaskInfo = m_lSchedule.begin(); l_iTaskInfo != m_lSchedule.end() ; l_iTaskInfo++ ){
        l_pTaskInfo = (*l_iTaskInfo);
        l_pTaskInfo->run();
    }
    HandleTickCount();
    CalculateNextSchedule();

    return l_u8ReturnCode;
}
// - Execute the setup function for all tasks
uint8_t Scheduler::setup(void){
    Task * l_pTask;
    uint8_t l_u8ReturnCode = NO_ERR;
    // - Run the setup function for all available tasks.
    for(uint8_t i = 0; i <  NUMBER_OF_SLOTS; i++ ){
        if(m_aTotalTasks[i].TaskExists() == false)
            break;
        l_pTask = m_aTotalTasks[i].GetTaskPtr();
        l_pTask->setup();
    }
    HandleTickCount();
    CalculateNextSchedule();
    return l_u8ReturnCode;
}

bool IsActiveTask(TaskInfo * const & i_pTaskInfo) {return i_pTaskInfo->TaskActive();};
bool IsInactiveTask(TaskInfo* const & i_pTaskInfo) {return i_pTaskInfo->TaskInactive();}; // How to add these into the class?
bool SortScheduleByPriority(TaskInfo* const & i_pTaskInfoOne, TaskInfo* const & i_pTaskInfoTwo){
    return (i_pTaskInfoOne->GetTaskPriority() < i_pTaskInfoTwo->GetTaskPriority() );
}
bool TickIntervalNotZero(TaskInfo* const & i_pTaskInfo) {return (i_pTaskInfo->GetTickInterval() != 0 );};

void Scheduler::RemoveInactiveTasks(void){
    for(uint8_t i = 0; i <  NUMBER_OF_SLOTS; i++ ){
        if(m_aTotalTasks[i].TaskExists() == false)
            break;

    }
}
st_Message Scheduler::getMail(){
    return m_pMailbox->getMessage(SCHEDULER_MB_ID);
}
void Scheduler::CheckMailbox(void){
    st_Message l_MailBoxMessage = getMail();
    while(l_MailBoxMessage.bMessageValid){
        //Switch on what to do depending on the message.

        l_MailBoxMessage = getMail();
    }
}
uint8_t Scheduler::CalculateNextSchedule(void){
    m_lSchedule.clear();
    //Start by looking if you have any message in your mailbox.
    CheckMailbox();
    for(uint8_t i = 0; i< NUMBER_OF_SLOTS; i++){
        if(m_aTotalTasks[i].TaskExists() ==false)
            break;
        m_lSchedule.push_back(&m_aTotalTasks[i]);
    }
    m_lSchedule.remove_if(IsInactiveTask);         //Remove the inactive ones
    list<TaskInfo *>::iterator l_iTaskInfo = m_lSchedule.begin();
    TaskInfo * l_pTask;
    m_lSchedule.remove_if(TickIntervalNotZero);     //Remove the tasks if the interval is not zero.
    m_lSchedule.sort(SortScheduleByPriority);       //Sort them by priority.
    SortScheduleByTime();                           //Sort how many will be available in a tick.
    return(NO_ERR);
}
void Scheduler::HandleTickCount(void){
    for(uint8_t i= 0; i<NUMBER_OF_SLOTS; i++){
        if(m_aTotalTasks[i].TaskExists() == false)
            break;
        switch(m_aTotalTasks[i].GetTaskType()){ // If task is active?
        case(TaskType_OneShot):
            m_aTotalTasks[i].DeactivateTask();
            break;
        case(TaskType_Always): //basically do nothing
            break;
        case(TaskType_Periodic):
            m_aTotalTasks[i].AddTick();
            break;
        default:
            break;
        }
        m_aTotalTasks[i].ResetRunValue();
    }
}
uint8_t Scheduler::SortScheduleByTime(void){
    float l_fTotalTaskTime = 0;
    list<TaskInfo *>::iterator l_iTaskInfo = m_lSchedule.begin();
    float l_fSchedulerTick = getSchedulerTick();
    float l_fTaskTime = 0;
    uint8_t l_taskPriority = 255;
    uint8_t l_currentPriority;
    Task * l_pTask;
    while(l_iTaskInfo != m_lSchedule.end()){ //Iterate the whole array
        if(l_fTotalTaskTime < l_fSchedulerTick){ //
            l_pTask = (*l_iTaskInfo)->GetTaskPtr();
            l_fTaskTime = l_pTask->getTaskTimems(); //pTask->getTaskTimems();
            if(l_fTotalTaskTime + l_fTaskTime >= l_fSchedulerTick){
                l_currentPriority = (*l_iTaskInfo)->GetTaskPriority();
                l_taskPriority = (l_currentPriority < l_taskPriority) ?
                        l_currentPriority : l_taskPriority;
                l_iTaskInfo = m_lSchedule.erase(l_iTaskInfo);
            }
            else if ((*l_iTaskInfo)->GetTaskPriority() > l_taskPriority) {
                l_iTaskInfo = m_lSchedule.erase(l_iTaskInfo);
                l_fTotalTaskTime += l_fSchedulerTick; // add a tick to ensure you wont enter again
            }
            else
                l_iTaskInfo++;
        }
        else{
            l_iTaskInfo = m_lSchedule.erase(l_iTaskInfo);//Remove the entry, because no more time.
        }
    }
    return(NO_ERR);
}

