#include "../includes/ft_ls.h"

void fatal_error(){
    char    *error_msg = ft_strjoin("Error: ", strerror(errno));

    write(2, error_msg, strlen(error_msg));
    free(error_msg);
    exit(errno);
}