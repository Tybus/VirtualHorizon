/*
 * Mailbox.cpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#include <Mailbox.hpp>
#include <stdio.h>
#define TASKS_QUANTITY 10

Mailbox* Mailbox::MailObj = new Mailbox();

extern "C"
{
    Mailbox* Mailbox::getMailbox(){
        return MailObj;
    }

    st_Message Mailbox::getMessage(uint8_t i_u8MailboxID)                            //asking for a message with the destination task
    {
        st_Message l_stMessage;
        uint8_t l_u8Searcher = 0;                                                    //Used to search the messages to N destination at each N+l_u8Searcher*TASKS_QUANTITY gap into  m_stMessageQueue
        while((i_u8MailboxID + TASKS_QUANTITY*l_u8Searcher) <= MAX_MESSAGE_QUEUE){
            if(m_stMessageQueue[i_u8MailboxID + TASKS_QUANTITY*l_u8Searcher].bMessageValid == true){
                l_stMessage = m_stMessageQueue[i_u8MailboxID + TASKS_QUANTITY*l_u8Searcher];
                m_stMessageQueue[i_u8MailboxID + TASKS_QUANTITY*l_u8Searcher].bMessageValid = false;                // Message read done
                return(l_stMessage);
            }
            else{
                l_u8Searcher++;
            }
        }
        l_stMessage.u32MessageData = 0;                                               //0 means old message
        return(l_stMessage);
    }

    bool Mailbox::sendMessage(st_Message i_stMessage) //TODO
    {
        uint8_t l_u8Positioner = 0; //Used to place the messages to N destination at each N+l_u8Positioner*TASKS_QUANTITY gap into  m_stMessageQueue
        while((i_stMessage.u8DestinationID + TASKS_QUANTITY*l_u8Positioner) <= MAX_MESSAGE_QUEUE){
            int k = i_stMessage.u8DestinationID + TASKS_QUANTITY*l_u8Positioner;
            printf("Position is: %d\n", k);
            if(m_stMessageQueue[i_stMessage.u8DestinationID + TASKS_QUANTITY*l_u8Positioner].bMessageValid == false)   //If there isn't any message valid for the destination task
            {
                m_stMessageQueue[i_stMessage.u8DestinationID + TASKS_QUANTITY*l_u8Positioner] = i_stMessage;
                return(true);
            }
            else
            {
                l_u8Positioner++;
            }
        }
        return(false);
    }

    void Mailbox::ValidBitCleaner(){
        for(uint8_t l_iPosition = 0; l_iPosition<= sizeof(m_stMessageQueue); l_iPosition++){
            m_stMessageQueue[l_iPosition].bMessageValid = false;
        }
    }
}


