#include <ti/devices/msp432p4xx/inc/msp.h>
#include "main.hpp"
#include "Scheduler.hpp"
#include "Task.hpp"
#include "LED.hpp"
#include <Timer32.h>
#include "ACCELL.hpp"
#include "ANGLE.h"
#include "POSITION.h"
#include "MID_LINE.hpp"
//#include "ACCELL.hpp"


volatile static uint64_t g_SystemTicks = 0; // - The system counter.
Mailbox* g_Mailbox = Mailbox::getMailbox();
Scheduler g_MainScheduler; // - Instantiate a Scheduler

// #########################
//          MAIN
// #########################
 void main(void){
    g_Mailbox->ValidBitCleaner(); //Cleans the Mailbox.
    Setup(g_MainScheduler.getSchedulerTick());
    // - Instantiate two new Tasks
    ACCELL Accelerometer = ACCELL();
    ANGLE Angle = ANGLE();
    POSITION Position = POSITION();
    MIDLINE ML = MIDLINE();
    //Attach all the tasks.

    Angle.setup();
    Position.setup();
    ML.setup();
    Accelerometer.setup();
    while(1){
        Accelerometer.run();
        Angle.run();
        Position.run();
        ML.run();
    }
    g_MainScheduler.attach(&ML, TaskType_Periodic, TaskActiveTrue,50, 7);
    g_MainScheduler.attach(&Accelerometer, TaskType_Always, TaskActiveTrue,0,4);
    g_MainScheduler.attach(&Angle, TaskType_Always, TaskActiveTrue,0 , 5);
    g_MainScheduler.attach(&Position, TaskType_Always, TaskActiveTrue,0, 6);
    // - Run the Setup for the scheduler and all task
    g_MainScheduler.setup();
    // - Main Loop
    while(1)
    {
        __wfe(); // Wait for Event
        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //- Only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }
}

// **********************************
// Setup function for the application
// @input - none
// @output - none
// **********************************
void Setup(float i_fTickms){
    uint32_t l_u32Prescale;
    uint32_t l_u32CountValue;
    // ****************************
    //         DEVICE CONFIG
    // ****************************
    // - Disable WDT
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // ****************************
    //         PORT CONFIG
    // ****************************
    // - P1.0 is connected to the Red LED
    // - This is the heart beat indicator.
    P1->DIR |= BIT0; //Red LED

    // ****************************
    //       TIMER CONFIG
    // ****************************
    // - Configure Timer32_1  with MCLK (3Mhz), Division by 1, Enable the interrupt, Periodic Mode
    // - Enable the interrupt in the NVIC
    // - Start the timer in UP mode.
    // - Re-enable interrupts

    l_u32Prescale = Timer32::calculatePrescale(i_fTickms);
    l_u32CountValue = Timer32::calculateValue(i_fTickms, l_u32Prescale);
    TIMER32_1->LOAD = l_u32CountValue;
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_IE | l_u32Prescale |
            TIMER32_CONTROL_MODE | TIMER32_CONTROL_SIZE;

    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);
    __enable_irq();

    return;
}

extern "C"
{
    // - Handle the Timer32 Interrupt
    void T32_INT1_IRQHandler(void)
    {
        TIMER32_1->INTCLR = 0U;
        P1->OUT ^= BIT0; // - Toggle the heart beat indicator (1ms)
        g_SystemTicks++;
        return;
    }
}
