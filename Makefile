#############################
#  Make Target Description  #
#############################
export TOPDIR	= $(CURDIR)
export GCCDIR =	/opt/or32
export SRCDIR = $(TOPDIR)/boot/src


all: clean bootloader install

ex_lib: clean compile_lib

sim: export EXTRA_CFLAGS := -DSIM
sim: clean bootloader install

##-DSIM_MODE   
##############################
#  Clean Target Description  #
##############################
clean: clean_boot

clean_boot:
	@$(MAKE) clean -s -C boot

##############################
#  Make Description          #
##############################
compile_lib:
	@echo ""																	|& tee -a $(BUILDRPT)
	@echo "*******************************************************************"	|& tee -a $(BUILDRPT)
	@echo "Compile EXRISC Library..."									|& tee -a $(BUILDRPT)
	@$(MAKE) -s -C boot/lib_src												|& tee -a $(BUILDRPT)


bootloader:
	@echo "make bootloader..."
	@$(MAKE) -s -C boot


##############################
#  Make Output Binary File   #
##############################
install:
	@rm -rf output/*
	@echo "BOOT : `cat boot/output/boot.bin | wc -c` bytes"
