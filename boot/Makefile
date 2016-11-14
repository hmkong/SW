

include ./config.mk

ASMS	 = src/reset.o
ASMS	+= src/cache.o
OBJS 	+= src/main.o
#OBJS 	+= src/ddr.o
#OBJS	+= src/uart.o
#OBJS  += src/dma.o
#OBJS  += src/util.o
#OBJS	+= src/isr.o
#OBJS	+= src/cpu.o
#OBJS	+= src/gpio.o
LIBS	+= -Llib -lEXL

all: clean boot

clean:
	@rm -rf src/*.o
	@rm -rf obj/*.o
	@rm -rf output/*.a

boot: $(OBJS) $(ASMS)
	@$(LD) -r -o obj/boot.o $(OBJS) $(ASMS) $(LIBS)
	@$(LD) -T ./mem.ld obj/boot.o -o output/boot.or32
	@$(OBJCOPY) -O binary output/boot.or32 output/boot.bin
	@$(OBJDUMP) -DSx output/boot.or32 > output/boot.dis
	@$(OBJDUMP) -d output/boot.or32 > output/verify.dis
	@rm -rf src/*.o
