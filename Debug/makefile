################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2

ORDERED_OBJS += \
"./compute.obj" \
"./essential.obj" \
"./main.obj" \
"./msp432_startup_ccs.obj" \
"./Peripherals/adc.obj" \
"./Peripherals/clock.obj" \
"./Peripherals/gpio.obj" \
"./Peripherals/i2c.obj" \
"./Peripherals/timer.obj" \
"./Peripherals/uart.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Peripherals/subdir_vars.mk
-include subdir_rules.mk
-include Peripherals/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
UltrasonicSensor.out \

EXE_OUTPUTS__QUOTED += \
"UltrasonicSensor.out" \

BIN_OUTPUTS += \
UltrasonicSensor.hex \

BIN_OUTPUTS__QUOTED += \
"UltrasonicSensor.hex" \


# All Target
all: UltrasonicSensor.out

# Tool invocations
UltrasonicSensor.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP432 Linker'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --advice:power=all -g --gcc --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs --display_error_number --diag_warning=225 --diag_wrap=off -z -m"UltrasonicSensor.map" --heap_size=55000 --stack_size=4096 -i"/home/prachetverma/ti/ccsv6/ccs_base/arm/include" -i"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/lib" -i"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="UltrasonicSensor_linkInfo.xml" --rom_model -o "UltrasonicSensor.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

UltrasonicSensor.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP432 Hex Utility'
	"/home/prachetverma/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armhex"  -o "UltrasonicSensor.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "compute.pp" "essential.pp" "main.pp" "msp432_startup_ccs.pp" "Peripherals/adc.pp" "Peripherals/clock.pp" "Peripherals/gpio.pp" "Peripherals/i2c.pp" "Peripherals/timer.pp" "Peripherals/uart.pp" 
	-$(RM) "compute.obj" "essential.obj" "main.obj" "msp432_startup_ccs.obj" "Peripherals/adc.obj" "Peripherals/clock.obj" "Peripherals/gpio.obj" "Peripherals/i2c.obj" "Peripherals/timer.obj" "Peripherals/uart.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

