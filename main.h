#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>	//sprintf
#include <string.h>	//memcmp,memset,strcmp
#include <stdlib.h>	//calloc

char (** list_dir (const char * dir_name));
int compare_file(FILE *file_compared,FILE *file_checked);

#endif
