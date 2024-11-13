#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"


void mat_product_c(float A[4][4], float B[4][4], float C[4][4])
{	
	for (int i=0; i<4; i++){
		for(int j=0; j<4;j++){
			C[i][j]= 0;
			for(int k=0;k<4;k++){
				
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}
int main()
{
	XTime start;
	XTime end;
	
	float A[4][4]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	float B[4][4]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	float C[4][4];
    init_platform();
	XTime_GetTime(&start);
	mat_product_c(A,B,C);
	XTime_GetTime(&end);
	for (int i=0; i<4; i++){
		for(int j=0; j<4;j++){
			printf("%f  ",C[i][j]);
		}
		printf("\n\r");
	}
	XTime time_diff= end-start;
	float time_ms= (time_diff*2.0)*1000000/XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ;
	printf("%f micro_s\n\r",time_ms);
	
    cleanup_platform();
    return 0;
}
