#include <cstring>
#include <cstdlib>
#include <iostream>
#include "chain_generator.h"
#include "../hash/hash.h"
#include "../reduce/reduction_function.h"

using namespace std;

Chain* generate_chain(char *password) {
	Chain *result_chain = new Chain();	// create new chain object

	for (int i = 0; i < maxPwLen; i++) {
		// save password to chain
		result_chain->head[i] = password[i];
	}
	result_chain->head[maxPwLen] = '\0';

	BitSequence *hash = NULL;
	BitSequence *bpassword = (BitSequence *) malloc(sizeof(BitSequence) * 6);// empty BitSequence* for password

	for (int i = 0; i < chainLen; i++) {
		free(hash);
		for (int j = 0; j < maxPwLen; j++) {
			// char* to BitSequence*
			bpassword[j] = password[j];
		}
		free(password);
		hash = hash_blake256(bpassword);
		password = reduction_function256(hash, i);
	}
	free(bpassword);
	free(password);
	for (int i = 0; i < 64; i++) {
		// save hash to chain
		result_chain->tail[i] = hash[i];
	}
	return result_chain;
}
