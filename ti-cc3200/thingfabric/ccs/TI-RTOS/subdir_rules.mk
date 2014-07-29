################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bma222drv.obj: C:/thingfabric/bma222drv.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="bma222drv.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

device_status.obj: C:/thingfabric/device_status.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="device_status.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio_if.obj: C:/ti/CC3200SDK/cc3200-sdk/example/common/gpio_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="gpio_if.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c_if.obj: C:/ti/CC3200SDK/cc3200-sdk/example/common/i2c_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="i2c_if.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: C:/thingfabric/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mqtt.obj: C:/thingfabric/mqtt.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="mqtt.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: C:/thingfabric/pinmux.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="pinmux.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

smartconfig.obj: C:/thingfabric/smartconfig.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="smartconfig.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tmp006drv.obj: C:/thingfabric/tmp006drv.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tmp006drv.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: C:/ti/CC3200SDK/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --include_path="C:/thingfabric/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK/cc3200-sdk/inc" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Include/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/simplelink/Source/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/driverlib/" --include_path="C:/ti/CC3200SDK/cc3200-sdk/oslib/" -g --define=ccs --define=SL_PLATFORM_MULTI_THREADED --define=USE_TIRTOS --define=CC3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uart_if.pp" --cmd_file="C:/ti/CC3200SDK/cc3200-sdk/ti_rtos/ti_rtos_config/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


