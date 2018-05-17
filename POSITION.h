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

class POSITION : public Task {
public:
    POSITION();
    virtual uint8_t run(void);
    virtual uint8_t setup(void);
protected:
    float m_fTaskTimems;
private:
    uint32_t m_u32LastElevation;
    Mailbox * m_pMailbox;
};

#endif /* POSITION_H_ */
