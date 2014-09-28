#ifndef CONFIG_H_
#define CONFIG_H_

#include "index.h"

/*enum cache_type {DIRECT_MAP_, FULLY_ASSOCATIVE_, SET_ASSOCIATIVE_};
enum replacement_policy {LRU_, LFU_, FIFO_};

cache_type cache = DIRECT_MAP_;
replacement_policy policy = LRU_; */

#define ADDRESS_WIDTH_	32	//in bits
#define CACHE_SIZE_		131072	//Data cahce (without tag and access bits) in Bytes
#define WAY_SIZE_		4	//For cache_type = SET_ASSOCIATIVE_
#define LINE_SIZE_		128	//in Bytes
#define DATA_SIZE_		4

#endif
