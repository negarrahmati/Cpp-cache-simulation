#include "line.h"

line::line(){
	valid = false;
	dirty = false;
	tag	  = 0;
	for(int i=0; i< LINE_SIZE_; i++){
		block[i] = 0;
		write_count[i] = 0;
		read_count[i] = 0;
	}
}

bool line::compare_tag(unsigned long tg){
	return (tag == tg);
}

bool line::read_valid(){
	return valid;
}

bool line::read_dirty(){
	return dirty;
}

unsigned long line::read_timestamp(){
	return timestamp;
}

unsigned int line::read_LRU_tag(){
	return LRU_tag;
}

void line::increase_LRU_tag(){
	LRU_tag ++;
	return;
}

void line::clear_LRU_tag(){
	LRU_tag = 0;
}

bool line::read_word(int offset, char *data, unsigned long ts){
	if(valid==false || offset >= LINE_SIZE_)
		return false;
	else{
		(*data)=block[offset];
		timestamp = ts;
		return true;
	}
}

bool line::write_word(int offset, char data, unsigned long ts){
	if(valid==false || offset >= LINE_SIZE_)
		return false;
	else{
		block[offset]=data;
		dirty = true;
		timestamp = ts;
		return true;
	}
}

void line::replace(char *blk, unsigned long tg, unsigned long ts, string op){
	if(read_dirty()); //Write Data back to memory

	for(int i=0;i<LINE_SIZE_;i++){
		block[i] = blk[i];
		write_count[i]++;
	}
	tag = tg;
	valid = true;
	if(op == "R")
		dirty = false;
	else
		dirty = true;
	timestamp = ts;
	return;
}


unsigned long int line::ret_write_count(unsigned int offset){
	return(write_count[offset]);
}

void line::clear_write_count(unsigned int offset){
	write_count[offset] = 0;
	return;
}

void line::inc_write_count(unsigned int offset){
	write_count[offset]++;
	return;
}

unsigned long int line::ret_read_count(unsigned int offset){
	return(read_count[offset]);
}

void line::clear_read_count(unsigned int offset){
	read_count[offset] = 0;
	return;
}

void line::inc_read_count(unsigned int offset){
	read_count[offset]++;
	return;
}
