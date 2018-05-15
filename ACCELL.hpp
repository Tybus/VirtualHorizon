/*
 * ACCELL.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: David
 */

#ifndef ACCELL_HPP_
#define ACCELL_HPP_
#define __NOP __nop
#include "msp.h"
#include "Task.hpp"
#include "driverlib.h"
#include "Mailbox.hpp"
#include <>stdio.h>


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
};

#endif /* LED_HPP_ */
