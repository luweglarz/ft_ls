#include "includes/ft_ls.h"

int main(int ac, char **av){
    int         errors = 0;
    e_options   opts = 0;
    t_file      *files = NULL;

    if (ac >= 1)
        errors = get_files_opts(ac, av, &files, &opts);
    if (opts & UNKNOWN){
        write(2, "ft_ls: invalid option\n", 23);
        free_files(files);
        exit(1);
    }
    if (count_files(files) == 1 && files->isdir == true){
        if (opts & R)
            print_dir_recur(files, opts);
        else if (errors >= 1)
		    print_dir(files, opts, false);
        else
            print_dir(files, opts, true);
        free(files);
	}
    else{
        while(files){
            printf("file: %s\n", files->name);
            files = files->next;
        }
    }
    return (0);
}
