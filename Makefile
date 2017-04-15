######################################################################
#  Project Makefile
######################################################################

BINARY		= main
#SRCFILES	= main.c i2c.c user.c stepper.c rtos/heap_4.c rtos/list.c rtos/port.c rtos/queue.c rtos/tasks.c rtos/opencm3.c
SRCFILES	= main.c user.c stepper.c rtos/heap_4.c rtos/list.c rtos/port.c rtos/queue.c rtos/tasks.c rtos/opencm3.c
LDSCRIPT	= stm32f103c8t6.ld

# Any additional dependencies for your build
# DEPS		= tb32.h
# CLOBBER	+= 	# Any additional files to be removed with "make clobber"

MYOPT	= -DDEBUG

include ../../Makefile.incl
include ../Makefile.rtos


######################################################################
#  NOTES:
#	1. remove any modules you don't need from SRCFILES
#	2. "make clean" will remove *.o etc., but leaves *.elf, *.bin
#	3. "make clobber" will "clean" and remove *.elf, *.bin etc.
#	4. "make flash" will perform:
#	   st-flash write main.bin 0x8000000
######################################################################
