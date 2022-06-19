#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define sboxCnt_dizy80 24
#define sboxCnt_dizy128 32
#define ROUNDS 15


typedef unsigned char u8;
typedef unsigned int u32;


void dizy80_ksg(u8* key, u8* round_consts, u8* IV){
	/*
	* IV and round consts xored before the s box
	* round consts are output for lfsr
	*/
	u8 state[15]={0};
	u8 temp5[sboxCnt_dizy80];
	u8 bin[120];
	
	for(int l=0; l<3; l++){	// 0 means key init, 1 mean IV init, 2 means first output producing block
		for(int i=0; i<ROUNDS; i++){ //ROUNDS
//			printf(" -------- %d round --------\n", i);		
			from8to5bits_120(temp5, state, 1);	 	
			if(l==0){
				if(i==0){
					key_add_2bit(key, temp5, 2);
				}			
			}
			if(l==1){
				if (i==0){
					IV_add_2bit(IV, temp5, 4);
				}
			} 						
			const_add_dizy80(round_consts[i], temp5);			
			sBox(temp5, sboxCnt_dizy80);			
			from5toBin_120(bin, temp5);
//			fromBinto8_120(state, bin, 1);
//				print(state, 15, "after sbox");
			perm120(bin);
			fromBinto8_120(state, bin, 1);
//				print(state, 15, "after perm");
			from8to5bits_120(temp5, state, 1);	
			shifting_dizy80(temp5);
			from5toBin_120(bin, temp5);
			fromBinto8_120(state, bin, 1);
//				print(state, 15, "after shifting");		
		}
		printf("\nstate %d: %02x%02x%02x%02x\n", l, state[0], state[1], state[2], state[3]); //32 bits keystream output
	}
}

void dizy128_ksg(u8* key, u8* round_consts, u8* IV){
	/*
	* IV and round consts xored before the s box
	* round consts are output for lfsr
	*/
	u8 state[20]={0};
	u8 temp5[sboxCnt_dizy128];
	u8 bin[160];

	for(int l=0; l<3; l++){ //l indicates number of blocks
		for(int i=0; i<ROUNDS; i++){ 
//			printf(" -------- %d round --------\n", i);		
			from8to5bits_160(temp5, state, 1);	 			
			if(l==0){
				if(i==0){
					key_add_2bit(key, temp5, 2);
				}									
			}
			if(l==1){
				if (i==0){
					IV_add_2bit(IV, temp5, 4);
				}
			} 			
			const_add_dizy128(round_consts[i], temp5); 				
			sBox(temp5, sboxCnt_dizy128);
			from5toBin_160(bin, temp5);
//			fromBinto8_120(state, bin, 1);
//				print(state, 15, "after sbox");
			perm160(bin);
			fromBinto8_160(state, bin, 1);
//				print(state, 20, "after perm ");
			from8to5bits_160(temp5, state, 1);	
			shifting_dizy128(temp5);
			from5toBin_160(bin, temp5);
			fromBinto8_160(state, bin, 1);			
		}
		printf("\nstate %d: %02x%02x%02x%02x\n", l, state[0], state[1], state[2], state[3]); //32 bits keystream output	
	}
}


int main(){
	// Uncomment either DIZY-80 or DIZY-128 to generate test vectors, key and IV values are loaded in two rounds according to algorithm definition, but for the test vector purposes 
	// only a short key and IV values added in the first rounds of related permutation blocks
	int i;

 	//DIZY-80-newinit-2bitxor 15 rounds test vectors uncomment the following lines of codes
 	
	u8 round_consts[ROUNDS];
	u8 init_poly[4] = {1,0,0,0};
	lfsr_4(round_consts, init_poly);
	printf("round consts: ");
	for(i=0; i<ROUNDS; i++)
		printf("%d ", round_consts[i]);
	printf("\n");
	u8 key[2]= {2,2};
	u8 IV[4] = {1,1,1,1};
//	st120_ksg(key, round_consts, IV);
	dizy80_ksg(key, round_consts, IV);

//	 lfsr outputs: 			8 1 3 7 15 14 13 10 5 11 6 12 9 2 4
// 	 first 32 bits output:  9def2292
// 	 second 32 bits output: 3c8cea27
//   third 32 bits:        	57f9de44 
	
/*****************************************************************************************************/
 	//DIZY-128-newinit-2bitxor 15 rounds test vectors uncomment the following lines of codes
// 	
//	u8 round_consts[ROUNDS];
//	u8 init_poly[4] = {1,0,0,0};
//	lfsr_4(round_consts, init_poly);
//	printf("round consts: ");
//	for(i=0; i<ROUNDS; i++)
//		printf("%d ", round_consts[i]);
//	printf("\n");
//	u8 key[2]= {2,2};
//	u8 IV[4] = {1,1,1,1};
//	dizy128_ksg(key, round_consts, IV);
	
//	// lfsr outputs: 			8 1 3 7 15 14 13 10 5 11 6 12 9 2 4
// 	// first 32 bits output:  8359d654
// 	// second 32 bits output: 46d7f8f2
 	// third 32 bits output:  3025582f

	
}

