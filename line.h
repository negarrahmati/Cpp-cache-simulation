#ifndef Line_H_
#define Line_H_

#include <string>
#include "config.h"

class line {
	char block [LINE_SIZE_];
	unsigned long tag;
	bool valid;
	bool dirty;
	unsigned long timestamp;
	unsigned int LRU_tag;
	unsigned long int write_count[LINE_SIZE_];
	unsigned long int read_count[LINE_SIZE_];

public:
	line ();
	bool compare_tag(unsigned long tg);
	bool read_valid();
	bool read_dirty();
	unsigned long read_timestamp();
	unsigned int read_LRU_tag();
	void increase_LRU_tag();
	void clear_LRU_tag();
	bool read_word(int offset, char *data, unsigned long ts);
	bool write_word(int offset, char data, unsigned long ts);
	void replace(char *blk, unsigned long tg, unsigned long ts, string op);
	unsigned long int ret_write_count(unsigned int offset);
	void clear_write_count(unsigned int offset);
	void inc_write_count(unsigned int offset);
	unsigned long int ret_read_count(unsigned int offset);
	void clear_read_count(unsigned int offset);
	void inc_read_count(unsigned int offset);
};

#endif