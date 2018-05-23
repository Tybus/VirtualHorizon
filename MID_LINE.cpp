/*
 * MID_LINE.cpp
 *
 *  Created on: 21 may. 2018
 *      Author: trejosk
 */

#include "MID_LINE.hpp"

    /* Graphic library context */
    Graphics_Context g_sContext;

MIDLINE::MIDLINE(){
    m_pMailbox = Mailbox::getMailbox();
    m_fTaskTimems = 10;
}

uint8_t MIDLINE::run(){
    Graphics_clearDisplay(&g_sContext);
    st_Message l_MreadMessages;
    st_Message l_MreadMessages2;
    l_MreadMessages = m_pMailbox -> getMessage(LINE_MB_ID);

    int16_t l_iAngle = 0;
    uint16_t l_iPosition = 0;

    if(l_MreadMessages.u8SourceID == ANGLE_MB_ID){
        l_iAngle = (int16_t) l_MreadMessages.u32MessageData; // Type-cast to convert uint32_t to int32_t
        //printf("Angulo en primer mensaje\n");
        //printf("angle is %d \n", l_iAngle);
    }
    if(l_MreadMessages.u8SourceID == POSITION_MB_ID){
        l_iPosition = (uint16_t) l_MreadMessages.u32MessageData; // Type-cast to convert uint32_t to int32_t
        //printf("posicion en primer mensaje\n");
        //printf("Position is %d \n", l_iPosition);
    }

    l_MreadMessages2 = m_pMailbox -> getMessage(LINE_MB_ID);

    if(l_MreadMessages2.u8SourceID == POSITION_MB_ID){
        l_iPosition = (uint16_t) l_MreadMessages2.u32MessageData; // Type-cast to convert uint32_t to int32_t
        //printf("posicion en segundo mensaje\n");
        //printf("Position is %d \n", l_iPosition);
    }
    if(l_MreadMessages2.u8SourceID == ANGLE_MB_ID){
        l_iAngle = (int16_t) l_MreadMessages2.u32MessageData; // Type-cast to convert uint32_t to int32_t
        //printf("Angulo en segundo mensaje\n");
        //printf("angle is %d \n", l_iAngle);
    }
    printf("Position is %d, and angle is %d \n", l_iPosition, l_iAngle);

    //Graphics_clearDisplay(&g_sContext);

    if(l_iAngle <= 45 && l_iAngle >= 0){
        //Graphics_clearDisplay(&g_sContext);
        m_ui16X0 = 0;
        m_ui16X1 = 127;
        m_ui16Y1 = l_iPosition + ((l_iAngle*64)/45);
        m_ui16Y0 = l_iPosition - ((l_iAngle*64)/45);
        //Graphics_clearDisplay(&g_sContext);
        //printf("0 < angle < 45 \n x0 %d, y0 %d, x1 %d y y1 %d \n", m_ui16X0, m_ui16Y0, m_ui16X1, m_ui16Y1);
        //printf("Positon is %d and angle is %d\n", l_iPosition, l_iAngle);
        //Graphics_drawLine(&g_sContext, 0, (l_iPosition - ((l_iAngle*64)/45)), 127, (l_iPosition + ((l_iAngle*64)/45)));
    }

    if(l_iAngle < 0 && l_iAngle >= -45){
        //Graphics_clearDisplay(&g_sContext);
        m_ui16X0 = 0;
        m_ui16X1 = 127;
        m_ui16Y1 = l_iPosition + ((l_iAngle*64)/45);
        m_ui16Y0 = l_iPosition - ((l_iAngle*64)/45);
        //Graphics_clearDisplay(&g_sContext);
        //printf("-45< angle < 0 \n x0 %d, y0 %d, x1 %d y y1 %d \n", m_ui8X0, m_ui8Y0, m_ui8X1, m_ui8Y1);
        //printf("Positon is %d and angle is %d\n", l_iPosition, l_iAngle);
        //Graphics_drawLine(&g_sContext, m_ui16X0, m_ui16Y0, m_ui16X1, m_ui16Y1);
    }

    if(l_iAngle > 45){
        Graphics_clearDisplay(&g_sContext);
        //m_ui16Y0 = 0;
        //m_ui16Y1 = 127;
        //m_ui16X0 = l_iPosition - 64 + ((l_iAngle-45)*64)/45;
        //m_ui16X1 = 64 + l_iPosition - ((l_iAngle-45)*64)/45;
        //printf("x0 %d, y0 %d, x1 %d y y1 %d \n", m_ui8X0, m_ui8Y0, m_ui8X1, m_ui8Y1);
        //printf("Positon is %d and angle is %d\n", l_iPosition, l_iAngle);
        //Graphics_drawLine(&g_sContext, m_ui16X0, m_ui16Y0, m_ui16X1, m_ui16Y1);
        //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
        Graphics_drawStringCentered(&g_sContext,
                                            (int8_t *)"DANGER",
                                            6,
                                            64,
                                            30,
                                            OPAQUE_TEXT);
    }
    if(l_iAngle < -45){
        Graphics_clearDisplay(&g_sContext);
        //m_ui16Y0 = 0;
        //m_ui16Y1 = 127;
        //m_ui16X0 = l_iPosition - ((l_iAngle+45)*63.5)/45;
        //m_ui16X1 = l_iPosition + ((l_iAngle+45)*64)/45;
        //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
        Graphics_drawStringCentered(&g_sContext,
                                            (int8_t *)"DANGER",
                                            AUTO_STRING_LENGTH,
                                            64,
                                            30,
                                            OPAQUE_TEXT);
    }


    uint8_t l_iShorterY = 0;
    uint8_t l_iBiggerY = 0;
    if(m_ui16Y1 >= m_ui16Y0){
        l_iShorterY = m_ui16Y0;
        l_iBiggerY = m_ui16Y1;
        //for(uint8_t l_iIterator = l_iBiggerY; l_iIterator >= l_iShorterY; l_iIterator --){
          //  Graphics_drawLine(&g_sContext, 0, l_iIterator, 127, l_iShorterY);
        //}
    }
    if(m_ui16Y0 > m_ui16Y1){
        l_iShorterY = m_ui16Y1;
        l_iBiggerY = m_ui16Y0;
        //for(uint8_t l_iIterator = l_iBiggerY; l_iIterator >= l_iShorterY; l_iIterator --){
        //    Graphics_drawLine(&g_sContext, 0, l_iShorterY, 127, l_iIterator);
        //}
    }
    Graphics_Rectangle myRectangle1 = {0, l_iBiggerY, 128, 128};
    Graphics_fillRectangle(&g_sContext, &myRectangle1);
    return 0;

}

uint8_t MIDLINE::setup(){

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    return 0;
    }





