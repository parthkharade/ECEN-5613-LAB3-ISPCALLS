MEMORYMODEL = --model-large
INC_DIR=./Inc
CFLAGS = -c -mmcs51 --std-sdcc99 -D HEAP_SIZE=5000 $(MEMORYMODEL) -I $(INC_DIR)
LFLAGS = --code-loc 0x3B40 --code-size 0x3FFF --xram-loc 0x0000 --xram-size 0x8000 \
	      --out-fmt-ihx $(MEMORYMODEL)

VPATH  = Src:Include:Debug

all:./Output/main.hex

./Debug/main.rel:main.c  
	sdcc $(CFLAGS) $^ -o $@

./Debug/serial.rel:serial.c  
	sdcc $(CFLAGS) $^ -o $@

./Debug/_heap.rel:_heap.c  
	sdcc $(CFLAGS) $^ -o $@

./Debug/debug.rel:debug.c  
	sdcc $(CFLAGS) $^ -o $@
		
./Debug/main.ihx:main.rel serial.rel _heap.rel debug.rel
	sdcc $(LFLAGS) $^ -o $@

./Output/main.hex:main.ihx
	packihx ./Debug/main.ihx > ./Output/main.hex

.PHONY:clean

clean:
	-rm -rf Debug/*
	-rm -rf Output/*
