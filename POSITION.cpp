/*
 * POSITION.cpp
 *
 *  Created on: May 15, 2018
 *      Author: david
 */
#include "POSITION.h"
POSITION::POSITION(){
    m_fTaskTimems = 0.1;
    m_u32LastElevation = 0;
    m_pMailbox = Mailbox::getMailbox();
}
uint8_t POSITION::setup(){
    return NO_ERR;
}
uint8_t POSITION::run(){
    st_Message l_MrMessage = m_pMailbox->getMessage(POSITION_MB_ID);
    st_Message l_MoutMessage;
    int32_t l_i32ElevationAngle;
    uint32_t l_u32Elevation = m_u32LastElevation;
    while(l_MrMessage.bMessageValid){
        if(l_MrMessage.u8SourceID == ANGLE_MB_ID
                && l_MrMessage.u8MessageCode == ANGLE_ELEVATION_ANGLE_RESULT_CODE){
            std::memcpy(&l_i32ElevationAngle, &l_MrMessage.u32MessageData, 4);
            l_u32Elevation = 64 + 0.71*l_i32ElevationAngle;
            m_u32LastElevation = l_u32Elevation;
        }
    }
    l_MoutMessage.bMessageValid = true;
    l_MoutMessage.pPayload = NULL;
    l_MoutMessage.u32MessageData = l_u32Elevation;
    l_MoutMessage.u8DestinationID = LINE_MB_ID;
    l_MoutMessage.u8MessageCode = POSITION_ELEVATION;
    l_MoutMessage.u8SourceID = POSITION_MB_ID;

    m_pMailbox->sendMessage(l_MoutMessage);

    return NO_ERR;
}


