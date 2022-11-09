#include "test.h"

static int simple_cases(t_list *files, char **ls_args, char **ft_ls_args, char **envp){
    int     ret = 0;
    int     i = 1;
    t_list  *tmp_files = files;

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

static int simple_error_cases(t_list *files, char **ls_args, char **ft_ls_args, char **envp){
    int     ret = 0;
    t_list  *tmp_files = files;

    ls_args[1] = ft_strdup("@*#!");
    ret += execute_compare(ls_args, ft_ls_args, envp);
    ls_args[2] = ft_strdup(";fw:");
    ret += execute_compare(ls_args, ft_ls_args, envp);
    if (tmp_files)
        ls_args[3] = (char*)tmp_files->content;
    ret += execute_compare(ls_args, ft_ls_args, envp);
    tmp_files = tmp_files->next;
    ls_args[4] = ft_strdup("P[eq]");
    ret += execute_compare(ls_args, ft_ls_args, envp);
    if (tmp_files)
        ls_args[5] = (char*)tmp_files->content;
    ret += execute_compare(ls_args, ft_ls_args, envp);
    free(ls_args[1]);
    free(ls_args[2]);
    free(ls_args[4]);
    reset_args(ls_args);
    reset_args(ft_ls_args);
    return (ret);
}

void simple_tests(t_list *files, char **ls_args, char **ft_ls_args, char **envp){
    printf("Simple test cases:\n");
    printf("simple cases: %d/%d\n", simple_cases(files, ls_args, ft_ls_args, envp), ft_lstsize(files));
    printf("simple error cases: %d/%d\n", simple_error_cases(files, ls_args, ft_ls_args, envp), 5);
}