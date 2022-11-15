#include "test.h"

extern int g_log_test_fd;

char *exec_fork(char **args, char **envp){
    int pipes[2];
    pid_t pid;
    char output[4096];

    bzero(&output, sizeof(output));
    if (pipe(pipes)==-1)
        fatal_error(errno);
    if ((pid = fork()) == -1)
        fatal_error(errno);
    if(pid == 0) {
        dup2 (pipes[1], STDOUT_FILENO);
		dup2 (pipes[1], STDERR_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        execve(args[0], args, envp);
        exit(errno);
    } else {
        close(pipes[1]);
        read(pipes[0], output, sizeof(output));
        waitpid(pid, NULL, 0);
        close(pipes[0]);
        return (ft_strdup(output));
    }
}

int execute_compare(char **ls_args, char **ft_ls_args, char **envp){
    char *ls_output;
    char *ft_ls_output;

    ls_output = exec_fork(ls_args, envp);
    ft_ls_output = exec_fork(ft_ls_args, envp);
    if (strcmp(ls_output, ft_ls_output) != 0){
        dprintf(g_log_test_fd, "Fail:\nls output: \n%s\nft_ls output: \n%s\n", ls_output, ft_ls_output);
        free(ls_output);
        free(ft_ls_output);
        return (0);
    }
    dprintf(g_log_test_fd, "Success:\nls output: \n%s\nft_ls output: \n%s\n", ls_output, ft_ls_output);
    free(ls_output);
    free(ft_ls_output);
    return (1);
}