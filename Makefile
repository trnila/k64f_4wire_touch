# This file was automagically generated by mbed.org. For more information, 
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

###############################################################################
# Boiler-plate

# cross-platform directory manipulation
ifeq ($(shell echo $$OS),$$OS)
    MAKEDIR = if not exist "$(1)" mkdir "$(1)"
    RM = rmdir /S /Q "$(1)"
else
    MAKEDIR = '$(SHELL)' -c "mkdir -p \"$(1)\""
    RM = '$(SHELL)' -c "rm -rf \"$(1)\""
endif

OBJDIR := BUILD
# Move to the build directory
ifeq (,$(filter $(OBJDIR),$(notdir $(CURDIR))))
.SUFFIXES:
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKETARGET = '$(MAKE)' --no-print-directory -C $(OBJDIR) -f '$(mkfile_path)' \
		'SRCDIR=$(CURDIR)' $(MAKECMDGOALS)
.PHONY: $(OBJDIR) clean
all:
	+@$(call MAKEDIR,$(OBJDIR))
	+@$(MAKETARGET)
$(OBJDIR): all
Makefile : ;
% :: $(OBJDIR) ; :
clean :
	$(call RM,$(OBJDIR))

else

# trick rules into thinking we are in the root, when we are in the bulid dir
VPATH = ..

# Boiler-plate
###############################################################################
# Project settings

PROJECT := touch


# Project settings
###############################################################################
# Objects and Paths

OBJECTS += ./FXOS8700Q/FXOS8700Q.o
OBJECTS += ./main.o

 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/PeripheralPins.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/analogin_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/analogout_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/crc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/dma_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/flash_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_adc16.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_clock.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_clock_config.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_cmp.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_cmt.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_common.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_crc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dac.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dmamux.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dspi.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_dspi_edma.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_edma.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_enet.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_ewm.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flash.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flexbus.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_flexcan.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_ftm.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_gpio.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_i2c.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_i2c_edma.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_llwu.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_lptmr.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_mpu.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pdb.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_phy.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pit.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_pmc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rcm.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rnga.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_rtc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sai.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sai_edma.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sdhc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_sim.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_smc.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_uart.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_uart_edma.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_vref.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/fsl_wdog.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/gpio_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/gpio_irq_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/i2c_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/lp_ticker.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_board.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_overrides.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_retarget.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/mbed_sdk_boot.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/pinmap.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/port_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/pwmout_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/rtc_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/serial_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/sleep.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/spi_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/startup_MK64F12.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/storage_driver.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/system_MK64F12.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/trng_api.o
 SYS_OBJECTS += ./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/us_ticker.o

INCLUDE_PATHS += -I../
INCLUDE_PATHS += -I../.
INCLUDE_PATHS += -I.././FXOS8700Q
INCLUDE_PATHS += -I.././FXOS8700Q/MotionSensor
INCLUDE_PATHS += -I.././mbed
INCLUDE_PATHS += -I.././mbed/TARGET_K64F
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api
INCLUDE_PATHS += -I.././mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM
INCLUDE_PATHS += -I.././mbed/drivers
INCLUDE_PATHS += -I.././mbed/hal
INCLUDE_PATHS += -I.././mbed/platform
INCLUDE_PATHS += -I.././mnt

LIBRARY_PATHS := -L.././mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM 
LIBRARIES := -lmbed 
LINKER_SCRIPT ?= .././mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld

# Objects and Paths
###############################################################################
# Tools and Flags

AS      = 'arm-none-eabi-gcc' '-x' 'assembler-with-cpp' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O0' '-g3' '-DMBED_DEBUG' '-DMBED_TRAP_ERRORS_ENABLED=1' '-mcpu=cortex-m4' '-mthumb' '-mfpu=fpv4-sp-d16' '-mfloat-abi=softfp'
CC      = 'arm-none-eabi-gcc' '-std=gnu99' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O0' '-g3' '-DMBED_DEBUG' '-DMBED_TRAP_ERRORS_ENABLED=1' '-mcpu=cortex-m4' '-mthumb' '-mfpu=fpv4-sp-d16' '-mfloat-abi=softfp'
CPP     = 'arm-none-eabi-g++' '-std=gnu++98' '-fno-rtti' '-Wvla' '-c' '-Wall' '-Wextra' '-Wno-unused-parameter' '-Wno-missing-field-initializers' '-fmessage-length=0' '-fno-exceptions' '-fno-builtin' '-ffunction-sections' '-fdata-sections' '-funsigned-char' '-MMD' '-fno-delete-null-pointer-checks' '-fomit-frame-pointer' '-O0' '-g3' '-DMBED_DEBUG' '-DMBED_TRAP_ERRORS_ENABLED=1' '-mcpu=cortex-m4' '-mthumb' '-mfpu=fpv4-sp-d16' '-mfloat-abi=softfp'
LD      = 'arm-none-eabi-gcc'
ELF2BIN = 'arm-none-eabi-objcopy'
PREPROC = 'arm-none-eabi-cpp' '-E' '-P' '-Wl,--gc-sections' '-Wl,--wrap,main' '-Wl,--wrap,_malloc_r' '-Wl,--wrap,_free_r' '-Wl,--wrap,_realloc_r' '-Wl,--wrap,_memalign_r' '-Wl,--wrap,_calloc_r' '-Wl,--wrap,exit' '-Wl,--wrap,atexit' '-Wl,-n' '-mcpu=cortex-m4' '-mthumb' '-mfpu=fpv4-sp-d16' '-mfloat-abi=softfp'


C_FLAGS += -std=gnu99
C_FLAGS += -DMBED_BUILD_TIMESTAMP=1517215826.29
C_FLAGS += -DTARGET_KSDK2_MCUS
C_FLAGS += -DFEATURE_LWIP=1
C_FLAGS += -D__MBED__=1
C_FLAGS += -DDEVICE_I2CSLAVE=1
C_FLAGS += -D__FPU_PRESENT=1
C_FLAGS += -DTARGET_Freescale
C_FLAGS += -DDEVICE_PORTINOUT=1
C_FLAGS += -DTARGET_RTOS_M4_M7
C_FLAGS += -DDEVICE_LOWPOWERTIMER=1
C_FLAGS += -DDEVICE_RTC=1
C_FLAGS += -DTOOLCHAIN_object
C_FLAGS += -DDEVICE_SERIAL_ASYNCH=1
C_FLAGS += -D__CMSIS_RTOS
C_FLAGS += -DFSL_RTOS_MBED
C_FLAGS += -DDEVICE_STORAGE=1
C_FLAGS += -DTARGET_KPSDK_MCUS
C_FLAGS += -DTOOLCHAIN_GCC
C_FLAGS += -DARM_MATH_CM4
C_FLAGS += -DTARGET_DEBUG
C_FLAGS += -DTARGET_LIKE_CORTEX_M4
C_FLAGS += -DDEVICE_ANALOGOUT=1
C_FLAGS += -DTARGET_M4
C_FLAGS += -DTARGET_UVISOR_UNSUPPORTED
C_FLAGS += -DTARGET_K64F
C_FLAGS += -DDEVICE_SPI_ASYNCH=1
C_FLAGS += -DDEVICE_PWMOUT=1
C_FLAGS += -DDEVICE_INTERRUPTIN=1
C_FLAGS += -DTARGET_CORTEX
C_FLAGS += -DDEVICE_I2C=1
C_FLAGS += -DDEVICE_PORTOUT=1
C_FLAGS += -D__CORTEX_M4
C_FLAGS += -DDEVICE_STDIO_MESSAGES=1
C_FLAGS += -DCPU_MK64FN1M0VMD12
C_FLAGS += -DTARGET_LIKE_MBED
C_FLAGS += -DTARGET_FF_ARDUINO
C_FLAGS += -DTARGET_KPSDK_CODE
C_FLAGS += -DDEVICE_SERIAL_FC=1
C_FLAGS += -DFEATURE_STORAGE=1
C_FLAGS += -DDEVICE_TRNG=1
C_FLAGS += -D__MBED_CMSIS_RTOS_CM
C_FLAGS += -DDEVICE_SLEEP=1
C_FLAGS += -DTOOLCHAIN_GCC_ARM
C_FLAGS += -DTARGET_FRDM
C_FLAGS += -DTARGET_MCUXpresso_MCUS
C_FLAGS += -DDEVICE_SPI=1
C_FLAGS += -DDEVICE_SPISLAVE=1
C_FLAGS += -DDEVICE_ANALOGIN=1
C_FLAGS += -DDEVICE_SERIAL=1
C_FLAGS += -DDEVICE_FLASH=1
C_FLAGS += -DDEVICE_PORTIN=1
C_FLAGS += -DTARGET_MCU_K64F
C_FLAGS += -DTARGET_CORTEX_M
C_FLAGS += -include
C_FLAGS += mbed_config.h

CXX_FLAGS += -std=gnu++98
CXX_FLAGS += -fno-rtti
CXX_FLAGS += -Wvla
CXX_FLAGS += -DMBED_BUILD_TIMESTAMP=1517215826.29
CXX_FLAGS += -DTARGET_KSDK2_MCUS
CXX_FLAGS += -DFEATURE_LWIP=1
CXX_FLAGS += -D__MBED__=1
CXX_FLAGS += -DDEVICE_I2CSLAVE=1
CXX_FLAGS += -D__FPU_PRESENT=1
CXX_FLAGS += -DTARGET_Freescale
CXX_FLAGS += -DDEVICE_PORTINOUT=1
CXX_FLAGS += -DTARGET_RTOS_M4_M7
CXX_FLAGS += -DDEVICE_LOWPOWERTIMER=1
CXX_FLAGS += -DDEVICE_RTC=1
CXX_FLAGS += -DTOOLCHAIN_object
CXX_FLAGS += -DDEVICE_SERIAL_ASYNCH=1
CXX_FLAGS += -D__CMSIS_RTOS
CXX_FLAGS += -DFSL_RTOS_MBED
CXX_FLAGS += -DDEVICE_STORAGE=1
CXX_FLAGS += -DTARGET_KPSDK_MCUS
CXX_FLAGS += -DTOOLCHAIN_GCC
CXX_FLAGS += -DARM_MATH_CM4
CXX_FLAGS += -DTARGET_DEBUG
CXX_FLAGS += -DTARGET_LIKE_CORTEX_M4
CXX_FLAGS += -DDEVICE_ANALOGOUT=1
CXX_FLAGS += -DTARGET_M4
CXX_FLAGS += -DTARGET_UVISOR_UNSUPPORTED
CXX_FLAGS += -DTARGET_K64F
CXX_FLAGS += -DDEVICE_SPI_ASYNCH=1
CXX_FLAGS += -DDEVICE_PWMOUT=1
CXX_FLAGS += -DDEVICE_INTERRUPTIN=1
CXX_FLAGS += -DTARGET_CORTEX
CXX_FLAGS += -DDEVICE_I2C=1
CXX_FLAGS += -DDEVICE_PORTOUT=1
CXX_FLAGS += -D__CORTEX_M4
CXX_FLAGS += -DDEVICE_STDIO_MESSAGES=1
CXX_FLAGS += -DCPU_MK64FN1M0VMD12
CXX_FLAGS += -DTARGET_LIKE_MBED
CXX_FLAGS += -DTARGET_FF_ARDUINO
CXX_FLAGS += -DTARGET_KPSDK_CODE
CXX_FLAGS += -DDEVICE_SERIAL_FC=1
CXX_FLAGS += -DFEATURE_STORAGE=1
CXX_FLAGS += -DDEVICE_TRNG=1
CXX_FLAGS += -D__MBED_CMSIS_RTOS_CM
CXX_FLAGS += -DDEVICE_SLEEP=1
CXX_FLAGS += -DTOOLCHAIN_GCC_ARM
CXX_FLAGS += -DTARGET_FRDM
CXX_FLAGS += -DTARGET_MCUXpresso_MCUS
CXX_FLAGS += -DDEVICE_SPI=1
CXX_FLAGS += -DDEVICE_SPISLAVE=1
CXX_FLAGS += -DDEVICE_ANALOGIN=1
CXX_FLAGS += -DDEVICE_SERIAL=1
CXX_FLAGS += -DDEVICE_FLASH=1
CXX_FLAGS += -DDEVICE_PORTIN=1
CXX_FLAGS += -DTARGET_MCU_K64F
CXX_FLAGS += -DTARGET_CORTEX_M
CXX_FLAGS += -include
CXX_FLAGS += mbed_config.h

ASM_FLAGS += -x
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -D__CORTEX_M4
ASM_FLAGS += -DCPU_MK64FN1M0VMD12
ASM_FLAGS += -DARM_MATH_CM4
ASM_FLAGS += -D__FPU_PRESENT=1
ASM_FLAGS += -D__MBED_CMSIS_RTOS_CM
ASM_FLAGS += -D__CMSIS_RTOS
ASM_FLAGS += -DFSL_RTOS_MBED
ASM_FLAGS += -I.
ASM_FLAGS += -I./mbed
ASM_FLAGS += -I./mbed/TARGET_K64F
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/TARGET_FRDM
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/device
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/TARGET_MCU_K64F/drivers
ASM_FLAGS += -I./mbed/TARGET_K64F/TARGET_Freescale/TARGET_MCUXpresso_MCUS/api
ASM_FLAGS += -I./mbed/TARGET_K64F/TOOLCHAIN_GCC_ARM
ASM_FLAGS += -I./mbed/drivers
ASM_FLAGS += -I./mbed/hal
ASM_FLAGS += -I./mbed/platform
ASM_FLAGS += -I./mnt
ASM_FLAGS += -I./FXOS8700Q
ASM_FLAGS += -I./FXOS8700Q/MotionSensor


LD_FLAGS :=-Wl,--gc-sections -Wl,--wrap,main -Wl,--wrap,_malloc_r -Wl,--wrap,_free_r -Wl,--wrap,_realloc_r -Wl,--wrap,_memalign_r -Wl,--wrap,_calloc_r -Wl,--wrap,exit -Wl,--wrap,atexit -Wl,-n -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp 
LD_SYS_LIBS :=-Wl,--start-group -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -lmbed -Wl,--end-group

# Tools and Flags
###############################################################################
# Rules

.PHONY: all lst size


all: $(PROJECT).bin $(PROJECT).hex size


.s.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  


.S.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Assemble: $(notdir $<)"
  
	@$(AS) -c $(ASM_FLAGS) -o $@ $<
  

.c.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CC) $(C_FLAGS) $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	+@$(call MAKEDIR,$(dir $@))
	+@echo "Compile: $(notdir $<)"
	@$(CPP) $(CXX_FLAGS) $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).link_script.ld: $(LINKER_SCRIPT)
	@$(PREPROC) $< -o $@



$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) $(PROJECT).link_script.ld 
	+@echo "link: $(notdir $@)"
	@$(LD) $(LD_FLAGS) -T $(filter-out %.o, $^) $(LIBRARY_PATHS) --output $@ $(filter %.o, $^) $(LIBRARIES) $(LD_SYS_LIBS)


$(PROJECT).bin: $(PROJECT).elf
	$(ELF2BIN) -O binary $< $@
	+@echo "===== bin file ready to flash: $(OBJDIR)/$@ =====" 

$(PROJECT).hex: $(PROJECT).elf
	$(ELF2BIN) -O ihex $< $@


# Rules
###############################################################################
# Dependencies

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
endif

# Dependencies
###############################################################################
