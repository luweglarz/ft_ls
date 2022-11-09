#include "test.h"

static int simple_recursive_cases(t_list *files, char **ls_args, char **ft_ls_args, char **envp){
    int     ret = 0;
    int     i = 3;
    t_list  *tmp_files = files;

    ls_args[2] = ft_strdup("-R");
    while(tmp_files){
        ls_args[i] = (char*)tmp_files->content;
        ft_ls_args[i] = (char*)tmp_files->content;
        ret += execute_compare(ls_args, ft_ls_args, envp);
        tmp_files = tmp_files->next;
        i++;
    }
    reset_args(ls_args);
    reset_args(ft_ls_args);
    return (ret);
}

void recursive_tests(t_list *files, char **ls_args, char **ft_ls_args, char **envp){
    printf("Recursive test cases:\n");
    printf("simple recursive cases: %d/%d\n", simple_recursive_cases(files, ls_args, ft_ls_args, envp), ft_lstsize(files));
}