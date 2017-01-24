#include <cstdlib>
#include "hash.h"

BitSequence* hash_blake256(BitSequence* data, DataLength databitlen) {
	BitSequence *hash = (BitSequence *) malloc(sizeof(BitSequence) * 64);
	Hash(256, data, databitlen, hash);
	return hash;
}
