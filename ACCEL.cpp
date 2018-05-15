#include "ACCELL.hpp"
//  X = P6.1 A14, Y = P4.0 A13 Z = P4.2 A11
ACCELL::ACCELL(){
	m_fTaskTimems = 0.1;
}

uint8_t ACCELL::run(){

    uint16_t l_u16xyzValues[3];
    st_Message l_MreadValues;
    ADC14_getMultiSequenceResult(&l_u16xyzValues);
    m_axyzValues = (uint32_t) l_u16xyzValues; //This might be wrong, checkout

    l_MreadValues.bMessageValid = true;
    l_MreadValues.u8DestinationID = ANGLE_MB_ID;
    l_MreadValues.u8SourceID = ACCELL_MB_ID;
    l_MreadValues.u8MessageCode = ACCELL_ADC_RESULT_CODE;
    l_MreadValues.u32MessageData = 3;//6 8 bit values to read.
    l_MreadValue.pPayload = this->m_axyzValues;
    printf("X: %d. /n",l_u6xyzValues[0]);
    printf("Y: %d. /n",l_u6xyzValues[1]);
    printf("Z: %d. /n",l_u6xyzValues[2]);
    return NO_ERR;

}

uint8_t ACCELL::setup(){

extern"C"{
    /* Configures Pin 4.0, 4.2, and 6.1 as ADC input */
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

     /* Initializing ADC (ADCOSC/64/8) */
     MAP_ADC14_enableModule();
     ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

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
}
    return(NO_ERR);'

}
