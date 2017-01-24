#ifndef CHAIN_GENERATOR_H_
#define CHAIN_GENERATOR_H_

#include "../hash/blake_ref.h"
#include "../info.h"

class Chain {
public:
	Chain() {
	}
	~Chain() {
	}
	char head[maxPwLen + 1];
	BitSequence tail[64];
};

Chain* generate_chain(char*);

#endif /* CHAIN_GENERATOR_H_ */

