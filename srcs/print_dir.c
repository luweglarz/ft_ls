#include "../includes/ft_ls.h"

static void	read_stream(t_file **files, t_file *dir, e_options opts){
	char			new_path[PATH_MAX];
	DIR 			*dir_stream = opendir(dir->path);
	struct dirent 	*file_ptr = NULL;

	while((file_ptr = readdir(dir_stream)) != NULL){
		if ((opts & t && (opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & t && (opts & a) > 0))){
			ft_strncpy(new_path, dir->path, ft_strlen(dir->path));
			ft_strncat(new_path, "/", 1);
			ft_strncat(new_path, file_ptr->d_name, ft_strlen(file_ptr->d_name));
			fileadd_by_time(files, file_ptr->d_name, new_path, opts & r);
		}
		else if (((opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & a) > 0)){
			ft_strncpy(new_path, dir->path, ft_strlen(dir->path));
			ft_strncat(new_path, "/", 1);
			ft_strncat(new_path, file_ptr->d_name, ft_strlen(file_ptr->d_name));
			fileadd_by_alpha(files, file_ptr->d_name, new_path, opts & r);
		}
	}
}

void	print_dir_recur(t_file *dir, e_options opts){
	t_file			*files = NULL;
	t_file			*dirs = NULL;
	t_file 			*file_to_del = NULL;

	if (dir == NULL)
		return ;
	ft_printf("%s:\n", dir->path);
	read_stream(&files, dir, opts);

	while(files){
		ft_printf("%s  ", files->name);
		if (files->isdir == true)
			fileadd_by_alpha(&dirs, files->name, files->path, opts & r);
		file_to_del = files;
		files = files->next;
		free(file_to_del);
	}
	ft_printf("\n\n");

	while(dirs){
		print_dir_recur(dirs, opts);
		dirs = dirs->next;
	}
}

void	print_dir(t_file *dir, e_options opts, bool root){
	t_file			*files = NULL;
	t_file 			*file_to_del = NULL;

	if (root == false)
		ft_printf("%s:\n", dir->path);
	read_stream(&files, dir, opts);
	
	while(files){
		ft_printf("%s  ", files->name);
		file_to_del = files;
		files = files->next;
		free(file_to_del);
	}
	ft_printf("\n");
	free(dir);
}