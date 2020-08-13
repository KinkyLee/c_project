
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc16.h"

#define BUFF_SIZE 256


#define FILENAME1 "./chkdat1.bin"
#define FILENAME2 "./chkdat2.bin"

int file_crc16_chk(char *filename, unsigned short *crc16val)
{
    FILE *fp;
    char buff[BUFF_SIZE];
    unsigned short val = 0;
    int ix, ret;
    
    fp = fopen(filename, "rb");
    if(NULL == fp)
        return -1;

    do
    {
        ret = fread(buff, 1, BUFF_SIZE, fp);
        if(ret > 0)
            val = crc16(val, buff, ret);
    } while(ret > 0);
    
    fclose(fp);
    
    *crc16val = val;

    return 0;
}

int main()
{
    char buff[BUFF_SIZE];
    int ix, ret;
    unsigned short crc16val = 0;
    
    for(ix=0; ix<BUFF_SIZE; ix++)
        buff[ix] = 255-ix;

    crc16val = crc16(0, buff, BUFF_SIZE);
    printf("一次计算CRC16值: 0x%X\n", crc16val);
    
    crc16val = crc16(0, buff, 128);
    printf("多次计算CRC16值: 0x%X\n", crc16val);
    crc16val = crc16(crc16val, &buff[128], 128);
    printf("多次计算CRC16值: 0x%X\n", crc16val);
    
    
    ret = file_crc16_chk(FILENAME1, &crc16val);
    if(0 == ret)
        printf("file [%s] crc16: 0x%04X\n", FILENAME1, crc16val);
    else
        printf("file [%s] crc16 chk err: %d\n", FILENAME1, ret);
        
    
    ret = file_crc16_chk(FILENAME2, &crc16val);
    if(0 == ret)
        printf("file [%s] crc16: 0x%04X\n", FILENAME2, crc16val);
    else
        printf("file [%s] crc16 chk err: %d\n", FILENAME2, ret);

    return 0;
}






