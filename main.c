#include "main.h"

int main(int argc,char *argv[]){
	
	FILE *fp;
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
	
	/*Compare files*/
	
	int counter = 0;	//count how many files have been checked
	while(1){
		int is_end = 0;
		int i = 0;
		fgets(filename1,PATH_MAX,fp);
		
		/*Jugde whether meet the end of file list*/
		
		for(i = 0; i < counter; i++){
			if(fgets(filename1,PATH_MAX+1,fp) == NULL){
				is_end = 1;
			}
		}
				
		if(is_end){
			break;
		}
		
		/*Remove the '\n' at the end of directory*/
		
		if(filename1[strlen(filename1)-1] == '\n'){
			filename1[strlen(filename1)-1] = 0;
		}
		
		while(fgets(filename2,PATH_MAX+1,fp) != NULL){
			if(filename2[strlen(filename2)-1] == '\n'){
				filename2[strlen(filename2)-1] = 0;
			}
		
		/*Compare files*/
		
			if(compare_file(filename1,filename2)){
				printf("%s is identical to %s\n\n",filename1,filename2);
			}
		}
		
		counter++;
		fseek(fp,0,SEEK_SET);
	}
	
	/*Print how many files have been checked*/
	
	fprintf(stderr,"%d files have been checked",counter);
	
	/*Free memory*/
	
	free(filename1);
	free(filename2);
	
	/*Close file*/
	
	fclose(fp);
	
	return 0;  
}
