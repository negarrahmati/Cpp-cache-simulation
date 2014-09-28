#ifndef FULL_ASSOCIATIVE_H_
#define FULL_ASSOCIATIVE_H_

#include "line.h"

class full_associative{
	unsigned int CAM_size;
	vector <line> CAM_set;
	vector<unsigned int> empty_slots;
public:
	full_associative();
	unsigned int ret_size();
	bool match(unsigned long add, unsigned int *pos);
	bool read_access(unsigned long ts, unsigned long add, char *data);
	bool write_access(unsigned long ts, unsigned long add, char data);
	unsigned int find_victim();
};

#endif
