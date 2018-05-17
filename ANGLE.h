/*
 * ANGLE.h
 *  Created on: Aug 31, 2016
 *      Author: David
 */

#ifndef ANGLE_HPP_
#define ANGLE_HPP_
#define __NOP __nop
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Task.hpp"
#include "Mailbox.hpp"
#include <math.h>


class ANGLE : public Task
{
    public:
        ANGLE(void);
        uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
        float m_fTaskTimems;
    private:
        uint32_t m_axyzValues[3];
        int32_t m_i32LastElevationAngle;
        int32_t m_i32LastRotationAngle;
        Mailbox * m_pMailbox;
};

#endif /* LED_HPP_ */
