#include "main.h"
int main(int argc,char *argv[]){
	
	FILE *fp,*fp2,*fp3;
	char * filename1, * filename2;
	
	filename1 = (char *)calloc(PATH_MAX,sizeof(char));
	filename2 = (char *)calloc(PATH_MAX,sizeof(char));
	
	/*Check whether the user enters the path*/
	
	if(argc!=2){
		fprintf(stderr,"Please enter one directory.\n");
		return 1;
	}
	
	/*Create a txt*/
	
	fp = fopen(MY_LIST_NAME,"w+");
	
	/*Write all the file found into txt*/
	
	list_dir(argv[1]);
	
	/*Close stream*/
	
	fclose(fp);
	
	/*Open that txt with read-only mode*/
	
	fp = fopen(MY_LIST_NAME,"r");
	
	int counter = 0;
	while(1){
		int is_end = 0;
		int i = 0;
		fgets(filename1,PATH_MAX,fp);
		
		for(i = 0; i < counter; i++){
			if(fgets(filename1,PATH_MAX+1,fp) == NULL){
				is_end = 1;
			}
		}
		
		if(filename1[strlen(filename1)-1] == '\n'){
			filename1[strlen(filename1)-1] = 0;
		}
		
//		printf("filename1: %s\n",filename1);
		// printf("is_end: %d\n",is_end);
		
		if(is_end){
			break;
		}
		
		if((fp2 = fopen(filename1,"r")) == NULL){
			fprintf (stderr, "Cannot open directory '%s':\n%s\n",
                 filename1, strerror (errno));
		} else {
//			printf("Openfile\n");
		}
		
		while(fgets(filename2,PATH_MAX+1,fp) != NULL){
			if(filename2[strlen(filename2)-1] == '\n'){
				filename2[strlen(filename2)-1] = 0;
			}
//			printf("filename2: %s\n",filename2);
			fp3 = fopen(filename2,"r");
			if(compare_file(fp2,fp3)){
				printf("%s is identical to %s\n\n",filename1,filename2);
			}
			fclose(fp3);
		}
		
		counter++;
		fseek(fp,0,SEEK_SET);
		fclose(fp2);
		
	}
	
	free(filename1);
	free(filename2);
	fclose(fp);
	return 0;  
}
