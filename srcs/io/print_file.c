#include "ft_ls.h"

void    print_file(t_file *file, t_format *format, e_options opts){
    if (opts & l)
	    print_long_format(file, format);
    else
        printf("%s\n", file->name);
}