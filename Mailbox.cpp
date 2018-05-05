/*
 * Mailbox.cpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#include <Mailbox.hpp>

Mailbox* Mailbox::MailObj = new Mailbox();

extern "C"
{
    Mailbox* Mailbox::getMailbox(){
        return MailObj;
    }

    st_Message Mailbox::getMessage(uint8_t i_u8MailboxID) //TODO
    {
        st_Message l_stMessage;

        l_stMessage = m_stMessageQueue[i_u8MailboxID];

        return(l_stMessage);
    }

    bool Mailbox::sendMessage(st_Message i_stMessage) //TODO
    {
        if(m_stMessageQueue[i_stMessage.u8DestinationID].bMessageValid == false)
        {
            m_stMessageQueue[i_stMessage.u8DestinationID] = i_stMessage;
            return(true);
        }
        else
        {
            return(false);
        }
    }
}


