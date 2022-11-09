#include "test.h"

void fatal_error(int custom_error){
    if (custom_error == -1){
        dprintf(2, "Error: %s\n", strerror(errno));
        exit(errno);
    }
    if (custom_error == BAD_ARG){
        write(2, "Error: Wrong number of argument: Format: ./tests [-Rartl] [root]\n", 66);
        exit(custom_error);
    }
}

char *get_dir_path(int ac, char **av){
	char *static_path;
	char *dir_path;

	if (ac == 2)
		static_path = av[1];
	else
		static_path = av[2];
	if (static_path[0] == '.' && static_path[1] == '\0')
		dir_path = ft_strdup("./");
	else if (static_path[ft_strlen(static_path) - 1] != '/')
		dir_path = ft_strjoin(static_path, "/");
	else
		dir_path = ft_strdup(static_path);
	return (dir_path);
}

static void    free_split(int words, char **tabword){
	int	i;

	i = 0;
	while (i < words)
	{
		free(tabword[i]);
		i++;
	}
	free(tabword);
}

char *get_cmd_path(char **envp, const char *cmd){
    char            **paths;
    char            *ret;
    int             i = 0;
    struct stat     buf;

    while (envp[i]){
        if(ft_strncmp(envp[i], "PATH=", 5) == 0)
            paths = ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5), ':');
        i++;
    }
    i = 0;
    while (paths[i]){
        paths[i] = ft_strjoin(paths[i], cmd);
        if (stat(paths[i], &buf) == 0)
            return paths[i];
        i++;
    }
    ret = ft_strdup(paths[i]);
    free_split(i, paths);
    return (ret);
}

char *get_ft_ls_path(){
    char cwd[256];
    char *ft_ls_path;

    bzero(&cwd, sizeof(cwd));
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (NULL);
    ft_ls_path = ft_strjoin(cwd, "/ft_ls");
    return (ft_ls_path);
}

void reset_args(char **args){
    int i = 1;
    while (i < 64){
        args[i] = NULL;
        i++;
    }
}