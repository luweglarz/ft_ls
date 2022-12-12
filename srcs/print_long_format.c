#include "../includes/ft_ls.h"

static char get_type(mode_t perms){
    if (S_ISBLK(perms))
        return ('b');
    else if (S_ISCHR(perms))
        return ('c');
    else if (S_ISDIR(perms))
        return ('d');
    else if (S_ISFIFO(perms))
        return ('f');
    else if (S_ISLNK(perms))
        return ('l');
    else if (S_ISSOCK(perms))
        return ('s');
    return ('-');
}

static void print_perm(mode_t perms){
    char chmod[11];

    chmod[0] = get_type(perms);
    chmod[1] = (S_IRUSR & perms) ? 'r' : '-';
	chmod[2] = (S_IWUSR & perms) ? 'w' : '-';
	chmod[3] = (S_IXUSR & perms) ? 'x' : '-';
	chmod[4] = (S_IRGRP & perms) ? 'r' : '-';
	chmod[5] = (S_IWGRP & perms) ? 'w' : '-';
	chmod[6] = (S_IXGRP & perms) ? 'x' : '-';
	chmod[7] = (S_IROTH & perms) ? 'r' : '-';
	chmod[8] = (S_IWOTH & perms) ? 'w' : '-';
	chmod[9] = (S_IXOTH & perms) ? 'x' : '-';
    chmod[10] = '\0';
    ft_printf("%-11s", chmod);
}

static void print_user_n_group(uid_t user_id, gid_t group_id){
    struct passwd *user_infos;
    struct group  *group_infos;

    user_infos = getpwuid(user_id);
    group_infos = getgrgid(group_id);
    ft_printf("%s %s ", user_infos->pw_name, group_infos->gr_name);
}

static void print_time(char *time_stamp){
    char *correct_format;
    int start = 0;
    int end = ft_strlen(time_stamp) - 1;

    while(time_stamp[start] != ' ')
        start++;
    while(time_stamp[end] != ':')
        end--;
    correct_format = ft_substr(time_stamp, start,ft_strlen(time_stamp) + 1 - (end - start));
    ft_printf("%s ", correct_format);
    free(correct_format);
}

void    print_long_format(t_file *file, size_t size_max, size_t hard_links_max){
    struct stat file_infos;

    if (lstat(file->path, &file_infos) < 0)
        fatal_error();
    print_perm(file_infos.st_mode);
    ft_printf("%*d ", hard_links_max, file->hard_links);
    print_user_n_group(file_infos.st_uid, file_infos.st_gid);
    ft_printf("%*d", size_max, file->size);
    print_time(ctime(&file_infos.st_mtime));
    ft_printf("%s\n", file->name);
}