
typedef unsigned char u8;
typedef unsigned int u32;

u8 S[32] = {
			0x00, 0x04, 0x0e, 0x09, 0x0d, 0x0b, 0x1e, 0x1b, 0x1c, 0x14, 0x13, 0x18, 0x17, 0x1d, 0x05, 0x0c, 
			0x0f, 0x11, 0x08, 0x15, 0x03, 0x1f, 0x19, 0x06, 0x10, 0x02, 0x16, 0x07, 0x1a, 0x0a, 0x01, 0x12 
			}; //00, 11,

void sBox(u8* temp, int adet){
	for(int k=0; k<adet; k++){
		temp[k] = S[temp[k]];
	}
}

void lfsr_4(u8* lfsr_consts, u8* initial_value){
	
	int i;
	u8 rg[4];
	for(i=0; i<4; i++){
		rg[i] = initial_value[i];
	}
	for(i=0; i<15; i++){
//		printf("%2d - ", i+1);
//		printf("%d%d%d%d ", rg[0], rg[1], rg[2], rg[3]);
		u8 output = (rg[0]<<3 | rg[1]<<2 | rg[2]<<1 | rg[3]);
		lfsr_consts[i] = output;
		
		u8 fb = rg[0] ^ rg[3];
		rg[0] = rg[1]; 
		rg[1] = rg[2]; 
		rg[2] = rg[3]; 
		rg[3] = fb;
	}
}

void lfsr_6(u8* lfsr_consts, u8* initial_value){
	
	int i;
	
	u8 rg[6];
	for(i=0; i<6; i++){
		rg[i] = initial_value[i];
	}
	
	for(i=0; i<63; i++){
//		printf("%2d - ", i+1);
//		printf("%d%d%d%d%d%d ", rg[0], rg[1], rg[2], rg[3], rg[4], rg[5]);
		u8 output = rg[0]<<5 | rg[1]<<4 | rg[2]<<3 | rg[3]<<2 | rg[4]<<1 | rg[5];
//		printf(" - %2d\n", output);
		lfsr_consts[i] = output;
		u8 fb = rg[5] ^ rg[0];
		rg[0] = rg[1]; 
		rg[1] = rg[2]; 
		rg[2] = rg[3]; 
		rg[3] = rg[4]; 
		rg[4] = rg[5]; 
		rg[5] = fb;
	}
}

void perm120(u8* state){
	
	u8 temp[120] = {0};
	//0
	temp[ 0] = state[6]  ^  state[22];
	temp[ 1] = state[16]  ^ state[8];
	temp[ 2] = state[0]  ^  state[18];
	temp[ 3] = state[15];          
	temp[ 4] = state[1];          
	//1                           
	temp[ 5] = state[7]  ^  state[27];
	temp[ 6] = state[20]  ^ state[13];
	temp[ 7] = state[2]  ^  state[23];
	temp[ 8] = state[21];          
	temp[ 9] = state[11];          
	//2                           
	temp[10] = state[12]  ^ state[17];
	temp[11] = state[26]  ^ state[3];
	temp[12] = state[10]  ^ state[28];
	temp[13] = state[25];          
	temp[14] = state[5];          
	//3                           
	temp[15] = state[2]  ^  state[27];
	temp[16] = state[21]  ^ state[9];
	temp[17] = state[11]  ^ state[24];
	temp[18] = state[16];          
	temp[19] = state[0];          
	//4                           
	temp[20] = state[7]  ^  state[17];
	temp[21] = state[15]  ^ state[14];
	temp[22] = state[1]  ^  state[29];
	temp[23] = state[20];          
	temp[24] = state[10];          
	//5                         
	temp[25] = state[12]  ^ state[25];
	temp[26] = state[22]  ^ state[4];
	temp[27] = state[5]  ^  state[19];
	temp[28] = state[26];
	temp[29] = state[6];
	//6              
	temp[30] = state[36]  ^ state[52];
	temp[31] = state[46]  ^ state[38];
	temp[32] = state[30]  ^ state[48];
	temp[33] = state[45];
	temp[34] = state[31];
	//7              
	temp[35] = state[37]  ^ state[57];
	temp[36] = state[50]  ^ state[43];
	temp[37] = state[32]  ^ state[53];
	temp[38] = state[51];
	temp[39] = state[41];
	//8              
	temp[40] = state[42]  ^ state[47];
	temp[41] = state[56]  ^ state[33];
	temp[42] = state[40]  ^ state[58];
	temp[43] = state[55];
	temp[44] = state[35];
	//9              
	temp[45] = state[32]  ^ state[57];
	temp[46] = state[51]  ^ state[39];
	temp[47] = state[41]  ^ state[54];
	temp[48] = state[46];
	temp[49] = state[30];
	//10             
	temp[50] = state[37]  ^ state[47];
	temp[51] = state[45]  ^ state[44];
	temp[52] = state[31]  ^ state[59];
	temp[53] = state[50];
	temp[54] = state[40];
	//11             
	temp[55] = state[42]  ^ state[55];
	temp[56] = state[52]  ^ state[34];
	temp[57] = state[35]  ^ state[49];
	temp[58] = state[56];
	temp[59] = state[36];
	//12
	temp[60] = state[66]  ^ state[82];
	temp[61] = state[76]  ^ state[68];
	temp[62] = state[60]  ^ state[78];
	temp[63] = state[75];
	temp[64] = state[61];
	//13
	temp[65] = state[67]  ^ state[87];
	temp[66] = state[80]  ^ state[73];
	temp[67] = state[62]  ^ state[83];
	temp[68] = state[81];
	temp[69] = state[71];
	//14
	temp[70] = state[72]  ^ state[77];
	temp[71] = state[86]  ^ state[63];
	temp[72] = state[70]  ^ state[88];
	temp[73] = state[85];
	temp[74] = state[65];
	//15
	temp[75] = state[62]  ^ state[87];
	temp[76] = state[81]  ^ state[69];
	temp[77] = state[71]  ^ state[84];
	temp[78] = state[76];
	temp[79] = state[60];
	//16
	temp[80] = state[67]  ^ state[77];
	temp[81] = state[75]  ^ state[74];
	temp[82] = state[61]  ^ state[89];
	temp[83] = state[80];
	temp[84] = state[70];
	//17
	temp[85] = state[72]  ^ state[85];
	temp[86] = state[82]  ^ state[64];
	temp[87] = state[65]  ^ state[79];
	temp[88] = state[86];
	temp[89] = state[66];
	//18
	temp[90] = state[96]  ^  state[112];
	temp[91] = state[106]  ^ state[98];
	temp[92] = state[90]  ^  state[108];
	temp[93] = state[105];
	temp[94] = state[91];
	//19
	temp[95] = state[97]  ^  state[117];
	temp[96] = state[110]  ^ state[103];
	temp[97] = state[92]  ^  state[113];
	temp[98] = state[111];
	temp[99] = state[101];
	//20
	temp[100] =state[102]  ^ state[107];
	temp[101] =state[116]  ^ state[93];
	temp[102] =state[100]  ^ state[118];
	temp[103] =state[115];
	temp[104] =state[95];
	//21
	temp[105] =state[92]  ^  state[117];
	temp[106] =state[111]  ^ state[99];
	temp[107] =state[101]  ^ state[114];
	temp[108] =state[106];
	temp[109] =state[90];
	//22
	temp[110] =state[97]  ^  state[107];
	temp[111] =state[105]  ^ state[104];
	temp[112] =state[91]  ^  state[119];
	temp[113] =state[110];         
	temp[114] =state[100];         
	//23                     
	temp[115] =state[102]  ^ state[115];
	temp[116] =state[112]  ^ state[94];
	temp[117] =state[95]  ^  state[109];
	temp[118] =state[116];            
	temp[119] =state[96];  
	
	for(int i=0; i<120; i++){
		state[i] = temp[i];
	}                                         
}

void perm160(u8* state){
	
	u8 temp[160] = {0};
	//0
    temp[ 0] = state[22] ^  state[2];
    temp[ 1] = state[35] ^  state[8];
    temp[ 2] = state[16] ^  state[28];
    temp[ 3] = state[10];             
    temp[ 4] = state[31];             
    //1                                
    temp[ 5] = state[20] ^  state[7];
    temp[ 6] = state[27] ^  state[13];
    temp[ 7] = state[1]  ^  state[33];
    temp[ 8] = state[15];             
    temp[ 9] = state[36];             
    //2                                 
    temp[10] = state[25] ^  state[12];
    temp[11] = state[32] ^  state[18];
    temp[12] = state[6]  ^  state[38];
    temp[13] = state[0];              
    temp[14] = state[21];             
    //3                                 
    temp[15] = state[37] ^  state[17];
    temp[16] = state[26] ^  state[3];
    temp[17] = state[11] ^  state[23];
    temp[18] = state[5];              
    temp[19] = state[30];             
    //4                                 
    temp[20] = state[27] ^  state[17];
    temp[21] = state[30] ^  state[9];
    temp[22] = state[0]  ^  state[24];
    temp[23] = state[11];             
    temp[24] = state[35];             
    //5                            
    temp[25] = state[32] ^  state[2];
    temp[26] = state[36] ^  state[14];
    temp[27] = state[5]  ^  state[29];
    temp[28] = state[16];
    temp[29] = state[20];
    //6             
    temp[30] = state[37] ^  state[7];
    temp[31] = state[21] ^  state[19];
    temp[32] = state[10] ^  state[34];
    temp[33] = state[1];
    temp[34] = state[25];
    //7              
    temp[35] = state[22] ^  state[12];
    temp[36] = state[31] ^  state[4];
    temp[37] = state[15] ^  state[39];
    temp[38] = state[6];
    temp[39] = state[26];
    //8              
    temp[40] = state[62] ^  state[42];
    temp[41] = state[75] ^  state[48];
    temp[42] = state[56] ^  state[68];
    temp[43] = state[50];
    temp[44] = state[71];
    //9              
    temp[45] = state[60] ^  state[47];
    temp[46] = state[67] ^  state[53];
    temp[47] = state[41] ^  state[73];
    temp[48] = state[55];
    temp[49] = state[76];
    //10             
    temp[50] = state[65] ^  state[52];
    temp[51] = state[72] ^  state[58];
    temp[52] = state[46] ^  state[78];
    temp[53] = state[40];
    temp[54] = state[61];
    //11             
    temp[55] = state[77] ^  state[57];
    temp[56] = state[66] ^  state[43];
    temp[57] = state[51] ^  state[63];
    temp[58] = state[45];
    temp[59] = state[70];
    //12
    temp[60] = state[67] ^  state[57];
    temp[61] = state[70] ^  state[49];
    temp[62] = state[40] ^  state[64];
    temp[63] = state[51];
    temp[64] = state[75];
    //13
    temp[65] = state[72] ^  state[42];
    temp[66] = state[76] ^  state[54];
    temp[67] = state[45] ^  state[69];
    temp[68] = state[56];
    temp[69] = state[60];
    //14
    temp[70] = state[77] ^  state[47];
    temp[71] = state[61] ^  state[59];
    temp[72] = state[50] ^  state[74];
    temp[73] = state[41];
    temp[74] = state[65];
    //15
    temp[75] = state[62] ^  state[52];
    temp[76] = state[71] ^  state[44];
    temp[77] = state[55] ^  state[79];
    temp[78] = state[46];
    temp[79] = state[66];
    //16
    temp[80] = state[102] ^  state[82];
    temp[81] = state[115] ^  state[88];
    temp[82] = state[96]  ^  state[108];
    temp[83] = state[90];
    temp[84] = state[111];
    //17
    temp[85] = state[100] ^  state[87];
    temp[86] = state[107] ^  state[93];
    temp[87] = state[81]  ^  state[113];
    temp[88] = state[95];
    temp[89] = state[116];
    //18
    temp[90] = state[105] ^  state[92];
    temp[91] = state[112] ^  state[98];
    temp[92] = state[86]  ^  state[118];
    temp[93] = state[80];
    temp[94] = state[101];
    //19
    temp[95] = state[117] ^  state[97];
    temp[96] = state[106] ^  state[83];
    temp[97] = state[91]  ^  state[103];
    temp[98] = state[85];
    temp[99] = state[110];
    //20
    temp[100] =state[107] ^  state[97];
    temp[101] =state[110] ^  state[89];
    temp[102] =state[80]  ^  state[104];
    temp[103] =state[91];
    temp[104] =state[115];
    //21
    temp[105] =state[112] ^  state[82];
    temp[106] =state[116] ^  state[94];
    temp[107] =state[85]  ^  state[109];
    temp[108] =state[96];
    temp[109] =state[100];
    //22
    temp[110] =state[117] ^  state[87];
    temp[111] =state[101] ^  state[99];
    temp[112] =state[90]  ^  state[114];
    temp[113] =state[81];          
    temp[114] =state[105];          
    //23                     
    temp[115] =state[102] ^  state[92];
    temp[116] =state[111] ^  state[84];
    temp[117] =state[95]  ^  state[119];
    temp[118] =state[86];            
    temp[119] =state[106];
        //24
    temp[120] = state[142] ^  state[122];
    temp[121] = state[155] ^  state[128];
    temp[122] = state[136] ^  state[148];
    temp[123] = state[130];
    temp[124] = state[151];
    //25
    temp[125] = state[140] ^  state[127];
    temp[126] = state[147] ^  state[133];
    temp[127] = state[121] ^  state[153];
    temp[128] = state[135];
    temp[129] = state[156];
    //26
    temp[130] = state[145] ^  state[132];
    temp[131] = state[152] ^  state[138];
    temp[132] = state[126] ^  state[158];
    temp[133] = state[120];
    temp[134] = state[141];
    //27
    temp[135] = state[157] ^  state[137];
    temp[136] = state[146] ^  state[123];
    temp[137] = state[131] ^  state[143];
    temp[138] = state[125];
    temp[139] = state[150];
    //28
    temp[140] = state[147] ^  state[137];
    temp[141] = state[150] ^  state[129];
    temp[142] = state[120] ^  state[144];
    temp[143] = state[131];
    temp[144] = state[155];
    //29
    temp[145] = state[152] ^  state[122];
    temp[146] = state[156] ^  state[134];
    temp[147] = state[125] ^  state[149];
    temp[148] = state[136];
    temp[149] = state[140];
    //30
    temp[150] = state[157] ^  state[127];
    temp[151] = state[141] ^  state[139];
    temp[152] = state[130] ^  state[154];
    temp[153] = state[121];          
    temp[154] = state[145];          
    //31                  
    temp[155] = state[142] ^  state[132];
    temp[156] = state[151] ^  state[124];
    temp[157] = state[135] ^  state[159];
    temp[158] = state[126];            
    temp[159] = state[146];

    for(int i=0; i<160; i++){
		state[i] = temp[i];
	} 
}                 


void key_add_1bit(u8* key, u8* temp5, int size){
	for(u8 i=0; i < size; i++){
		temp5[i] ^= key[i];
//		bit ^= 1;
	}
}

void IV_add_2bit(u8* IV, u8* temp5, int size){
//	u8 bit = 0;
	for(u8 i=0; i < size; i++){
		temp5[i] ^= (IV[i]<<3);
//		bit ^= 1;
	}
}

void key_add_2bit(u8* key, u8* temp5, int size){
	for(u8 i=0; i < size; i++){
		temp5[i] ^= (key[i]<<3);
//		bit ^= 1;
	}
}

void const_add_dizy80(u8 round_consts, u8* temp5){
	// adding const values from lfsr outputs
	for(u8 sbox_cnt=0; sbox_cnt < 24; sbox_cnt++){
		temp5[sbox_cnt] ^= (round_consts);
	}
}

void const_add_dizy128(u8 round_consts, u8* temp5){
	// adding const values from lfsr outputs
	for(u8 sbox_cnt=0; sbox_cnt < 32; sbox_cnt++){
		temp5[sbox_cnt] ^= round_consts;
	}
}


void from8to5bits_120(u8* temp5, u8* state, int offSet){
	
	temp5[0] = (state[1-offSet] >> 3)&0x1f;                      
	temp5[1] = (state[1-offSet] & 0x7)<<2 | (state[2-offSet] >> 6)&0x3;
	temp5[2] = (state[2-offSet] >> 1) & 0x1f;              
	temp5[3] = (state[2-offSet] & 0x1)<<4 | (state[3-offSet] >> 4)&0xf;
	temp5[4] = (state[3-offSet] & 0xf)<<1 | (state[4-offSet] >> 7)&0x1;
	temp5[5] = (state[4-offSet] >> 2) & 0x1f;                
	temp5[6] = (state[4-offSet] & 0x3)<<3 | (state[5-offSet] >> 5);
	temp5[7] =  state[5-offSet] & 0x1f;	         
					  
	temp5[8] = (state[6-offSet] >> 3)&0x1f;                     
	temp5[9] = (state[6-offSet] & 0x7)<<2 | (state[7-offSet] >> 6)&0x3;
	temp5[10]= (state[7-offSet] >> 1) & 0x1f;           
	temp5[11]= (state[7-offSet] & 0x1)<<4 | (state[8-offSet] >> 4)&0xf;
	temp5[12]= (state[8-offSet] & 0xf)<<1 | (state[9-offSet] >> 7)&0x1; 
	temp5[13]= (state[9-offSet] >> 2) & 0x1f;
	temp5[14]= (state[9-offSet] & 0x3)<<3 | (state[10-offSet] >> 5);
	temp5[15]= state[10-offSet] & 0x1f;
						 
	temp5[16]= (state[11-offSet] >> 3)&0x1f;
	temp5[17]= (state[11-offSet] & 0x7)<<2 | (state[12-offSet] >> 6)&0x3;
	temp5[18]= (state[12-offSet] >> 1) & 0x1f;
	temp5[19]= (state[12-offSet] & 0x1)<<4 | (state[13-offSet] >> 4)&0xf;
	temp5[20]= (state[13-offSet] & 0xf)<<1 | (state[14-offSet] >> 7)&0x1;
	temp5[21]= (state[14-offSet] >> 2) & 0x1f;
	temp5[22]= (state[14-offSet] & 0x3)<<3 | (state[15-offSet] >> 5);
	temp5[23]=  state[15-offSet] & 0x1f;
}

void from5toBin_120(u8* temp, u8* temp5){
	temp[ 0] = (temp5[0] >> 4)&1;
	temp[ 1] = (temp5[0] >> 3)&1;
	temp[ 2] = (temp5[0] >> 2)&1;
	temp[ 3] = (temp5[0] >> 1)&1;
	temp[ 4] =  temp5[0] & 1;
	//1
	temp[ 5] = (temp5[1] >> 4)&1;
	temp[ 6] = (temp5[1] >> 3)&1;
	temp[ 7] = (temp5[1] >> 2)&1;
	temp[ 8] = (temp5[1] >> 1)&1;
	temp[ 9] =  temp5[1] & 1;
	//2
	temp[10] = (temp5[2] >> 4)&1;
	temp[11] = (temp5[2] >> 3)&1;
	temp[12] = (temp5[2] >> 2)&1;
	temp[13] = (temp5[2] >> 1)&1;
	temp[14] =  temp5[2] & 1;
	//3
	temp[15] = (temp5[3] >> 4)&1;
	temp[16] = (temp5[3] >> 3)&1;
	temp[17] = (temp5[3] >> 2)&1;
	temp[18] = (temp5[3] >> 1)&1;
	temp[19] =  temp5[3] & 1;
	//4
	temp[20] = (temp5[4] >> 4)&1;
	temp[21] = (temp5[4] >> 3)&1;
	temp[22] = (temp5[4] >> 2)&1;
	temp[23] = (temp5[4] >> 1)&1;
	temp[24] =  temp5[4] & 1;
	//5
	temp[25] = (temp5[5] >> 4)&1;
	temp[26] = (temp5[5] >> 3)&1;
	temp[27] = (temp5[5] >> 2)&1;
	temp[28] = (temp5[5] >> 1)&1;
	temp[29] =  temp5[5] & 1;
	//6
	temp[30] = (temp5[6] >> 4)&1;
	temp[31] = (temp5[6] >> 3)&1;
	temp[32] = (temp5[6] >> 2)&1;
	temp[33] = (temp5[6] >> 1)&1;
	temp[34] =  temp5[6] & 1;
	//7
	temp[35] = (temp5[7] >> 4)&1;
	temp[36] = (temp5[7] >> 3)&1;
	temp[37] = (temp5[7] >> 2)&1;
	temp[38] = (temp5[7] >> 1)&1;
	temp[39] =  temp5[7] & 1;
	//8
	temp[40] =(temp5[8] >> 4)&1;
	temp[41] =(temp5[8] >> 3)&1;
	temp[42] =(temp5[8] >> 2)&1;
	temp[43] =(temp5[8] >> 1)&1;
	temp[44] = temp5[8] & 1;                 
	//9                         
	temp[45] =(temp5[9] >> 4)&1;
	temp[46] =(temp5[9] >> 3)&1;
	temp[47] =(temp5[9] >> 2)&1;
	temp[48] =(temp5[9] >> 1)&1;
	temp[49] = temp5[9] & 1;                 
	//10                        
	temp[50] =(temp5[10] >> 4)&1;
	temp[51] =(temp5[10] >> 3)&1;
	temp[52] =(temp5[10] >> 2)&1;
	temp[53] =(temp5[10] >> 1)&1;
	temp[54] = temp5[10] & 1;                  
	//11                        
	temp[55] =(temp5[11] >> 4)&1;
	temp[56] =(temp5[11] >> 3)&1;
	temp[57] =(temp5[11] >> 2)&1;
	temp[58] =(temp5[11] >> 1)&1;
	temp[59] = temp5[11] & 1;                  
	//12                        
	temp[60] =(temp5[12] >> 4)&1;
	temp[61] =(temp5[12] >> 3)&1;
	temp[62] =(temp5[12] >> 2)&1;
	temp[63] =(temp5[12] >> 1)&1;
	temp[64] = temp5[12] & 1;                  
	//13                        
	temp[65] =(temp5[13] >> 4)&1;
	temp[66] =(temp5[13] >> 3)&1;
	temp[67] =(temp5[13] >> 2)&1;
	temp[68] =(temp5[13] >> 1)&1;
	temp[69] = temp5[13] & 1;
	//14
	temp[70] =(temp5[14] >> 4)&1;
	temp[71] =(temp5[14] >> 3)&1;
	temp[72] =(temp5[14] >> 2)&1;
	temp[73] =(temp5[14] >> 1)&1;
	temp[74] = temp5[14] & 1;                  
	//15                        
	temp[75] =(temp5[15] >> 4)&1;
	temp[76] =(temp5[15] >> 3)&1;
	temp[77] =(temp5[15] >> 2)&1;
	temp[78] =(temp5[15] >> 1)&1;
	temp[79] = temp5[15] & 1;                  
	//16                        
	temp[80] =(temp5[16] >> 4)&1;
	temp[81] =(temp5[16] >> 3)&1;
	temp[82] =(temp5[16] >> 2)&1;
	temp[83] =(temp5[16] >> 1)&1;
	temp[84] = temp5[16] & 1;                  
	//17                        
	temp[85] =(temp5[17] >> 4)&1;
	temp[86] =(temp5[17] >> 3)&1;
	temp[87] =(temp5[17] >> 2)&1;
	temp[88] =(temp5[17] >> 1)&1;
	temp[89] = temp5[17] & 1;                  
	//18                        
	temp[90] =(temp5[18] >> 4)&1;
	temp[91] =(temp5[18] >> 3)&1;
	temp[92] =(temp5[18] >> 2)&1;
	temp[93] =(temp5[18] >> 1)&1;
	temp[94] = temp5[18] & 1;                  
	//19                        
	temp[95] =(temp5[19] >> 4)&1;
	temp[96] =(temp5[19] >> 3)&1;
	temp[97] =(temp5[19] >> 2)&1;
	temp[98] =(temp5[19] >> 1)&1;
	temp[99] = temp5[19] & 1;
	//20
	temp[100] =(temp5[20] >> 4)&1;
	temp[101] =(temp5[20] >> 3)&1;
	temp[102] =(temp5[20] >> 2)&1;
	temp[103] =(temp5[20] >> 1)&1;
	temp[104] = temp5[20] & 1;
	//21
	temp[105] =(temp5[21] >> 4)&1;
	temp[106] =(temp5[21] >> 3)&1;
	temp[107] =(temp5[21] >> 2)&1;
	temp[108] =(temp5[21] >> 1)&1;
	temp[109] = temp5[21] & 1;
	//22
	temp[110] =(temp5[22] >> 4)&1;
	temp[111] =(temp5[22] >> 3)&1;
	temp[112] =(temp5[22] >> 2)&1;
	temp[113] =(temp5[22] >> 1)&1;
	temp[114] = temp5[22] & 1;
	//23
	temp[115] =(temp5[23] >> 4)&1;
	temp[116] =(temp5[23] >> 3)&1;
	temp[117] =(temp5[23] >> 2)&1;
	temp[118] =(temp5[23] >> 1)&1;
	temp[119] = temp5[23] & 1;
}
 
void fromBinto8_120(u8* state, u8* bin, int offSet){

	state[0] = 0;	 
	state[1-offSet] =  ((bin[ 0]&1)<<7) | ((bin[ 1]&1)<<6) | ((bin[ 2]&1)<<5) |  ((bin[ 3]&1)<<4) | ((bin[ 4]&1)<<3) | ((bin[ 5]&1)<<2) | ((bin[ 6]&1)<<1) | bin[ 7]&1;
	state[2-offSet] =  ((bin[ 8]&1)<<7) | ((bin[ 9]&1)<<6) | ((bin[10]&1)<<5) |  ((bin[11]&1)<<4) | ((bin[12]&1)<<3) | ((bin[13]&1)<<2) | ((bin[14]&1)<<1) | bin[15]&1;
	state[3-offSet] =  ((bin[16]&1)<<7) | ((bin[17]&1)<<6) | ((bin[18]&1)<<5) |  ((bin[19]&1)<<4) | ((bin[20]&1)<<3) | ((bin[21]&1)<<2) | ((bin[22]&1)<<1) | bin[23]&1;
	                  
	state[4-offSet] =  ((bin[24]&1)<<7) | ((bin[25]&1)<<6) | ((bin[26]&1)<<5) |  ((bin[27]&1)<<4) | ((bin[28]&1)<<3) | ((bin[29]&1)<<2) | ((bin[30]&1)<<1) | bin[31]&1;
	state[5-offSet] =  ((bin[32]&1)<<7) | ((bin[33]&1)<<6) | ((bin[34]&1)<<5) |  ((bin[35]&1)<<4) | ((bin[36]&1)<<3) | ((bin[37]&1)<<2) | ((bin[38]&1)<<1) | bin[39]&1;
	state[6-offSet] =  ((bin[40]&1)<<7) | ((bin[41]&1)<<6) | ((bin[42]&1)<<5) |  ((bin[43]&1)<<4) | ((bin[44]&1)<<3) | ((bin[45]&1)<<2) | ((bin[46]&1)<<1) | bin[47]&1;
	state[7-offSet] =  ((bin[48]&1)<<7) | ((bin[49]&1)<<6) | ((bin[50]&1)<<5) |  ((bin[51]&1)<<4) | ((bin[52]&1)<<3) | ((bin[53]&1)<<2) | ((bin[54]&1)<<1) | bin[55]&1;
                   
	state[8-offSet] =  ((bin[56]&1)<<7) | ((bin[57]&1)<<6) | ((bin[58]&1)<<5) |  ((bin[59]&1)<<4) | ((bin[60]&1)<<3) | ((bin[61]&1)<<2) | ((bin[62]&1)<<1) | bin[63]&1;
	state[9-offSet] =  ((bin[64]&1)<<7) | ((bin[65]&1)<<6) | ((bin[66]&1)<<5) |  ((bin[67]&1)<<4) | ((bin[68]&1)<<3) | ((bin[69]&1)<<2) | ((bin[70]&1)<<1) | bin[71]&1;
	state[10-offSet] = ((bin[72]&1)<<7) | ((bin[73]&1)<<6) | ((bin[74]&1)<<5) |  ((bin[75]&1)<<4) | ((bin[76]&1)<<3) | ((bin[77]&1)<<2) | ((bin[78]&1)<<1) | bin[79]&1;
	state[11-offSet] = ((bin[80]&1)<<7) | ((bin[81]&1)<<6) | ((bin[82]&1)<<5) |  ((bin[83]&1)<<4) | ((bin[84]&1)<<3) | ((bin[85]&1)<<2) | ((bin[86]&1)<<1) | bin[87]&1;
	                 
	state[12-offSet] = ((bin[88]&1)<<7) | ((bin[89]&1)<<6) | ((bin[90]&1)<<5) |  ((bin[91]&1)<<4) | ((bin[92]&1)<<3) | ((bin[93]&1)<<2) | ((bin[94]&1)<<1) | bin[95]&1;
	state[13-offSet] = ((bin[96]&1)<<7) | ((bin[97]&1)<<6) | ((bin[98]&1)<<5) |  ((bin[99]&1)<<4) | ((bin[100]&1)<<3)| ((bin[101]&1)<<2)| ((bin[102]&1)<<1)| bin[103]&1;
	state[14-offSet] = ((bin[104]&1)<<7)| ((bin[105]&1)<<6)| ((bin[106]&1)<<5)|  ((bin[107]&1)<<4)| ((bin[108]&1)<<3)| ((bin[109]&1)<<2)| ((bin[110]&1)<<1)| bin[111]&1;
	state[15-offSet] = ((bin[112]&1)<<7)| ((bin[113]&1)<<6)| ((bin[114]&1)<<5)|  ((bin[115]&1)<<4)| ((bin[116]&1)<<3)| ((bin[117]&1)<<2)| ((bin[118]&1)<<1)| bin[119]&1;
}

void shifting_dizy80(u8* temp5){
	u8 temp[18];
	
	for(int i=0; i<18; i++){
		temp[i] = temp5[i+3];
	}
	temp5[3]  = temp[9];
	temp5[4]  = temp[10];
	temp5[5]  = temp[11];
	temp5[6]  = temp[0];
	temp5[7]  = temp[1];
	temp5[8]  = temp[2];
	temp5[9]  = temp[12];
	temp5[10] = temp[13];
	temp5[11] = temp[14];
	temp5[12] = temp[3];
	temp5[13] = temp[4];
	temp5[14] = temp[5];
	temp5[15] = temp[15];
	temp5[16] = temp[16];
	temp5[17] = temp[17];
	temp5[18] = temp[6];
	temp5[19] = temp[7];
	temp5[20] = temp[8];
}

void shifting_dizy128(u8* temp5){
	u8 temp[32];	
	for(int i=0; i<32; i++){
		temp[i] = temp5[i];
	}
	
	temp5[ 0] = temp[ 0];
	temp5[ 1] = temp[ 1];
	temp5[ 2] = temp[ 2];
	temp5[ 3] = temp[ 3];

	temp5[ 4] = temp[16];
	temp5[ 5] = temp[17];
	temp5[ 6] = temp[18];
	temp5[ 7] = temp[19];
	
	temp5[ 8] = temp[4];
	temp5[ 9] = temp[5];
	temp5[10] = temp[6];
	temp5[11] = temp[7];
	
	temp5[12] = temp[20];
	temp5[13] = temp[21];
	temp5[14] = temp[22];
	temp5[15] = temp[23];
	
	temp5[16] = temp[8];
	temp5[17] = temp[9];
	temp5[18] = temp[10];
	temp5[19] = temp[11];
	
	temp5[20] = temp[24];
	temp5[21] = temp[25];
	temp5[22] = temp[26];
	temp5[23] = temp[27];
	
	temp5[24] = temp[12];
	temp5[25] = temp[13];
	temp5[26] = temp[14];
	temp5[27] = temp[15];
	
	temp5[28] = temp[28];
	temp5[29] = temp[29];
	temp5[30] = temp[30];
	temp5[31] = temp[31];
}


void from8to5bits_160(u8* temp5, u8* state, int offSet){
	
	temp5[0] = (state[1-offSet] >> 3)&0x1f;                      
	temp5[1] = (state[1-offSet] & 0x7)<<2 | (state[2-offSet] >> 6)&0x3;
	temp5[2] = (state[2-offSet] >> 1) & 0x1f;              
	temp5[3] = (state[2-offSet] & 0x1)<<4 | (state[3-offSet] >> 4)&0xf;
	temp5[4] = (state[3-offSet] & 0xf)<<1 | (state[4-offSet] >> 7)&0x1;
	temp5[5] = (state[4-offSet] >> 2) & 0x1f;                
	temp5[6] = (state[4-offSet] & 0x3)<<3 | (state[5-offSet] >> 5);
	temp5[7] =  state[5-offSet] & 0x1f;	         
					  
	temp5[8] = (state[6-offSet] >> 3)&0x1f;                     
	temp5[9] = (state[6-offSet] & 0x7)<<2 | (state[7-offSet] >> 6)&0x3;
	temp5[10]= (state[7-offSet] >> 1) & 0x1f;           
	temp5[11]= (state[7-offSet] & 0x1)<<4 | (state[8-offSet] >> 4)&0xf;
	temp5[12]= (state[8-offSet] & 0xf)<<1 | (state[9-offSet] >> 7)&0x1; 
	temp5[13]= (state[9-offSet] >> 2) & 0x1f;
	temp5[14]= (state[9-offSet] & 0x3)<<3 | (state[10-offSet] >> 5);
	temp5[15]= state[10-offSet] & 0x1f;
						 
	temp5[16]= (state[11-offSet] >> 3)&0x1f;
	temp5[17]= (state[11-offSet] & 0x7)<<2 | (state[12-offSet] >> 6)&0x3;
	temp5[18]= (state[12-offSet] >> 1) & 0x1f;
	temp5[19]= (state[12-offSet] & 0x1)<<4 | (state[13-offSet] >> 4)&0xf;
	temp5[20]= (state[13-offSet] & 0xf)<<1 | (state[14-offSet] >> 7)&0x1;
	temp5[21]= (state[14-offSet] >> 2) & 0x1f;
	temp5[22]= (state[14-offSet] & 0x3)<<3 | (state[15-offSet] >> 5);
	temp5[23]=  state[15-offSet] & 0x1f;
	
	temp5[24]= (state[16-offSet] >> 3)&0x1f;
	temp5[25]= (state[16-offSet] & 0x7)<<2 | (state[17-offSet] >> 6)&0x3;
	temp5[26]= (state[17-offSet] >> 1) & 0x1f;
	temp5[27]= (state[17-offSet] & 0x1)<<4 | (state[18-offSet] >> 4)&0xf;
	temp5[28]= (state[18-offSet] & 0xf)<<1 | (state[19-offSet] >> 7)&0x1;
	temp5[29]= (state[19-offSet] >> 2) & 0x1f;
	temp5[30]= (state[19-offSet] & 0x3)<<3 | (state[20-offSet] >> 5);
	temp5[31]=  state[20-offSet] & 0x1f;
}

void from5toBin_160(u8* temp, u8* temp5){
	
	temp[ 0] = (temp5[0] >> 4)&1;
	temp[ 1] = (temp5[0] >> 3)&1;
	temp[ 2] = (temp5[0] >> 2)&1;
	temp[ 3] = (temp5[0] >> 1)&1;
	temp[ 4] =  temp5[0] & 1;
	//1
	temp[ 5] = (temp5[1] >> 4)&1;
	temp[ 6] = (temp5[1] >> 3)&1;
	temp[ 7] = (temp5[1] >> 2)&1;
	temp[ 8] = (temp5[1] >> 1)&1;
	temp[ 9] =  temp5[1] & 1;
	//2
	temp[10] = (temp5[2] >> 4)&1;
	temp[11] = (temp5[2] >> 3)&1;
	temp[12] = (temp5[2] >> 2)&1;
	temp[13] = (temp5[2] >> 1)&1;
	temp[14] =  temp5[2] & 1;
	//3
	temp[15] = (temp5[3] >> 4)&1;
	temp[16] = (temp5[3] >> 3)&1;
	temp[17] = (temp5[3] >> 2)&1;
	temp[18] = (temp5[3] >> 1)&1;
	temp[19] =  temp5[3] & 1;
	//4
	temp[20] = (temp5[4] >> 4)&1;
	temp[21] = (temp5[4] >> 3)&1;
	temp[22] = (temp5[4] >> 2)&1;
	temp[23] = (temp5[4] >> 1)&1;
	temp[24] =  temp5[4] & 1;
	//5
	temp[25] = (temp5[5] >> 4)&1;
	temp[26] = (temp5[5] >> 3)&1;
	temp[27] = (temp5[5] >> 2)&1;
	temp[28] = (temp5[5] >> 1)&1;
	temp[29] =  temp5[5] & 1;
	//6
	temp[30] = (temp5[6] >> 4)&1;
	temp[31] = (temp5[6] >> 3)&1;
	temp[32] = (temp5[6] >> 2)&1;
	temp[33] = (temp5[6] >> 1)&1;
	temp[34] =  temp5[6] & 1;
	//7
	temp[35] = (temp5[7] >> 4)&1;
	temp[36] = (temp5[7] >> 3)&1;
	temp[37] = (temp5[7] >> 2)&1;
	temp[38] = (temp5[7] >> 1)&1;
	temp[39] =  temp5[7] & 1;
	//8
	temp[40] =(temp5[8] >> 4)&1;
	temp[41] =(temp5[8] >> 3)&1;
	temp[42] =(temp5[8] >> 2)&1;
	temp[43] =(temp5[8] >> 1)&1;
	temp[44] = temp5[8] & 1;                 
	//9                         
	temp[45] =(temp5[9] >> 4)&1;
	temp[46] =(temp5[9] >> 3)&1;
	temp[47] =(temp5[9] >> 2)&1;
	temp[48] =(temp5[9] >> 1)&1;
	temp[49] = temp5[9] & 1;                 
	//10                        
	temp[50] =(temp5[10] >> 4)&1;
	temp[51] =(temp5[10] >> 3)&1;
	temp[52] =(temp5[10] >> 2)&1;
	temp[53] =(temp5[10] >> 1)&1;
	temp[54] = temp5[10] & 1;                  
	//11                        
	temp[55] =(temp5[11] >> 4)&1;
	temp[56] =(temp5[11] >> 3)&1;
	temp[57] =(temp5[11] >> 2)&1;
	temp[58] =(temp5[11] >> 1)&1;
	temp[59] = temp5[11] & 1;                  
	//12                        
	temp[60] =(temp5[12] >> 4)&1;
	temp[61] =(temp5[12] >> 3)&1;
	temp[62] =(temp5[12] >> 2)&1;
	temp[63] =(temp5[12] >> 1)&1;
	temp[64] = temp5[12] & 1;                  
	//13                        
	temp[65] =(temp5[13] >> 4)&1;
	temp[66] =(temp5[13] >> 3)&1;
	temp[67] =(temp5[13] >> 2)&1;
	temp[68] =(temp5[13] >> 1)&1;
	temp[69] = temp5[13] & 1;
	//14
	temp[70] =(temp5[14] >> 4)&1;
	temp[71] =(temp5[14] >> 3)&1;
	temp[72] =(temp5[14] >> 2)&1;
	temp[73] =(temp5[14] >> 1)&1;
	temp[74] = temp5[14] & 1;                  
	//15                        
	temp[75] =(temp5[15] >> 4)&1;
	temp[76] =(temp5[15] >> 3)&1;
	temp[77] =(temp5[15] >> 2)&1;
	temp[78] =(temp5[15] >> 1)&1;
	temp[79] = temp5[15] & 1;                  
	//16                        
	temp[80] =(temp5[16] >> 4)&1;
	temp[81] =(temp5[16] >> 3)&1;
	temp[82] =(temp5[16] >> 2)&1;
	temp[83] =(temp5[16] >> 1)&1;
	temp[84] = temp5[16] & 1;                  
	//17                        
	temp[85] =(temp5[17] >> 4)&1;
	temp[86] =(temp5[17] >> 3)&1;
	temp[87] =(temp5[17] >> 2)&1;
	temp[88] =(temp5[17] >> 1)&1;
	temp[89] = temp5[17] & 1;                  
	//18                        
	temp[90] =(temp5[18] >> 4)&1;
	temp[91] =(temp5[18] >> 3)&1;
	temp[92] =(temp5[18] >> 2)&1;
	temp[93] =(temp5[18] >> 1)&1;
	temp[94] = temp5[18] & 1;                  
	//19                        
	temp[95] =(temp5[19] >> 4)&1;
	temp[96] =(temp5[19] >> 3)&1;
	temp[97] =(temp5[19] >> 2)&1;
	temp[98] =(temp5[19] >> 1)&1;
	temp[99] = temp5[19] & 1;
	//20
	temp[100] =(temp5[20] >> 4)&1;
	temp[101] =(temp5[20] >> 3)&1;
	temp[102] =(temp5[20] >> 2)&1;
	temp[103] =(temp5[20] >> 1)&1;
	temp[104] = temp5[20] & 1;
	//21
	temp[105] =(temp5[21] >> 4)&1;
	temp[106] =(temp5[21] >> 3)&1;
	temp[107] =(temp5[21] >> 2)&1;
	temp[108] =(temp5[21] >> 1)&1;
	temp[109] = temp5[21] & 1;
	//22
	temp[110] =(temp5[22] >> 4)&1;
	temp[111] =(temp5[22] >> 3)&1;
	temp[112] =(temp5[22] >> 2)&1;
	temp[113] =(temp5[22] >> 1)&1;
	temp[114] = temp5[22] & 1;
	//23
	temp[115] =(temp5[23] >> 4)&1;
	temp[116] =(temp5[23] >> 3)&1;
	temp[117] =(temp5[23] >> 2)&1;
	temp[118] =(temp5[23] >> 1)&1;
	temp[119] = temp5[23] & 1;
	//24
	temp[120] =(temp5[24] >> 4)&1;
	temp[121] =(temp5[24] >> 3)&1;
	temp[122] =(temp5[24] >> 2)&1;
	temp[123] =(temp5[24] >> 1)&1;
	temp[124] = temp5[24] & 1;                  
	//25                         
	temp[125] =(temp5[25] >> 4)&1;
	temp[126] =(temp5[25] >> 3)&1;
	temp[127] =(temp5[25] >> 2)&1;
	temp[128] =(temp5[25] >> 1)&1;
	temp[129] = temp5[25] & 1;                  
	//26                         
	temp[130] =(temp5[26] >> 4)&1;
	temp[131] =(temp5[26] >> 3)&1;
	temp[132] =(temp5[26] >> 2)&1;
	temp[133] =(temp5[26] >> 1)&1;
	temp[134] = temp5[26] & 1;                  
	//27 13                      
	temp[135] =(temp5[27] >> 4)&1;
	temp[136] =(temp5[27] >> 3)&1;
	temp[137] =(temp5[27] >> 2)&1;
	temp[138] =(temp5[27] >> 1)&1;
	temp[139] = temp5[27] & 1;
	//28
	temp[140] =(temp5[28] >> 4)&1;
	temp[141] =(temp5[28] >> 3)&1;
	temp[142] =(temp5[28] >> 2)&1;
	temp[143] =(temp5[28] >> 1)&1;
	temp[144] = temp5[28] & 1;
	//29 14
	temp[145] =(temp5[29] >> 4)&1;
	temp[146] =(temp5[29] >> 3)&1;
	temp[147] =(temp5[29] >> 2)&1;
	temp[148] =(temp5[29] >> 1)&1;
	temp[149] = temp5[29] & 1;
	//30
	temp[150] =(temp5[30] >> 4)&1;
	temp[151] =(temp5[30] >> 3)&1;
	temp[152] =(temp5[30] >> 2)&1;
	temp[153] =(temp5[30] >> 1)&1;
	temp[154] = temp5[30] & 1;
	//31 15
	temp[155] =(temp5[31] >> 4)&1;
	temp[156] =(temp5[31] >> 3)&1;
	temp[157] =(temp5[31] >> 2)&1;
	temp[158] =(temp5[31] >> 1)&1;
	temp[159] = temp5[31] & 1;
}
void fromBinto8_160(u8* state, u8* bin, int offSet){
	 
	state[1-offSet] =  ((bin[ 0]&1)<<7) | ((bin[ 1]&1)<<6) | ((bin[ 2]&1)<<5) |  ((bin[ 3]&1)<<4) | ((bin[ 4]&1)<<3) | ((bin[ 5]&1)<<2) | ((bin[ 6]&1)<<1) | bin[ 7]&1;
	state[2-offSet] =  ((bin[ 8]&1)<<7) | ((bin[ 9]&1)<<6) | ((bin[10]&1)<<5) |  ((bin[11]&1)<<4) | ((bin[12]&1)<<3) | ((bin[13]&1)<<2) | ((bin[14]&1)<<1) | bin[15]&1;
	state[3-offSet] =  ((bin[16]&1)<<7) | ((bin[17]&1)<<6) | ((bin[18]&1)<<5) |  ((bin[19]&1)<<4) | ((bin[20]&1)<<3) | ((bin[21]&1)<<2) | ((bin[22]&1)<<1) | bin[23]&1;	                  
	state[4-offSet] =  ((bin[24]&1)<<7) | ((bin[25]&1)<<6) | ((bin[26]&1)<<5) |  ((bin[27]&1)<<4) | ((bin[28]&1)<<3) | ((bin[29]&1)<<2) | ((bin[30]&1)<<1) | bin[31]&1;	
	state[5-offSet] =  ((bin[32]&1)<<7) | ((bin[33]&1)<<6) | ((bin[34]&1)<<5) |  ((bin[35]&1)<<4) | ((bin[36]&1)<<3) | ((bin[37]&1)<<2) | ((bin[38]&1)<<1) | bin[39]&1;
	
	state[6-offSet] =  ((bin[40]&1)<<7) | ((bin[41]&1)<<6) | ((bin[42]&1)<<5) |  ((bin[43]&1)<<4) | ((bin[44]&1)<<3) | ((bin[45]&1)<<2) | ((bin[46]&1)<<1) | bin[47]&1;
	state[7-offSet] =  ((bin[48]&1)<<7) | ((bin[49]&1)<<6) | ((bin[50]&1)<<5) |  ((bin[51]&1)<<4) | ((bin[52]&1)<<3) | ((bin[53]&1)<<2) | ((bin[54]&1)<<1) | bin[55]&1;                
	state[8-offSet] =  ((bin[56]&1)<<7) | ((bin[57]&1)<<6) | ((bin[58]&1)<<5) |  ((bin[59]&1)<<4) | ((bin[60]&1)<<3) | ((bin[61]&1)<<2) | ((bin[62]&1)<<1) | bin[63]&1;
	state[9-offSet] =  ((bin[64]&1)<<7) | ((bin[65]&1)<<6) | ((bin[66]&1)<<5) |  ((bin[67]&1)<<4) | ((bin[68]&1)<<3) | ((bin[69]&1)<<2) | ((bin[70]&1)<<1) | bin[71]&1;
	state[10-offSet] = ((bin[72]&1)<<7) | ((bin[73]&1)<<6) | ((bin[74]&1)<<5) |  ((bin[75]&1)<<4) | ((bin[76]&1)<<3) | ((bin[77]&1)<<2) | ((bin[78]&1)<<1) | bin[79]&1;
	
	state[11-offSet] = ((bin[80]&1)<<7) | ((bin[81]&1)<<6) | ((bin[82]&1)<<5) |  ((bin[83]&1)<<4) | ((bin[84]&1)<<3) | ((bin[85]&1)<<2) | ((bin[86]&1)<<1) | bin[87]&1;                 
	state[12-offSet] = ((bin[88]&1)<<7) | ((bin[89]&1)<<6) | ((bin[90]&1)<<5) |  ((bin[91]&1)<<4) | ((bin[92]&1)<<3) | ((bin[93]&1)<<2) | ((bin[94]&1)<<1) | bin[95]&1;	
	state[13-offSet] = ((bin[96]&1)<<7) | ((bin[97]&1)<<6) | ((bin[98]&1)<<5) |  ((bin[99]&1)<<4) | ((bin[100]&1)<<3)| ((bin[101]&1)<<2)| ((bin[102]&1)<<1)| bin[103]&1;
	state[14-offSet] = ((bin[104]&1)<<7)| ((bin[105]&1)<<6)| ((bin[106]&1)<<5)|  ((bin[107]&1)<<4)| ((bin[108]&1)<<3)| ((bin[109]&1)<<2)| ((bin[110]&1)<<1)| bin[111]&1;
	state[15-offSet] = ((bin[112]&1)<<7)| ((bin[113]&1)<<6)| ((bin[114]&1)<<5)|  ((bin[115]&1)<<4)| ((bin[116]&1)<<3)| ((bin[117]&1)<<2)| ((bin[118]&1)<<1)| bin[119]&1;
    
	state[16-offSet] = ((bin[120]&1)<<7) | ((bin[121]&1)<<6) | ((bin[122]&1)<<5) | ((bin[123]&1)<<4) | ((bin[124]&1)<<3) | ((bin[125]&1)<<2) | ((bin[126]&1)<<1) | bin[127]&1;
	state[17-offSet] = ((bin[128]&1)<<7) | ((bin[129]&1)<<6) | ((bin[130]&1)<<5) | ((bin[131]&1)<<4) | ((bin[132]&1)<<3) | ((bin[133]&1)<<2) | ((bin[134]&1)<<1) | bin[135]&1;
	state[18-offSet] = ((bin[136]&1)<<7) | ((bin[137]&1)<<6) | ((bin[138]&1)<<5) | ((bin[139]&1)<<4) | ((bin[140]&1)<<3) | ((bin[141]&1)<<2) | ((bin[142]&1)<<1) | bin[143]&1;
	state[19-offSet] = ((bin[144]&1)<<7) | ((bin[145]&1)<<6) | ((bin[146]&1)<<5) | ((bin[147]&1)<<4) | ((bin[148]&1)<<3) | ((bin[149]&1)<<2) | ((bin[150]&1)<<1) | bin[151]&1;
	state[20-offSet] = ((bin[152]&1)<<7) | ((bin[153]&1)<<6) | ((bin[154]&1)<<5) | ((bin[155]&1)<<4) | ((bin[156]&1)<<3) | ((bin[157]&1)<<2) | ((bin[158]&1)<<1) | bin[159]&1;
}

void print(u8* temp, int size, char* comment){
	printf("%s\n", comment);
	for(int i=0; i<size; i++){
		printf("%02x ", temp[i]);	
	}
	printf("\n");
}


