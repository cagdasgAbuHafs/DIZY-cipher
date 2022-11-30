# DIZY-cipher

There are two directories for C and VHDL codes of the DIZY-80 and DIZY-128 algorithms. C codes are generated only for test vector purposes therefore no optimizations are considered.

VHDL implementation results of the different designs given in the files which ends with '.rpt' extension. DIZY-80-ht and DIZY-128-ht stands for high throughput, the other two designs have lower area requirements but runs for more cycles. 

Output bits given as Ciphertext are in the most significant 32 bits for both VHDL and C codes. Even though, they are shown in that position for readibilty, the analysis should be made such that output bits given as ciphertext are from 0th, 3rd, 6th, .... 93rd bits. (From left to right notation, starting from the most significant bits) Indeed, it does not change the hardware cost.      
