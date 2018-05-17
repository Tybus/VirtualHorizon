#include "ACCELL.hpp"
//  X = P6.1 A14, Y = P4.0 A13 Z = P4.2 A11
ACCELL::ACCELL(){
	m_fTaskTimems = 0.1;
	m_pMailbox = Mailbox::getMailbox();
}

uint8_t ACCELL::run(){

    st_Message l_MreadValues;
    m_axyzValues[0] = (int16_t) ADC14_getResult(ADC_MEM0); //better get this for sure.
    m_axyzValues[1] = (int16_t) ADC14_getResult(ADC_MEM1);
    m_axyzValues[2] = (int16_t) ADC14_getResult(ADC_MEM2);
    l_MreadValues.bMessageValid = true;
    l_MreadValues.u8DestinationID = ANGLE_MB_ID;
    l_MreadValues.u8SourceID = ACCELL_MB_ID;
    l_MreadValues.u8MessageCode = ACCELL_ADC_RESULT_CODE;
    l_MreadValues.u32MessageData = 3;//6 8 bit values to read.
    l_MreadValues.pPayload = (uint32_t * ) this->m_axyzValues;

    m_pMailbox->sendMessage(l_MreadValues);

    //l_MreadValues = m_pMailbox->getMessage(ANGLE_MB_ID); mailbox is not working

    return NO_ERR;

}

uint8_t ACCELL::setup(){

    /* Configures Pin 4.0, 4.2, and 6.1 as ADC input */
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

     /* Initializing ADC (ADCOSC/64/8) */
     MAP_ADC14_enableModule();
     ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);
     ADC14_setResultFormat(ADC_SIGNED_BINARY);
     ADC14_setResolution(ADC_14BIT);

     /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM2 (A11, A13, A14)  with no repeat)
          * with internal 2.5v reference */
     MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);
     MAP_ADC14_configureConversionMemory(ADC_MEM0,
             ADC_VREFPOS_AVCC_VREFNEG_VSS,
             ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

     MAP_ADC14_configureConversionMemory(ADC_MEM1,
             ADC_VREFPOS_AVCC_VREFNEG_VSS,
             ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

     MAP_ADC14_configureConversionMemory(ADC_MEM2,
             ADC_VREFPOS_AVCC_VREFNEG_VSS,
             ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);


     /* Setting up the sample timer to automatically step through the sequence
      * convert.
      */
     MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

     /* Triggering the start of the sample */
     MAP_ADC14_enableConversion();
     MAP_ADC14_toggleConversionTrigger();
    return(NO_ERR);

}
