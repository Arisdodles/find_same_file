#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>	//sprintf
#include <string.h>	//memcmp,memset,strcmp
#include <stdlib.h>	//calloc
#include <limits.h> //PATH_MAX
#include <errno.h>	//errno
#define MY_LIST_NAME "all_file.txt"

void list_dir (const char * dir_name);
int compare_file(char *file_compared,char *file_checked);

#endif
