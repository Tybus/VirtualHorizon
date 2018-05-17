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
}

uint8_t ANGLE::run(){

    uint16_t l_u16xyzValues[3];
    st_Message l_MreadValues;
    ADC14_getMultiSequenceResult(&l_u16xyzValues);
    m_axyzValues = (uint32_t) l_u16xyzValues; //This might be wrong, checkout

    l_MreadValues.bMessageValid = true;
    l_MreadValues.u8DestinationID = ANGLE_MB_ID;
    l_MreadValues.u8SourceID = ANGLE_MB_ID;
    l_MreadValues.u8MessageCode = ANGLE_ADC_REULT_CODE;
    l_MreadValues.u32MessageData = 3;//6 8 bit values to read.
    l_MreadValue.pPayload = this->m_axyzValues;
    printf("X: %d. /n". l_u6xyzValues[0]);
    printf("Y: %d. /n". l_u6xyzValues[1]);
    printf("Z: %d. /n". l_u6xyzValues[2]);


}

uint8_t ANGLE::setup(){
    return NO_ERR:
}
