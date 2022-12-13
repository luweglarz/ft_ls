#include "../includes/ft_ls.h"

void fatal_error(t_file *files){
    char    *error_msg = ft_strjoin("Error: ", strerror(errno));

    write(2, error_msg, strlen(error_msg));
    free(error_msg);
    free_files(files);
    exit(errno);
}