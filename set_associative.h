#ifndef SET_ASSOCIATIVE_H_
#define SET_ASSOCIATIVE_H_

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "line.h"

class set_associative{
	unsigned int set_size;
	vector < vector <line> > line_CAM;
	vector < vector<unsigned int> > empty_slots;
public:
	set_associative();
	unsigned int ret_size();
	bool match(unsigned long add, unsigned int *pos);
	bool read_access(unsigned long ts, unsigned long add, char *data);
	bool write_access(unsigned long ts, unsigned long add, char data);
	unsigned int find_victim(unsigned int index);
	void file_out();
};

#endif
