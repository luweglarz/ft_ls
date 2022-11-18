#include "../includes/ft_ls.h"

void	print_dir(t_file *file, e_options opts, bool root){
	DIR 			*dir = opendir(file->path);
	struct dirent 	*file_ptr = NULL;
	t_file			*files = NULL;

	if (root == true){
		while((file_ptr = readdir(dir)) != NULL){
			if ((opts & t && (opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & t && (opts & a) > 0)))
				fileadd_by_time(&files, file_ptr->d_name, opts & r);
			else if (((opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & a) > 0))
				fileadd_by_alpha(&files, file_ptr->d_name, opts & r);
		}
		t_file *tmp_files = NULL;
		while(files){
			ft_printf("%s  ", files->name);
			tmp_files = files;
			free(tmp_files->name);
			files = files->next;
			free(tmp_files);
		}
		ft_printf("\n");
	}
	free(dir);
}
