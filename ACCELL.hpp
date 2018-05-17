/*
 * ACCELL.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: David
 */

#ifndef ACCELL_HPP_
#define ACCELL_HPP_
#define __NOP __nop
#include "Task.hpp"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include "Mailbox.hpp"

class ACCELL : public Task
{
    public:
        ACCELL(void);
        uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
        float m_fTaskTimems;
    private:
        uint32_t m_axyzValues[3];
        Mailbox * m_pMailbox;
};

#endif /* LED_HPP_ */
