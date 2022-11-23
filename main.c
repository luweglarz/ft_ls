#include "includes/ft_ls.h"

int main(int ac, char **av){
    e_options   opts = 0;
    t_file      *files = NULL;

    if (ac > 1)
        get_files_opts(ac, av, &files, &opts);
    if (count_files(files) == 0 || (count_files(files) == 1 && files->isdir == true)){
        if (files == NULL || ft_strncmp(files->name, "./", 3) == 0)
            files = init_file(".", ".");
        if (opts & R)
            print_dir_recur(files, opts);
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
