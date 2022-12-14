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

static char print_perm(mode_t perms){
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
    return (chmod[0]);
}

static void print_user_n_group(uid_t user_id, gid_t group_id){
    struct passwd *user_infos;
    struct group  *group_infos;

    user_infos = getpwuid(user_id);
    group_infos = getgrgid(group_id);
    ft_printf("%s %s ", user_infos->pw_name, group_infos->gr_name);
}

static int  get_month_number(char *month){
    if (ft_strncmp(month, "Jan", 3) == 0)
        return (1);
    if (ft_strncmp(month, "Feb", 3) == 0)
        return (2);
    if (ft_strncmp(month, "Mar", 3) == 0)
        return (3);
    if (ft_strncmp(month, "Apr", 3) == 0)
        return (4);
    if (ft_strncmp(month, "May", 3) == 0)
        return (5);
    if (ft_strncmp(month, "Jun", 3) == 0)
        return (6);
    if (ft_strncmp(month, "Jul", 3) == 0)
        return (7);
    if (ft_strncmp(month, "Aug", 3) == 0)
        return (8);
    if (ft_strncmp(month, "Sep", 3) == 0)
        return (9);
    if (ft_strncmp(month, "Oct", 3) == 0)
        return (10);
    if (ft_strncmp(month, "Nov", 3) == 0)
        return (11);
    return (12);
}

static bool past_six_month(int file_day, int file_month, int file_year){
    int actual_day, actual_month, actual_year;
    int diff_month = 0, diff_year = 0;
    time_t  actual_time;
    char    **actual_split;

    actual_time = time(&actual_time);
    actual_split = ft_split(ctime(&actual_time), ' ');
    actual_day = ft_atoi(actual_split[2]);
    actual_month = get_month_number(actual_split[1]);
    actual_year = ft_atoi(actual_split[4]);

    if ((actual_day - file_day) < 0)
        diff_month += 1;
    diff_month += actual_month - file_month;
    diff_year = actual_year - file_year;
    if ((diff_year >= 1) || (diff_year == 0 && diff_month >= 6))
        return (true);
    return (false);

}

static void print_time(char *time_stamp){
    char **time_stamp_split = ft_split(time_stamp, ' ');

    ft_printf("%s ", time_stamp_split[1]);
    ft_printf("%s ", time_stamp_split[2]);
    if (past_six_month(ft_atoi(time_stamp_split[2]), get_month_number(time_stamp_split[1]), ft_atoi(time_stamp_split[4])) == false)
        ft_printf("%.5s ", time_stamp_split[3]);
    else{
        time_stamp_split[4][4] = '\0'; 
        ft_printf("%s ", time_stamp_split[4]);
    }
    free(time_stamp_split);
}

void    print_long_format(t_file *file, size_t size_max, size_t hard_links_max){
    struct stat file_infos;
    char        type;

    if (lstat(file->path, &file_infos) < 0)
        fatal_error(file);
    type = print_perm(file_infos.st_mode);
    ft_printf("%*d ", hard_links_max, file->hard_links);
    print_user_n_group(file_infos.st_uid, file_infos.st_gid);
    ft_printf("%*d ", size_max, file->size);
    print_time(ctime(&file_infos.st_mtime));
    if (type == 'l'){
        char sym_link[PATH_MAX];
        ssize_t link_string_length;
        
        link_string_length = readlink(file->path, sym_link, sizeof sym_link);
        sym_link[link_string_length] = '\0';
        ft_printf("%s -> %s\n", file->name, sym_link);
    }
    else
        ft_printf("%s\n", file->name);
}