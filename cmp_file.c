//https://stackoverflow.com/questions/6163611/compare-two-files
#include "main.h" 
/*Compare files function*/
int compare_file(char *filename1,char *filename2){
	int is_same = 1;
	int N = 1024;
	int counter = 0;
	int ret_memcmp;
	size_t ret_fread1,ret_fread2;
	char *buf1 = (char*) calloc (1,N+1);
	char *buf2 = (char*) calloc (1,N+1);
	FILE *fp1, *fp2;
	
	/*Open files*/
	
	if((fp1 = fopen(filename1,"r")) == NULL){
		fprintf (stderr, "Cannot open directory '%s':\n%s\n",
			filename1, strerror (errno));
	}
	if((fp2 = fopen(filename2,"r")) == NULL){
		fprintf (stderr, "Cannot open directory '%s':\n%s\n",
			filename2, strerror (errno));
	}
	
	/*Compare files*/
	
	do {
		ret_fread1 = fread(buf1,1,N,fp1);
		ret_fread2 = fread(buf2,1,N,fp2);
		ret_memcmp = memcmp(buf1,buf2,N);
		fprintf(stderr,"%d KB compared\r",counter);
		counter++;
		if(ret_fread1 != ret_fread2 || ret_memcmp){
			is_same = 0;
			break;
		}
	}while(!feof(fp1) || !feof(fp2));
	
	/*Close stream*/
	
	fclose(fp1);
	fclose(fp2);
	
	/*Free memory*/
	
	free(buf1);
	free(buf2);
	
	/*Return whether two files are same*/
	
	return is_same;
}
