#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"


void edge(unsigned char arr[10][10], unsigned char arr2[10][10]){

	for (int i=1; i<9; i++){
		for (int j=1; j<9; j++){
			int G= abs(arr[i][j+1] - arr[i][j-1])+abs(arr[i+1][j]-arr[i-1][j]);
			if (G >= 100){
				arr2[i][j]= 1;
			}
			else{
				arr2[i][j]= 0;
			
			}
			
		}
	}
}


int main()
{
	XTime start;
	XTime end;
	init_platform();
	
	
	unsigned char x[10][10]= {{ }};
	unsigned char y[10][10]= {0};
	
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i < 5) {  // Upper half
                x[i][j] = 100;
            } else {  // Lower half
                x[i][j] = 0;
            }
        }
    }
    
	XTime_GetTime(&start);
	edge(x,y);
	XTime_GetTime(&end);
	
	for (int i=0; i<10; i++){
		for(int j=0; j<10;j++){
			printf("%d  ",y[i][j]);
		}
		printf("\n\r");
	}
	
	
	XTime time_diff= end-start;
	float time_ms= (time_diff*2.0)*1000000/XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ;
	printf("%f micro_s\n\r",time_ms);
	
    cleanup_platform();
    return 0;
}
