#ifndef DIRECT_MAP_H_
#define DIRECT_MAP_H_

#include "line.h"

class direct_map{
	unsigned int num_lines;
	vector <line> line_set;
public:
	direct_map();
	unsigned int ret_size();
	bool match(unsigned long add);
	bool read_access(unsigned long ts, unsigned long add, char *data);
	bool write_access(unsigned long ts, unsigned long add, char data);
};

#endif
