/*
 * POSITION.h
 *
 *  Created on: May 15, 2018
 *      Author: david
 */

#ifndef POSITION_H_
#define POSITION_H_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Task.hpp"
#include "Mailbox.hpp"
//! POSITION class inherits from task
class POSITION : public Task {
public:
    //! DTF CTR
    POSITION();
    //! Run Task
    virtual uint8_t run(void);
    //! SetupTask
    virtual uint8_t setup(void);
protected:
    //! Time of the task
    float m_fTaskTimems;
private:
    //! Saves the last elevation data
    uint32_t m_u32LastElevation;
    //! Pointer to the Mailbox.
    Mailbox * m_pMailbox;
};

#endif /* POSITION_H_ */
