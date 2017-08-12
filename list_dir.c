//https://www.lemoda.net/c/recursive-directory/
#include "main.h"
#include <sys/types.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

#define FULL_DIR_LEN 1000

/* List the files in "dir_name". */

char (** list_dir (const char * dir_name))
{
    DIR * d;
	int i = 0;
	/* Create a dynamic array to store found files*/
	char (** found_file);
	found_file = (char **)calloc(10000,sizeof(char *));
	for(i = 0; i < 10000; i++){
		found_file[i] = (char *)calloc(FULL_DIR_LEN,sizeof(char));
	}
	
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
//		printf ("%s/%s\n", dir_name, d_name);
		if(!(entry->d_type & DT_DIR)){
			int full_dir;
			full_dir = snprintf(found_file[i], FULL_DIR_LEN, "%s/%s", dir_name, d_name);
			if (full_dir >= FULL_DIR_LEN) {
				fprintf (stderr, "Path length has got too long.\n");
				exit (EXIT_FAILURE);
				}
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
	
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
//	i -=1;
//	for(;i>=0;i--){
//		printf("%s\n",found_file[i]);
//	}
	return found_file;
}
