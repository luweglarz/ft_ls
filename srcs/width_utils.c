#include "../includes/ft_ls.h"

size_t	count_digit(size_t number){
	size_t cnt = 0;

	while (number){
		number /= 10;
		cnt++;
	}
	return (cnt);
}

void get_width(t_file *files, size_t *size_max, size_t *hard_links_max){
	t_file		*tmp_files 		= files;
	size_t		max_size		= 0;
	size_t		max_hard_links	= 0;

	while(tmp_files){
		max_size = count_digit(tmp_files->size);
		if (max_size > *size_max)
			*size_max = max_size;
		max_hard_links = count_digit(tmp_files->hard_links);
		if (max_hard_links > *hard_links_max)
			*hard_links_max = max_hard_links;
		tmp_files = tmp_files->next;
	}
}