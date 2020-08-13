


INC +=

SRC += crc_test.c
SRC += crc16.c

CFLAGS += 

TARGET = crctest


all:
	${CC} ${INC} ${SRC} ${CFLAGS} -o ${TARGET}
	


clean:
	rm -rf *.o *~ ${TARGET}



