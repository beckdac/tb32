#!/bin/bash

arm-none-eabi-gdb main.elf -iex "target remote localhost:3333" -iex "monitor reset halt" -iex "monitor reset init" -iex "load main.elf"
