
#include "full_associative.h"

full_associative::full_associative(){
	CAM_size = CACHE_SIZE_/LINE_SIZE_;
	line clear_line;
	for(unsigned int i=0; i<CAM_size; i++){
		CAM_set.push_back(clear_line);
		empty_slots.push_back(i);
	}
}

unsigned int full_associative::ret_size(){
	return CAM_size;
}

bool full_associative::match(unsigned long add, unsigned int *pos){
	unsigned long tag = add / LINE_SIZE_;
	
	for(unsigned int i=0;i<CAM_size;i++){
		if(CAM_set[i].read_valid() && CAM_set[i].compare_tag(tag)){
			(*pos) = i;
			return true;
		}
	}
	return false;
}

bool full_associative::read_access(unsigned long ts, unsigned long add, char *data){
	unsigned long tag = add / LINE_SIZE_;
	int offset = (int) (add % LINE_SIZE_);
	unsigned int pos;
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY
	bool hit_miss;

	if(match(add, &pos)){
		CAM_set[pos].read_word(offset, data, ts);
		hit_miss = true;		// HIT
	}
	else{
		pos = find_victim();
		CAM_set[pos].replace(blk, tag, ts, "R");
		(*data) = blk[offset];
		hit_miss = false;		// MISS
	}
//LRU policy
	CAM_set[pos].clear_LRU_tag();
	for(unsigned int i=0; i<CAM_size; i++){
		if(i!=pos && CAM_set[i].read_valid())
			CAM_set[i].increase_LRU_tag();
	}
//LRU policy
	return hit_miss;
}

bool full_associative::write_access(unsigned long ts, unsigned long add, char data){
	unsigned long tag = add / LINE_SIZE_;
	int offset = (int) (add % LINE_SIZE_);
	unsigned int pos;
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY
	bool hit_miss;

	if(match(add, &pos)){
		CAM_set[pos].write_word(offset, data, ts);
		hit_miss = true;		// HIT
	}
	else{
		pos = find_victim();
		blk[offset] = data;
		CAM_set[pos].replace(blk, tag, ts, "W");
		hit_miss = false;		// MISS
	}
//LRU policy
	CAM_set[pos].clear_LRU_tag();
	for(unsigned int i=0; i<CAM_size; i++){
		if(i != pos && CAM_set[i].read_valid())
			CAM_set[i].increase_LRU_tag();
	}
//LRU policy
	return hit_miss;
}

unsigned int full_associative::find_victim(){
	unsigned int pos;
	unsigned int LRU_tag;
	if(!empty_slots.empty()){
		pos = empty_slots.front();
		empty_slots.erase(empty_slots.begin());
	} else {
		LRU_tag = CAM_set[0].read_LRU_tag();
		pos = 0;
		for(unsigned int i=1; i<CAM_size; i++){
			if(CAM_set[i].read_LRU_tag() > LRU_tag){
				LRU_tag = CAM_set[i].read_LRU_tag();
				pos = i;
			}
		}
	}
	return pos;
}

