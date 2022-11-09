#ifndef TEST_H
# define TEST_H 

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../libft/libft.h"
#include "test.h"

#define BAD_ARG 1

//Utils
char    *get_dir_path(int ac, char **av);
char    *get_cmd_path(char **envp, const char *cmd);
char    *get_ft_ls_path();
void    fatal_error(int custom_error);
void    reset_args(char **args);

//Exec
int     execute_compare(char **ls_args, char **ft_ls_args, char **envp);

//Tests
void simple_tests(t_list *files, char **ls_args, char **ft_ls_args, char **envp);
void recursive_tests(t_list *files, char **ls_args, char **ft_ls_args, char **envp);

#endif