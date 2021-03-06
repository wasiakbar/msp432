################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Peripherals/adc.obj: ../Peripherals/adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/adc.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Peripherals/clock.obj: ../Peripherals/clock.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/clock.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Peripherals/gpio.obj: ../Peripherals/gpio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/gpio.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Peripherals/i2c.obj: ../Peripherals/i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/i2c.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Peripherals/timer.obj: ../Peripherals/timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/timer.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

Peripherals/uart.obj: ../Peripherals/uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include" --include_path="/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="/home/prachetverma/ti/ccsv6/ccs_base/arm/include/CMSIS" --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="Peripherals/uart.pp" --obj_directory="Peripherals" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


