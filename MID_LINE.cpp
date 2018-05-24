/*
 * MID_LINE.cpp
 *
 *  Created on: 21 may. 2018
 *      Author: trejosk
 */

#include "MID_LINE.hpp"

    /* Graphic library context */
    Graphics_Context g_sContextBlue;
    Graphics_Context g_sContextGreen;

MIDLINE::MIDLINE(){
    m_pMailbox = Mailbox::getMailbox();
    m_fTaskTimems = 10;
}

uint8_t MIDLINE::run(){
    /*
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

*/
    uint8_t l_u8LinePoint = 0;
    st_Message l_MReadMesage = m_pMailbox->getMessage(LINE_MB_ID);
    while(l_MReadMesage.bMessageValid){
        if( l_MReadMesage.u8SourceID == POSITION_MB_ID){
            l_u8LinePoint = l_MReadMesage.u32MessageData;
            break;
        }
        else
            l_MReadMesage = m_pMailbox->getMessage(LINE_MB_ID);
    }
    Graphics_Rectangle BlueRectangle = {0,0, 127, l_u8LinePoint};
    Graphics_Rectangle GreenRectangle = {0,l_u8LinePoint, 127, 127};
    Graphics_fillRectangle(&g_sContextBlue, &BlueRectangle);
    Graphics_fillRectangle(&g_sContextGreen, &GreenRectangle);
    return 0;

}

uint8_t MIDLINE::setup(){
    //MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Initializes Clock System */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContextGreen, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContextGreen, GRAPHICS_COLOR_GREEN);
    Graphics_setBackgroundColor(&g_sContextGreen, GRAPHICS_COLOR_BLUE);

    Graphics_initContext(&g_sContextBlue, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setBackgroundColor(&g_sContextBlue, GRAPHICS_COLOR_GREEN);
    Graphics_setForegroundColor(&g_sContextBlue, GRAPHICS_COLOR_BLUE);
    return 0;
    }





