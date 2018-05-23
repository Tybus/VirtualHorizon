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
#include <stdio.h>
#include "Mailbox.hpp"
//! ACCELL Class, INherits form Task
class ACCELL : public Task
{
    public:
        //! STD CTR
        ACCELL(void);
        //! Run the task
        virtual uint8_t run(void);
        //! Setup The task
        virtual uint8_t setup(void);
    protected:
        //!Time that the task will spend
        float m_fTaskTimems;
    private:
        //! Read Values of the Accelerometer for the xyz values
        int32_t m_axyzValues[3];
        //! Pointer to the mailbox
        Mailbox * m_pMailbox;
};

#endif /* LED_HPP_ */
