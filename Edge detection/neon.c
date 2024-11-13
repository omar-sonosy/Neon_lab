#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"
#include <arm_neon.h>



void edge_neon(unsigned char arr[10][10], unsigned char arr2[10][10]){
	uint8x8_t N,S,W,E;
	uint8x8_t reg_out;
	uint8x8_t sub1,sub2;
	
	uint8x8_t sum;
	uint8x8_t threshold;
	threshold=vdup_n_u8(100);
	
	for(int i=1;i<9;i++){
		N= vld1_u8(&arr[i-1][1]);
		S= vld1_u8(&arr[i+1][1]);
		W= vld1_u8(&arr[i][0]);
		E= vld1_u8(&arr[i][2]);	
		sub1=vabd_u8(N,S);
		sub2=vabd_u8(W,E);
		sum=vadd_u8(sub1,sub2);
		sum= vcge_u8(sum,threshold);
		vst1_u8(&arr2[i][1],sum);
		
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
	edge_neon(x,y);
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
