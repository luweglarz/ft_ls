#include "../includes/ft_ls.h"

void	print_dir(t_file *file, e_options opts, bool root){
	DIR 			*dir = opendir(file->path);
	struct dirent 	*file_ptr;
	t_file			*files;

	if (root == true){
		while((file_ptr = readdir(dir)) != NULL){
			if ((opts & t && (opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & t && (opts & a) > 0)))
				fileadd_by_time(&files, file_ptr->d_name, opts & r);
			else if (((opts & a) == 0 && file_ptr->d_name[0] != '.') || ((opts & a) > 0))
				fileadd_by_alpha(&files, file_ptr->d_name, opts & r);
		}
		while(files){
			printf("%s  ", files->name);
			files = files->next;
		}
		printf("\n");
	}
}