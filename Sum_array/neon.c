#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"
#include <arm_neon.h>

int sum_ni(int16_t* arr)
{	
	int16x8_t v1,vsum,vtemp;
	vsum= vdupq_n_s16(0);
	for(int i=0; i<2048 ; i=i+8){
		 v1=vld1q_s16(&arr[i]);
		 vsum = vaddq_s16(vsum, v1);
	
	}
	
	int sum=0;
	sum=vgetq_lane_s16(vsum,0);
	sum+=vgetq_lane_s16(vsum,1);
	sum+=vgetq_lane_s16(vsum,2);
	sum+=vgetq_lane_s16(vsum,3);
	sum+=vgetq_lane_s16(vsum,4);
	sum+=vgetq_lane_s16(vsum,5);
	sum+=vgetq_lane_s16(vsum,6);
	sum+=vgetq_lane_s16(vsum,7);
	return sum;
}
int main()
{
	XTime start;
	XTime end;
	
	//double total_time;
    init_platform();
	int16_t arr[2048];
	int sum;
	for(int i=0;i<2048;i++)
		arr[i]=(int16_t)1;
	
	XTime_GetTime(&start);
	sum= sum_ni(arr);
	XTime_GetTime(&end);
	printf("%llu \t %d\n\r",end-start, sum);
	
    cleanup_platform();
    return 0;
}
