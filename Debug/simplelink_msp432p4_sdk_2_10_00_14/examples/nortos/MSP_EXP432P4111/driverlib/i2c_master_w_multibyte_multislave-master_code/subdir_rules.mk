################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/i2c_master_w_multibyte_multislave-master_code.obj: ../simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/i2c_master_w_multibyte_multislave-master_code.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/ti/ccsv7/ccs_base/arm/include" --include_path="/home/david/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="../../../../ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/i2c_master_w_multibyte_multislave-master_code.d_raw" --obj_directory="simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/system_msp432p4111.obj: ../simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/system_msp432p4111.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/ti/ccsv7/ccs_base/arm/include" --include_path="/home/david/ti/ccsv7/ccs_base/arm/include/CMSIS" --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="../../../../ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code/system_msp432p4111.d_raw" --obj_directory="simplelink_msp432p4_sdk_2_10_00_14/examples/nortos/MSP_EXP432P4111/driverlib/i2c_master_w_multibyte_multislave-master_code" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

