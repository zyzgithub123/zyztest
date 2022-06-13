# Makefile2.6
obj-m += helloDriver.o        # 产生hellomod 模块的目标文件
CURRENT_PATH := $(shell pwd)   #模块所在的当前路径
LINUX_KERNEL := $(shell uname -r)    #Linux内核源代码的当前版本
#x86_LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL) 				#Linux内核源代码的绝对路径  x86版本
x86_LINUX_KERNEL_PATH :=/lib/modules/5.17.9/source
 
CURRENT_PATH ?= $(shell pwd)
LINUX_KERNEL ?= $(shell uname -r)
x86_LINUX_KERNEL_PATH ?= /lib/modules/$(LINUX_KERNEL)/build

x86:helloApp_x86
	make -C $(x86_LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	
clean:
#清理
	-make -C $(x86_LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
	-rm helloApp_arm

helloApp_x86:helloApp.c
