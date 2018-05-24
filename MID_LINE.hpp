/*
 * MID_LINE.hpp
 *
 *  Created on: 21 may. 2018
 *      Author: Kevin
 */

#ifndef MID_LINE_HPP_
#define MID_LINE_HPP_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Task.hpp"
#include "Mailbox.hpp"
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.hpp"
#include <cmath>

//! MIDLINE class inherits from task
class MIDLINE : public Task {
public:
    //! CTR: get the last datapoints to print
    MIDLINE();
    //! Run Task: Print on screen the midline
    virtual uint8_t run(void);
    //! SetupTask: Calculates the coordinates to print
    virtual uint8_t setup(void);
protected:
    //! Time that the task will spend
    float m_fTaskTimems;
private:
    //! Saves the X0 coordinate of the MIDLINE
    int16_t m_ui16X0;
    //! Saves the Y0 coordinate of the MIDLINE
    int16_t m_ui16Y0;
    //! Saves the X1 coordinate of the MIDLINE
    int16_t m_ui16X1;
    //! Saves the Y1 coordinate of the MIDLINE
    int16_t m_ui16Y1;
    //! Pointer to the Mailbox.
    Mailbox * m_pMailbox;
};




#endif /* MID_LINE_HPP_ */
