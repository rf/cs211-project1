#ifndef _WORDSTAT_H
#define _WORDSTAT_H

// get a whole file at once and stick it in res
int get_file (char * filename, char ** res);

// print usage; name is argv[0]
void usage (char * name);

// check if a value is in the dict
bool in_dict (char ** dict, int dict_count, char * search);

#endif
