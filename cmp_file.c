//https://stackoverflow.com/questions/6163611/compare-two-files
#include "main.h" 

int compare_file(FILE *file_compared,FILE *file_checked){
	int is_same = 1;
	int N = 1048576;
	int counter = 0;
	int ret_memcmp;
	size_t ret_fread1,ret_fread2;
	char *buf1 = (char*) calloc (1,N+1);
	char *buf2 = (char*) calloc (1,N+1);
	do {
		ret_fread1 = fread(buf1,1,N,file_compared);
		ret_fread2 = fread(buf2,1,N,file_checked);
		ret_memcmp = memcmp(buf1,buf2,N);
		fprintf(stderr,"%d MB compared\r",counter);
		counter++;
		if(ret_fread1 != ret_fread2 || ret_memcmp)
		{
			is_same = 0;
			break;
		}
	}
	while(!feof(file_compared) || !feof(file_checked));
	return is_same;
}
