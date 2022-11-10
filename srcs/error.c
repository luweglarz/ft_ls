#include "../includes/ft_ls.h"

void fatal_error(){
    dprintf(2, "Error: %s\n", strerror(errno));
        exit(errno);
}