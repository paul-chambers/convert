#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
/* "readdir" etc. are defined here. */
#include <dirent.h>
/* limits.h defines "PATH_MAX". */
#include <limits.h>

void list_dir( const char * dir_name )
{
    DIR * d;

    d = opendir( dir_name );
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n", dir_name, strerror( errno ));
        exit( EXIT_FAILURE );
    }

    do {
        struct dirent * entry;

        entry = readdir( d );
        if ( entry != NULL )
        {
            const char *entryName = entry->d_name;
            /* Print the name of the file and directory. */
            printf ("%s/%s\n", dir_name, entryName);

            if ( (entry->d_type & DT_DIR) && entryName[0] != '.' )
            {
                int path_length;
                char path[PATH_MAX];

                path_length = snprintf( path, PATH_MAX, "%s/%s", dir_name, entryName );
                printf( "%s\n", path );
                if ( path_length >= PATH_MAX ) {
                    fprintf( stderr, "Path length has got too long.\n" );
                    exit( EXIT_FAILURE );
                }
                /* Recursively call ourself with the new path. */
                list_dir( path );
            }
        }
    } while ( entry != NULL );

    /* After going through all the entries, close the directory. */
    if ( closedir (d) )
    {
        fprintf (stderr, "Could not close '%s': %s\n", dir_name, strerror( errno ));
        exit (EXIT_FAILURE);
    }
}

int main ()
{
    list_dir ("/usr/share/games");
    return 0;
}
