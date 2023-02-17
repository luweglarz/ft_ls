#include "ft_ls.h"

size_t	count_digit(size_t number){
	size_t cnt = 0;

	while (number){
		number /= 10;
		cnt++;
	}
	return (cnt);
}

static void	get_file_size_width(t_file *file, t_format *format){
	int	max_size	= 0;

	max_size = count_digit(file->file_infos.st_size);
	if (max_size > format->size_width)
		format->size_width = max_size;
}

static bool is_acl(t_file *file){
	if (listxattr(file->path, NULL, 0))
		return (true);
	return (false);
}

static void	get_device_size_width(t_file *file, t_format *format){
	int	major_size	= 0;
	int minor_size	= 0;
	int total_size	= 0;

	major_size = count_digit(major(file->file_infos.st_rdev));
	minor_size = count_digit(minor(file->file_infos.st_rdev));
	total_size = major_size + minor_size + 3;
	if (total_size > format->size_width)
		format->size_width = total_size;
}

void 	get_width(t_file *files, t_format *format){
	t_file			*tmp_files 		= files;
	int				max_hard_links	= 0;
	struct passwd 	*user_infos;
    struct group  	*group_infos;

	format->hard_links_width = 0;
	format->size_width = 0;
	format->user_group_width = 0;
	format->user_name_width = 0;
	format->perm_width = 11;
	while(tmp_files){
		if(is_device(tmp_files))
			get_device_size_width(tmp_files, format);
		else
			get_file_size_width(tmp_files, format);
		max_hard_links = count_digit(tmp_files->file_infos.st_nlink);
		if (max_hard_links > format->hard_links_width)
			format->hard_links_width = max_hard_links;
		user_infos = getpwuid(tmp_files->file_infos.st_uid);
		if (user_infos && (int)ft_strlen(user_infos->pw_name) > format->user_name_width)
			format->user_name_width = (int)ft_strlen(user_infos->pw_name);
		group_infos = getgrgid(tmp_files->file_infos.st_gid);
		if (group_infos && (int)ft_strlen(group_infos->gr_name) > format->user_group_width)
			format->user_group_width = (int)ft_strlen(group_infos->gr_name);
		if (is_acl(tmp_files))
			format->perm_width = 12;
		tmp_files = tmp_files->next;
	}
}