#include "test.h"

int g_log_test_fd = 0;

void unit_tests(t_list *files, char **envp){
	char			*ls_args[64];
	char			*ft_ls_args[64];

	ls_args[0] = get_cmd_path(envp, "/ls");
	ft_ls_args[0] = get_ft_ls_path();
	simple_tests(files, ls_args, ft_ls_args, envp);
	recursive_tests(files, ls_args, ft_ls_args, envp);
}

int main(int ac, char **av , char **envp){
	char			*dir_path;
    DIR             *dir_stream;
    struct dirent   *dir_ptr;
	struct stat		arg_stat;
	t_list			*files = NULL;

    if (ac != 2)
		fatal_error(BAD_ARG);
    if (stat(av[1], &arg_stat) == -1)
		fatal_error(-1);
	dir_path = get_dir_path(ac, av);
	if(!(dir_stream = opendir(dir_path)))
		fatal_error(-1);
	dir_ptr = readdir(dir_stream);
    while(dir_ptr != NULL){
		ft_lstadd_back(&files, ft_lstnew(ft_strjoin(dir_path, dir_ptr->d_name)));
		dir_ptr = readdir(dir_stream);
    }
	unlink("test_ls.log");
	if (!(g_log_test_fd = open("test_ls.log", O_WRONLY | O_APPEND | O_CREAT, 0644)))
		fatal_error(errno);
	unit_tests(files, envp);
    return (0);
}