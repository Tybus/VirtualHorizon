/*
 * Mailbox.hpp
 *
 *  Created on: May 1, 2018
 *      Author: eortiz
 */

#ifndef MAILBOX_HPP_
#define MAILBOX_HPP_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <vector>
#define MAX_MESSAGE_QUEUE 50
using std::vector;
struct st_Message
{
    bool     bMessageValid;   // - True when message is valid
    uint8_t  u8DestinationID; // - Destination Task ID
    uint8_t  u8SourceID;      // - Source Task ID
    uint8_t  u8MessageCode;   // - Message code, interpreted by Destination
    uint32_t u32MessageData;  // - Message data, interpreted by Destination
    uint32_t * pPayload;       // - Message Payload, interpreted by Destination
};

class Mailbox
{
public:
    static Mailbox* getMailbox();                       //Returns a pointer to this Mailbox
    bool sendMessage(st_Message i_stMessage);           //Returns 1 if error.
    st_Message getMessage(uint8_t i_u8MailboxID);       //Returns a st_Message , if bMessageValid = 0, Its not a valid message

private:
    Mailbox(){};
    static Mailbox* MailObj;
    //st_Message m_stMessageQueue[MAX_MESSAGE_QUEUE];
    vector<st_Message> m_stMessageQueue;
};

#endif /* MAILBOX_HPP_ */
