/* Palm-tree is a copy of the tree programm common on windows systems.
 *
 * Author: Benedict Konhäuser
 */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Returns all subdirectories excluding .. and . as a list of names. */
char **get_subdirs(DIR *dir, int *dir_count)
{
    int count = 0;
    char **subs = malloc(0);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
   	// Ignore all files.
	if (entry->d_type == DT_DIR &&
        // Ignore .. and .
            strcmp(entry->d_name, "..") != 0 &&
            strcmp(entry->d_name, ".")  != 0)
        {
            // Put name into the list.
            count++;
            subs = realloc(subs, count*sizeof(char **));
            subs[count - 1] = malloc(1000);
            strcpy(subs[count - 1], entry->d_name);
        }
    }

    *dir_count = count;
    return subs;
}

char *str_append(char *s1, char *s2)
{
    char *ret = malloc(1000);
    strcpy(ret, s1);
    strcat(ret, s2);

    return ret;
}

char *path_append(char *p1, char *p2)
{
    char *ret = str_append(p1, p2);
    strcat(ret, "/");

    return ret;
}

/* Prints a tree representaion of dir and all its subdirectories. */
void print_tree(char *path, char *indent)
{
    DIR *dir = opendir(path);
    if (!dir)
        return;

    int sub_c;
    char **subs = get_subdirs(dir, &sub_c);
    for (int i = 0; i < sub_c - 1; i++)
    {
        printf("%s├───%s\n", indent, subs[i]);
        // Print descendants.
        char *next_path = path_append(path, subs[i]);
        char *next_indent = str_append(indent, "|   ");
        print_tree(next_path, next_indent);
        free(next_path); free(next_indent);
    }
    if (sub_c > 0)
    {
        printf("%s╰───%s\n", indent, subs[sub_c - 1]);
        char *next_path = path_append(path, subs[sub_c - 1]);
        char *next_indent = str_append(indent, "    ");
        print_tree(next_path, next_indent);
        free(next_path); free(next_indent);
    }

    free(subs);
    closedir(dir);
}

int main(int argc, char **argv)
{
    // Print current directory.
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
       printf("%s\n", cwd);

    // Plot subdirectories.
    char *indent = malloc(1000);
    *indent = '\0';
    print_tree("./", indent);

    return 0;
}
