#!/bin/bash

arm-none-eabi-gdb main.elf -iex "target remote localhost:3333" -iex "reset halt" -iex "reset init" -iex "load main.elf"
