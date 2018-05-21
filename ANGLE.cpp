/*
 * ANGLE.cpp
 *
 *  Created on: May 11, 2018
 *      Author: david
 */

#include "ANGLE.h"
//  X = P6.1 A14, Y = P4.0 A13 Z = P4.2 A11
ANGLE::ANGLE(){
    m_fTaskTimems = 0.1;
    m_pMailbox = Mailbox::getMailbox();
    m_i32LastElevationAngle = 0;
    m_i32LastRotationAngle = 0;
}

uint8_t ANGLE::run(){
    st_Message l_MoutMessage;
    st_Message l_MrMessage = m_pMailbox->getMessage(ANGLE_MB_ID);

    int32_t l_i32xCoordinate, l_i32yCoordinate, l_i32zCoordinate;
    int32_t l_i32ElevationAngle = m_i32LastElevationAngle;
    int32_t l_i32RotationAngle = m_i32LastRotationAngle;
    while(l_MrMessage.bMessageValid){
        if(l_MrMessage.u8SourceID == ACCELL_MB_ID
                && l_MrMessage.u8MessageCode == ACCELL_ADC_RESULT_CODE){ //Calculates the angles
            l_i32xCoordinate = (int32_t) l_MrMessage.pPayload[0];
            l_i32yCoordinate = (int32_t) l_MrMessage.pPayload[1];
            l_i32zCoordinate = (int32_t) l_MrMessage.pPayload[2];
            float l_fxyPlaneMag = sqrt( (float) l_i32yCoordinate*l_i32yCoordinate + l_i32xCoordinate* l_i32xCoordinate);
            float l_fyzPlaneMag = sqrt((float) l_i32yCoordinate*l_i32yCoordinate + l_i32zCoordinate*l_i32zCoordinate);
            l_i32ElevationAngle = atan((float)-l_i32zCoordinate / l_fxyPlaneMag)*180/3,14;
            l_i32RotationAngle = atan((float) -l_i32xCoordinate / l_fyzPlaneMag)*180/3,14;
            m_i32LastElevationAngle = l_i32ElevationAngle;
            m_i32LastRotationAngle = l_i32RotationAngle;
        }
        l_MrMessage = m_pMailbox->getMessage(ANGLE_MB_ID);
    }
    //Sending the  elevation information
    std::memcpy(&l_MoutMessage.u32MessageData , &l_i32ElevationAngle, 4); //copy the contents of the of the
                                                              //input files. Muting int to uint
    l_MoutMessage.bMessageValid = true;
    l_MoutMessage.u8DestinationID = POSITION_MB_ID;
    l_MoutMessage.u8SourceID = ANGLE_MB_ID;
    l_MoutMessage.u8MessageCode = ANGLE_ELEVATION_ANGLE_RESULT_CODE;
    l_MoutMessage.pPayload = NULL;

    m_pMailbox->sendMessage(l_MoutMessage);
    //Sending the rotation information
    std::memcpy(&l_MoutMessage.u32MessageData , &l_i32RotationAngle, 4); //copy the contents of the of the
                                                              //input files. Muting int to uint
    l_MoutMessage.bMessageValid = true;
    l_MoutMessage.u8DestinationID = LINE_MB_ID;
    l_MoutMessage.u8SourceID = ANGLE_MB_ID;
    l_MoutMessage.u8MessageCode = ANGLE_ROTATION_ANGLE_RESULT_CODE;
    l_MoutMessage.pPayload = NULL;

    m_pMailbox->sendMessage(l_MoutMessage);


    return NO_ERR;



}

uint8_t ANGLE::setup(){ //No hardware config to be made
    return NO_ERR;
}
