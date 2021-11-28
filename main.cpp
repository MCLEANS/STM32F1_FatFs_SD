#include "sdcard.h"
#include "stm32f10x.h"
#include "USART.h"
#include "stdlib.h"
#include "spi.h"

custom_libraries::USART debug(USART1,GPIOA,10,9,9600);


int main(void)
{	
	debug.initialize();
	InitSdcard();
 
    char data[] = "Hello \r\n";
    char file_name[] = "test.txt";
    FIL fil;
	volatile FRESULT fr;
	debug.println("Initializing");

 
	_mountSdcard();

	_openfile(file_name , WRITE_FILE , &fil);

	fr = f_lseek(&fil , f_size(&fil));
	char val[3];
	itoa(fr,val,10);
	debug.print("CODE : ");
	debug.println(val);
	if(fr != FR_OK){
		if(fr == FR_NOT_READY){
			debug.println("NOT READY");
		}
		else{
			debug.println("ERROR");
		}
    }
	else{
		debug.println("OK");
	}

	_writeString(data , &fil);

	_closefile(&fil);
	_unmountSdcard();
	

	

	while(1){
			SpiCsLow();
			SpiSendData('U');
	}
}