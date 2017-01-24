#include <cstdlib>
#include <cstdio>
#include "reduction_function.h"
#include "../info.h"

char rcharSet[charSetLen] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '@' };


char* reduction_function256(BitSequence hash[64], int step) {
	char *data = (char*)malloc(sizeof(char)* maxPwLen);
	for (int i = 0, j = 0; i < maxPwLen; i++, j++) {
		int pos = (hash[j] ^ step) & 63;
		data[i] = rcharSet[pos];
		step >>= 8;
	}
	return data;
}

//char* reduction_function256(BitSequence hash[64]) {
//	char *data = (char*)malloc(sizeof(char)* maxPwLen);
//	int step = 2;
//	for (int i = 0, j = 0; i < maxPwLen; i++, j++) {
//		int pos = (hash[j] ^ step) & 63;
//		data[i] = rcharSet[pos];
//		step <<= 2;
//	}
//	return data;
//}