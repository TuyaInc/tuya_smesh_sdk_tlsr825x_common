############################################################
# 全局变量
############################################################
PROJECT_ROOT := ../../..

INCS := -I$(PROJECT_ROOT)/includes/components \
	-I$(PROJECT_ROOT)/includes/board \
	-I$(PROJECT_ROOT)/includes/board/bal \
	-I$(PROJECT_ROOT)/includes/board/hal \
	-I$(PROJECT_ROOT)/includes/board/chip/telink_sig_mesh_sdk/sdk/vendor/common \
	-I$(PROJECT_ROOT)/includes/board/chip/telink_sig_mesh_sdk/sdk/drivers/8258 \
	-I$(PROJECT_ROOT)/includes/board/chip/telink_sig_mesh_sdk/sdk \
	-I../_build

OBJS := 
C_SRCS :=


BIN = .
LIBS := -ltuya_ble_os



CC = tc32-elf-gcc
CFLAGS = -ffunction-sections -fdata-sections -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions
CMACROS = -DCHIP_TYPE=CHIP_TYPE_8258 -D__TUYA_PROJECT__=1 -DTLSR825X_SYS

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
8258_mesh.lst \

FLASH_IMAGE += \
8258_mesh.bin \

SIZEDUMMY += \
sizedummy \


-include app/subdir.mk


############################################################
# makefile 依赖 
############################################################
# Main-build Target
main-build: ble_lt_mesh.elf secondary-outputs

# Tool invocations
ble_lt_mesh.elf: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"$(PROJECT_ROOT)/libs" -T boot.link -o"ble_lt_mesh.elf" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

8258_mesh.lst: ble_lt_mesh.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S ble_lt_mesh.elf  >"8258_mesh.lst"
	@echo 'Finished building: $@'
	@echo ' '

8258_mesh.bin: ble_lt_mesh.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary ble_lt_mesh.elf  "8258_mesh.bin"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ble_lt_mesh.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t ble_lt_mesh.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE) $(ELFS) $(OBJS) $(LST) $(SIZEDUMMY) ble_lt_mesh.elf
	-@echo ' '

pre-build:
	-"./getver.sh"
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)
