KERN_DIR = /home/myl/Workspace/kernel-src/linux-2.6.32.62

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= myleds.o
