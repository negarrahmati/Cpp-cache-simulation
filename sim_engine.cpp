//An extern function for simulating direct_map cache
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "line.h"
#include "config.h"
#include "direct_map.h"
#include "full_associative.h"
#include "set_associative.h"

void simulate_direct(){
	unsigned long simulation_time = 0;
	direct_map cache;
	unsigned long next_time, next_add;
	char r_data;
	char w_data;
	string acc_time, acc_address, acc_opr, word_data;

	unsigned long hit_access = 0, miss_access = 0, total_access = 0;
	bool hit_miss;

	ifstream read_file;
	read_file.open("input");
	while(!read_file.eof()){
		read_file >> acc_time >> acc_address >> acc_opr >> word_data;
		next_time = atoi(acc_time.c_str());
		if(simulation_time > next_time)
			cout<<"Simulation time error in direct_map";
		simulation_time = next_time;
		next_add = atoi(acc_address.c_str());
		if((double) next_add >= pow(2.0, (int) ADDRESS_WIDTH_))
			cout<<"Address range error in direct_map";
		w_data = (char) atoi(word_data.c_str());

		if(acc_opr == "R")
			hit_miss = cache.read_access(simulation_time, next_add, &r_data);
		else
			hit_miss = cache.write_access(simulation_time, next_add, w_data);

		total_access ++;
		if(hit_miss)
			hit_access ++;
		else
			miss_access ++;
	}
	read_file.close();

	cout<<"Total Number of accesses: " << total_access << endl;
	cout<<"Number of hits (rate): " << hit_access << "(" << hit_access/total_access << ")" << endl;
	cout<<"Number of misses (rate): " << miss_access << "(" << miss_access/total_access << ")" << endl;

	return;
}

void simulate_full_associative(){
	unsigned long simulation_time = 0;
	full_associative cache;
	unsigned long next_time, next_add;
	char r_data;
	char w_data;
	string acc_time, acc_address, acc_opr, word_data;

	unsigned long hit_access = 0, miss_access = 0, total_access = 0;
	bool hit_miss;

	ifstream read_file;
	read_file.open("input");
	while(!read_file.eof()){
		read_file >> acc_time >> acc_address >> acc_opr >> word_data;
		next_time = atoi(acc_time.c_str());
		if(simulation_time > next_time)
			cout<<"Simulation time error in fully_associative";
		simulation_time = next_time;
		next_add = atoi(acc_address.c_str());
		if((double) next_add >= pow(2.0, (int) ADDRESS_WIDTH_))
			cout<<"Address range error in fully_associative";
		w_data = (char) atoi(word_data.c_str());

		if(acc_opr == "R")
			hit_miss = cache.read_access(simulation_time, next_add, &r_data);
		else
			hit_miss = cache.write_access(simulation_time, next_add, w_data);

		total_access ++;
		if(hit_miss)
			hit_access ++;
		else
			miss_access ++;
	}
	read_file.close();

	cout<<"Total Number of accesses: " << total_access << endl;
	cout<<"Number of hits (rate): " << hit_access << "(" << hit_access/total_access << ")" << endl;
	cout<<"Number of misses (rate): " << miss_access << "(" << miss_access/total_access << ")" << endl;

	return;
}

void simulate_set_associative(){
	unsigned long simulation_time = 0;
	set_associative cache;
	unsigned long next_time, next_add;
	char r_data='x';
	char w_data='x';
//	string acc_time, acc_address, acc_opr, word_data;
	char index[DATA_SIZE_];
	string acc_time, acc_address, acc_opr, acc_size, hit_miss_str, first_byte, second_byte, third_byte, four_byte;

	unsigned long hit_access = 0, miss_access = 0, total_access = 0;
	bool hit_miss;

	ifstream read_file;
	read_file.open("equake_DL1_a");
	while(!read_file.eof()){
		read_file >> acc_time >> acc_address >> acc_opr >> acc_size >> hit_miss_str >> first_byte >> second_byte >>
			third_byte >> four_byte;
		next_time = atoi(acc_time.c_str());
		if(simulation_time > next_time)
			cout<<"Simulation time error in set_associative";
		simulation_time = next_time;
		next_add = atoi(acc_address.c_str());
		if((double) next_add >= pow(2.0, (int) ADDRESS_WIDTH_))
			cout<<"Address range error in set_associative";
		index[0] = atoi(first_byte.c_str());
		index[1] = atoi(second_byte.c_str());
		index[2] = atoi(third_byte.c_str());
		index[3] = atoi(four_byte.c_str());

		if(acc_opr == "Read")
			hit_miss = cache.read_access(simulation_time, next_add, &r_data);
		else
			hit_miss = cache.write_access(simulation_time, next_add, w_data);

		total_access ++;
		if(hit_miss)
			hit_access ++;
		else
			miss_access ++;
	}
	read_file.close();
	cache.file_out();

	cout<<"Total Number of accesses: " << total_access << endl;
	cout<<"Number of hits (rate): " << hit_access << "(" << (float) hit_access/total_access << ")" << endl;
	cout<<"Number of misses (rate): " << miss_access << "(" << (float) miss_access/total_access << ")" << endl;

	return;
}
