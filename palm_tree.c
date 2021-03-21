/* Palm-tree is a copy of the tree programm common on windows systems.
 *
 * Author: Benedict Konhäuser
 */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

/* Prints a tree representaion of dir and all its subdirectories. */
void print_tree(DIR *dir, int depth, FILE *out)
{}

/* Prints an error message and exits the program. */
void print_error(const char *msg)
{
    fprintf(stderr, "error: %s!\n", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    FILE *out_file = stdout;

    // Processing command line arguments.
    opterr = 0;
    char c;
    while ((c = getopt(argc, argv, "f:h")) != -1)
    {
        switch (c)
        {
        case 'f':
            out_file = fopen(optarg, "w");
            if (!out_file)
            {
                char *msg; sprintf(msg, "could not open '%s'", optarg);
                print_error(msg);
            }
            break;
        case 'h':
        case '?':
            puts(
                "Usage: palm_tree [options] <path>\n"
                "\n"
                "Prints a tree representation of either the current directory if path is empty or path otherwise.\n"
                "\n"
                "Options:\n"
                "\tf <file-path>\tprint output to file instead of stdout\n"
                "\th\t\tprint help message\n"
                );
        }
    }

    // Open initial directory.
    DIR *init_dir = opendir(optind < argc? argv[optind] : "./");
    if (!init_dir)
        print_error("could not open initial directory");

    print_tree(init_dir, 0, out_file);

    return 0;
}
