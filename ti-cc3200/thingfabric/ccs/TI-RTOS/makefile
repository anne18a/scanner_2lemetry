################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/arm_5.1.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./uart_if.obj" \
"./tmp006drv.obj" \
"./smartconfig.obj" \
"./pinmux.obj" \
"./mqtt.obj" \
"./main.obj" \
"./i2c_if.obj" \
"./gpio_if.obj" \
"./device_status.obj" \
"./bma222drv.obj" \
"../cc3200v1p32.cmd" \
-l"libc.a" \
-ldriverlib.a \
-lsimplelink.a \
-lti_rtos.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
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
thingfabric.out \

EXE_OUTPUTS__QUOTED += \
"thingfabric.out" \

BIN_OUTPUTS += \
thingfabric.hex \

BIN_OUTPUTS__QUOTED += \
"thingfabric.hex" \


# All Target
all: thingfabric.out

dependents:
	-cd C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default && $(MAKE) clean all

# Tool invocations
thingfabric.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/linker.cmd
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off -z -m"thingfabric.map" --heap_size=0x2000 --stack_size=0x1000 -i"c:/ti/ccsv6/tools/compiler/arm_5.1.5/lib" -i"c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" -i"C:/ti/CC3200SDK/cc3200-sdk/driverlib/ccs/Release" -i"C:/ti/CC3200SDK/cc3200-sdk/simplelink/ccs/OS" -i"C:/ti/CC3200SDK/cc3200-sdk/oslib/ccs/ti_rtos" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="thingfabric_linkInfo.xml" --rom_model -l"C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/linker.cmd" -o "thingfabric.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

thingfabric.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armhex"  -o "thingfabric.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "bma222drv.pp" "device_status.pp" "gpio_if.pp" "i2c_if.pp" "main.pp" "mqtt.pp" "pinmux.pp" "smartconfig.pp" "tmp006drv.pp" "uart_if.pp" 
	-$(RM) "bma222drv.obj" "device_status.obj" "gpio_if.obj" "i2c_if.obj" "main.obj" "mqtt.obj" "pinmux.obj" "smartconfig.obj" "tmp006drv.obj" "uart_if.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'convert to bin files'
	-"c:/ti/ccsv6/utils/tiobj2bin/tiobj2bin" "thingfabric.out" "thingfabric.bin" "c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armofd" "c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armhex" "c:/ti/ccsv6/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/linker.cmd:

-include ../makefile.targets

