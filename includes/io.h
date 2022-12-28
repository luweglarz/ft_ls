#ifndef IO_H
# define IO_H

typedef struct  s_format{
    int  size_width;
    int  hard_links_width;
    int  user_name_width;
    int  user_group_width;
}               t_format;

void    print_long_format(t_file *file, t_format *format);

void	print_dir(t_file *dir, e_options opts, bool root);
void	print_dir_recur(t_file *dir, e_options opts);
void    print_file(t_file *file, t_format *format, e_options opts);

size_t	count_digit(size_t number);
void    get_width(t_file *files, t_format *format);

bool    is_past_six_month(int file_month, int file_year);
int     get_month_number(char *month);

#endif