#include <ti/devices/msp432p4xx/inc/msp.h>
#include "main.hpp"
#include "Scheduler.hpp"
#include "Task.hpp"
#include "LED.hpp"
#include <Timer32.h>
#include "ACCELL.hpp"
#include "ANGLE.h"
#include "POSITION.h"
//#include "ACCELL.hpp"


volatile static uint64_t g_SystemTicks = 0; // - The system counter.
Mailbox* g_Mailbox = Mailbox::getMailbox();
Scheduler g_MainScheduler; // - Instantiate a Scheduler

// #########################
//          MAIN
// #########################
void main(void){


    // - Instantiate two new Tasks
    ACCELL Accelerometer = ACCELL();
    ANGLE Angle = ANGLE();
    POSITION Position = POSITION();
    LED BlueLED(BIT2);
    LED GreenLED(BIT1);
    //ACCELL Accelerometer = ACCELL();
    // - Run the overall setup function for the system
    Setup(g_MainScheduler.getSchedulerTick());//Start with 1ms Tick
    // - Attach the Tasks to the Scheduler;
    Angle.setup();
    Accelerometer.setup();
    Position.setup();
    while(1){
        //Angle.run();
        //Accelerometer.run();
        Position.run();
    }
    //g_MainScheduler.attach(&BlueLED,TaskType_Periodic, TaskActiveTrue,500);
    g_MainScheduler.attach(&GreenLED, TaskType_Periodic,TaskActiveTrue, 600);
    g_MainScheduler.attach(&Accelerometer, TaskType_Always, TaskActiveTrue,0);
    // - Run the Setup for the scheduler and all tasks

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
