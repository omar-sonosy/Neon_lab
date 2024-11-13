CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -c -Wall -I./include
LDFLAGS=-mcpu=cortex-a9 -mfpu=neon -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,lscript.ld -Llib
LIBS=-Wl,--start-group,-lxil,-lgcc,-lc,--end-group


all: neon.elf

main.o: main.c
	$(CC) $(CFLAGS) -O3 -o main.o main.c
	
neon.o: neon.c
	$(CC) $(CFLAGS) -O3 -o neon.o neon.c
	
platform.o: platform.c
	$(CC) $(CFLAGS) -o platform.o platform.c

main.elf: main.o platform.o
	$(CC) $(LDFLAGS) -o main.elf main.o platform.o $(LIBS)

neon.elf: neon.o platform.o
	$(CC) $(LDFLAGS) -o neon.elf neon.o platform.o $(LIBS)
clean:
	rm *.o *.elf
