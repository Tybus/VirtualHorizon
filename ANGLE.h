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

//! ANGLE class inherits from task
class ANGLE : public Task
{
    public:
        //! CTR
        ANGLE(void);
        //! Run the task
        virtual uint8_t run(void);
        //! Setups the task
        virtual uint8_t setup(void);
    protected:
        //! Time of the task
        float m_fTaskTimems;
    private:
        //! Read angle of elevation
        int32_t m_i32LastElevationAngle;
        //! Read angle of rotation
        int32_t m_i32LastRotationAngle;
        //! Pointer to the mailbox
        Mailbox * m_pMailbox;
};

#endif /* LED_HPP_ */
