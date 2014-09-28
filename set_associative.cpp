
#include "set_associative.h"

set_associative::set_associative(){
	vector <line> set;
	vector <unsigned int> set_empty_list;

	set_size = (CACHE_SIZE_ / LINE_SIZE_) / WAY_SIZE_;
	line clear_line;
	for(unsigned int i=0; i<WAY_SIZE_; i++){
		set.push_back(clear_line);
		set_empty_list.push_back(i);
	}
	for(unsigned int i=0; i<set_size; i++){
			line_CAM.push_back(set);
			empty_slots.push_back(set_empty_list);
	}
}


unsigned int set_associative::ret_size(){
	return (set_size);
}

bool set_associative::match(unsigned long add, unsigned int *pos){
	unsigned long index = (add / LINE_SIZE_) % set_size;
	unsigned long tag = (add / LINE_SIZE_) / set_size;
		
	for(unsigned int i=0; i<WAY_SIZE_; i++){
		if(line_CAM[index][i].read_valid() && line_CAM[index][i].compare_tag(tag)){
			(*pos) = i;
			return true;
		}
	}
	return false;
}

bool set_associative::read_access(unsigned long ts, unsigned long add, char *data){
	unsigned long index = (add / LINE_SIZE_) % set_size;
	unsigned long tag = (add / LINE_SIZE_) / set_size;
	int offset = (int) (add % LINE_SIZE_);
	unsigned int pos;
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY
	bool hit_miss;

	if(match(add, &pos)){
		line_CAM[index][pos].read_word(offset, data, ts);
		for(int i=0; i<DATA_SIZE_; i++){
			line_CAM[index][pos].inc_read_count(offset+i);
		}
		hit_miss = true;		// HIT
	}
	else{
		pos = find_victim(index);
		if(line_CAM[index][pos].read_dirty()){
			for(int i=0; i<LINE_SIZE_; i++)
				line_CAM[index][pos].inc_read_count(i);
		}
		line_CAM[index][pos].replace(blk, tag, ts, "R");
		(*data) = blk[offset];
		hit_miss = false;		// MISS
	}
//LRU policy
	line_CAM[index][pos].clear_LRU_tag();
	for(unsigned int i=0; i<WAY_SIZE_; i++){
		if(i!=pos && line_CAM[index][i].read_valid())
			line_CAM[index][i].increase_LRU_tag();
	}
//LRU policy
	return hit_miss;
}

bool set_associative::write_access(unsigned long ts, unsigned long add, char data){
	unsigned long index = (add / LINE_SIZE_) % set_size;
	unsigned long tag = (add / LINE_SIZE_) / set_size;
	int offset = (int) (add % LINE_SIZE_);
	unsigned int pos;
	char blk[LINE_SIZE_] = {0}; // READ FROM MAIN MEMORY
	bool hit_miss;

	if(match(add, &pos)){
		line_CAM[index][pos].write_word(offset, data, ts);
		for(int i=0; i<DATA_SIZE_; i++)
			line_CAM[index][pos].inc_write_count(offset+i);
		hit_miss = true;		// HIT
	}
	else{
		pos = find_victim(index);
		if(line_CAM[index][pos].read_dirty()){
			for(int i=0; i<LINE_SIZE_; i++)
				line_CAM[index][pos].inc_read_count(i);
		}
		blk[offset] = data;
		line_CAM[index][pos].replace(blk, tag, ts, "W");
		hit_miss = false;		// MISS
	}
//LRU policy
	line_CAM[index][pos].clear_LRU_tag();
	for(unsigned int i=0; i<WAY_SIZE_; i++){
		if(i!=pos && line_CAM[index][i].read_valid())
			line_CAM[index][i].increase_LRU_tag();
	}
//LRU policy
	return hit_miss;
}

unsigned int set_associative::find_victim(unsigned int index){
	unsigned int pos;
	unsigned int LRU_tag;
	if(!empty_slots[index].empty()){
		pos = empty_slots[index].front();
		empty_slots[index].erase(empty_slots[index].begin());
	} else {
		LRU_tag = line_CAM[index][0].read_LRU_tag();
		pos = 0;
		for(unsigned int i=1; i<WAY_SIZE_; i++){
			if(line_CAM[index][i].read_LRU_tag() > LRU_tag){
				LRU_tag = line_CAM[index][i].read_LRU_tag();
				pos = i;
			}
		}
	}
	return pos;
}

void set_associative::file_out(){
	ofstream write_file, read_file;
	write_file.open("write_counts");
	read_file.open("read_counts");
	for(unsigned long int i=0; i<set_size; i++){
		for(unsigned int j=0; j<WAY_SIZE_; j++){
			for(unsigned int k=0; k<LINE_SIZE_; k++){
				write_file<<line_CAM[i][j].ret_write_count(k)<<"\t";
				read_file<<line_CAM[i][j].ret_read_count(k)<<"\t";
			}
			write_file<<"\t\t";
			read_file<<"\t\t";
		}
		write_file<<"\n";
		read_file<<"\n";
	}
	write_file.close();
	read_file.close();
}
