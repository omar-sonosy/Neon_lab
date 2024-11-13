#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"
#include <arm_neon.h>

void mat_product_ni(float A[4][4], float B[4][4], float C[4][4])
{	
	float32x4_t V_A[4],V_B[4],result_temp[6];
	float32x4x4_t V_B_4,V_A_4,result;
	
	V_A_4=vld4q_f32(&A[0][0]);
	V_A[0]=V_A_4.val[0];
	V_A[1]=V_A_4.val[1];
	V_A[2]=V_A_4.val[2];
	V_A[3]=V_A_4.val[3];
	V_B_4=vld4q_f32(&B[0][0]);
	V_B[0]=V_B_4.val[0];
	V_B[1]=V_B_4.val[1];
	V_B[2]=V_B_4.val[2];
	V_B[3]=V_B_4.val[3];
	//float temp[4];
	
	
	for(int i=0;i<4;i++){
		//for(int j=0;j<4;j++){
			result_temp[0]=vmulq_n_f32(V_A[0],vgetq_lane_f32(V_B[i],0));
			result_temp[1]=vmulq_n_f32(V_A[1],vgetq_lane_f32(V_B[i],1));
			result_temp[2]=vmulq_n_f32(V_A[2],vgetq_lane_f32(V_B[i],2));
			result_temp[3]=vmulq_n_f32(V_A[3],vgetq_lane_f32(V_B[i],3));
		//}
		result_temp[4]=vaddq_f32(result_temp[0],result_temp[1]);
		result_temp[5]=vaddq_f32(result_temp[2],result_temp[3]);
		result.val[i]=vaddq_f32(result_temp[4],result_temp[5]);
		
	}
	vst4q_f32(&C[0][0],result);

	
	
}
int main()
{
	XTime start;
	XTime end;
	
	float A[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	float B[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
	float C[4][4];
    init_platform();
	XTime_GetTime(&start);
	mat_product_ni(A,B,C);
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
