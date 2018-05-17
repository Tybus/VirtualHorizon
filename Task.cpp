#include "Task.hpp"

uint8_t Task::m_u8NextTaskID = 0; // - Init task ID
Task::Task()
{
    m_u8TaskID = m_u8NextTaskID;
    m_u8NextTaskID++;
    m_bIsFinished = false;
    m_pMailbox = Mailbox::getMailbox();
}

st_Message Task::getMessage(uint8_t i_u8TaskID)
{
    return(m_pMailbox->getMessage(m_u8TaskID));
}

bool Task::sendMessage(st_Message i_stMessage)
{
    return(m_pMailbox->sendMessage(i_stMessage));
}
