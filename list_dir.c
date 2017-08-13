//https://www.lemoda.net/c/recursive-directory/
#include "main.h"
#include <sys/types.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>


/* List the files in "dir_name". */

void list_dir (const char * dir_name)
{
    DIR * d;
	int i = 0;
	
	/* Write found files into a txt file*/
	FILE * fp;
	fp = fopen(MY_LIST_NAME,"a+");
	
    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
	
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
	i = 0;
    while (1) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
		
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;

        /* Print the name of the file and directory. */

		if(!(entry->d_type & DT_DIR)){
			
			fprintf(fp, "%s/%s\n", dir_name, d_name);
			i++;
			if(i>10000){
				fprintf(stderr,"10000 files found. Reached the max.");
				break;
			}
		}
		

		if (entry->d_type & DT_DIR) {

			/* Check that the directory is not "d" or d's parent. */
			
			if (strcmp (d_name, "..") != 0 &&
				strcmp (d_name, ".") != 0) {
				int path_length;
				char path[PATH_MAX];

				path_length = snprintf (path, PATH_MAX,
										"%s/%s", dir_name, d_name);
//				printf ("%s\n", path);
				if (path_length >= PATH_MAX) {
					fprintf (stderr, "Path length has got too long.\n");
					exit (EXIT_FAILURE);
				}
				/* Recursively call "list_dir" with the new path. */
				list_dir (path);
			}
		}
	}
	
	/*Close stream*/
	
	if(fclose(fp)){
		fprintf (stderr, "Could not close stream: %s\n", strerror (errno));
        exit (EXIT_FAILURE);
	}
	
    /* After going through all the entries, close the directory. */
	
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }

}
