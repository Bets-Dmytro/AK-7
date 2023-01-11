# normal makefile
KDIR ?= $$HOME/repos/linux-stable
ccflags-y += -g

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	$(CROSS_COMPILE)strip -g hello.ko
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
