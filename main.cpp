#include "sdcard.h"
#include "stm32f10x.h"

int main(void)
{
		InitSdcard();
    char data[] = "Hello \r\n";
    char file_name[] = "test.txt";
    FIL fil;
		FRESULT fr;

		_mountSdcard();
		_openfile(file_name , WRITE_FILE , &fil);

		fr = f_lseek(&fil , f_size(&fil));
		if(fr != FR_OK){
      
    }


		_writeString(data , &fil);

		_closefile(&fil);
		_unmountSdcard();
		while(1){

    }
}