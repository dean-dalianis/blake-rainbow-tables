#ifndef HASH_H_
#define HASH_H_

#include "blake_ref.h"

BitSequence* hash_blake256(BitSequence*,
	DataLength databitlen = 48);

#endif /* HASH_H_ */
