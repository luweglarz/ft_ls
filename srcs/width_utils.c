#include "../includes/ft_ls.h"

size_t	count_digit(size_t number){
	size_t cnt = 0;

	while (number){
		number /= 10;
		cnt++;
	}
	return (cnt);
}

void get_width(t_file *files, t_format *format){
	t_file			*tmp_files 		= files;
	int				max_size		= 0;
	int				max_hard_links	= 0;
	struct passwd 	*user_infos;
    struct group  	*group_infos;

	format->hard_links_width = 0;
	format->size_width = 0;
	format->user_group_width = 0;
	format->user_name_width = 0;
	while(tmp_files){
		max_size = count_digit(tmp_files->file_infos.st_size);
		if (max_size > format->size_width)
			format->size_width = max_size;
		max_hard_links = count_digit(tmp_files->file_infos.st_nlink);
		if (max_hard_links > format->hard_links_width)
			format->hard_links_width = max_hard_links;
		user_infos = getpwuid(tmp_files->file_infos.st_uid);
		if ((int)ft_strlen(user_infos->pw_name) > format->user_name_width)
			format->user_name_width = (int)ft_strlen(user_infos->pw_name);
		group_infos = getgrgid(tmp_files->file_infos.st_gid);
		if ((int)ft_strlen(group_infos->gr_name) > format->user_group_width)
			format->user_group_width = (int)ft_strlen(group_infos->gr_name);
		tmp_files = tmp_files->next;
	}
}