#include "includes/ft_ls.h"

int main(int ac, char **av){
    e_options   opts = 0;
    t_file      *files = NULL;
	t_file		*tmp_files = NULL;

    if (ac > 1)
        get_files_opts(ac, av, &files, &opts);
    if (ac == 1 || (files == NULL && ac == 1) || count_files(files) == 1){
        if (files == NULL || ft_strncmp(files->name, "./", 3) == 0)
            files = init_file(".");
		print_dir(files, opts, true);
	}
    free_files(files);
    return (0);
}
