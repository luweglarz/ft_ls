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
        t_file *tmp_files = files;

        if (has_file(tmp_files)){
            while(tmp_files){
                if (tmp_files->isdir == false){
                    t_format format;

                    get_width(tmp_files, &format);
                    print_file(tmp_files, format, opts);
                }
                tmp_files = tmp_files->next;
            }
            if (has_dir(files))
                ft_printf("\n");
        }
        tmp_files = files;
        while(tmp_files){
            if (tmp_files->isdir == true){
                if (opts & R)
                    print_dir_recur(tmp_files, opts);
                else
		            print_dir(tmp_files, opts, false);
                if (tmp_files->next != NULL)
                    ft_printf("\n");
            }
            tmp_files = tmp_files->next;
        }
        free_files(files);
    }
    return (0);
}
