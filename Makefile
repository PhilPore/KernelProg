obj-m += hello1.o
obj-m += hello2.o
obj-m += hello3.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell name -r)/build M=$(PWD) clean

