################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
ACCEL.obj: ../ACCEL.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ACCEL.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

LED.obj: ../LED.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="LED.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Mailbox.obj: ../Mailbox.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Mailbox.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Scheduler.obj: ../Scheduler.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Scheduler.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Task.obj: ../Task.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Task.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer32.obj: ../Timer32.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Timer32.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_msp432p401r_ccs.obj: ../startup_msp432p401r_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="startup_msp432p401r_ccs.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

system_msp432p401r.obj: ../system_msp432p401r.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/david/Documents/Universidad/Incrustados/Labo2/VirtualHorizon" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source" --include_path="/home/david/ti/simplelink_msp432p4_sdk_2_10_00_14/source/third_party/CMSIS/Include" --include_path="/home/david/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --advice:power=none --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="system_msp432p401r.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


