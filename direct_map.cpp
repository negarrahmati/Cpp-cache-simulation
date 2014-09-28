#include "direct_map.h"

direct_map::direct_map(){
	num_lines = CACHE_SIZE_/LINE_SIZE_;
	line clear_line;
	for(unsigned int i=0; i<num_lines; i++)
		line_set.push_back(clear_line);
}

unsigned int direct_map::ret_size(){
	return num_lines;
}

bool direct_map::match(unsigned long add){
	unsigned long index = (add / LINE_SIZE_) % num_lines;
	unsigned long tag = (add / LINE_SIZE_) / num_lines;
	
	if(line_set[index].read_valid())
		return (line_set[index].compare_tag(tag));
	else
		return false;
}

bool direct_map::read_access(unsigned long ts, unsigned long add, char *data){
	unsigned long index = (add / LINE_SIZE_) % num_lines;
	unsigned long tag = (add / LINE_SIZE_) / num_lines;
	int offset = (int) (add % LINE_SIZE_);
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY

	if(match(add)){
		line_set[index].read_word(offset, data, ts);
		return true;		// HIT
	}
	else{
		line_set[index].replace(blk, tag, ts, "R");
		(*data) = blk[offset];
		return false;		// MISS
	}
}

bool direct_map::write_access(unsigned long ts, unsigned long add, char data){
	unsigned long index = (add / LINE_SIZE_) % num_lines;
	unsigned long tag = (add / LINE_SIZE_) / num_lines;
	int offset = (int) (add % LINE_SIZE_);
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY

	if(match(add)){
		line_set[index].write_word(offset, data, ts);
		return true;		// HIT
	}
	else{
		blk[offset] = data;
		line_set[index].replace(blk, tag, ts, "W");
		return false;		// MISS
	}
}

