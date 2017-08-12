#include "main.h"

char (** list_dir (const char * dir_name));
int compare_file(FILE *file_compared,FILE *file_checked);

 int main(int argc,char *argv[])  
 {  
	FILE *fp1,*fp2;
	int j,k;
	char **filename;
	if(argc!=2)
	{
		fprintf(stderr,"Please enter one directory.\n");
		return 1;
	}	
//	printf("Noting");
	filename = list_dir(argv[1]);
	 for(j=1;j<=10000;j++)
	 {
		if(filename[j][0] == 0){
			break;
		}
		
//		printf("Noting");
//		printf("%s\n",filename[j]);
		
		fp1=fopen(filename[j],"r");
		for(k=j+1;k<=10000;k++)
		{
		   fp2=fopen(filename[k],"r");
		   if(compare_file(fp1,fp2))
		   {
			  printf("%s and %s is equal\n",filename[j],filename[k]);
		   }	
		}
	 }
	 
	 free(filename);
	 return 0;  
 }
