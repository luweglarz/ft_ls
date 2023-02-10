#include "ft_ls.h"

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
    if (S_ISUID & perms){
        if (S_IXUSR)
            chmod[3] = 'S';
        else
            chmod[3] = 's';
    }
    else
	    chmod[3] = (S_IXUSR & perms) ? 'x' : '-';

	chmod[4] = (S_IRGRP & perms) ? 'r' : '-';
	chmod[5] = (S_IWGRP & perms) ? 'w' : '-';
    if (S_ISGID & perms){
        if (S_IXUSR)
            chmod[6] = 'S';
        else
            chmod[6] = 's';
    }
    else
	    chmod[6] = (S_IXGRP & perms) ? 'x' : '-';

	chmod[7] = (S_IROTH & perms) ? 'r' : '-';
	chmod[8] = (S_IWOTH & perms) ? 'w' : '-';
    if (S_ISVTX & perms)
        chmod[9] = 't';
    else
	    chmod[9] = (S_IXGRP & perms) ? 'x' : '-';
    chmod[10] = '\0';
    printf("%-10s ", chmod);
    return (chmod[0]);
}

static void print_user_n_group(uid_t user_id, gid_t group_id, t_format *format){
    struct passwd *user_infos;
    struct group  *group_infos;

    user_infos = getpwuid(user_id);
    group_infos = getgrgid(group_id);
    if (user_infos && group_infos)
        printf("%-*s %-*s ", format->user_name_width, user_infos->pw_name, format->user_group_width, group_infos->gr_name);
    else{
        char *str_user_id = ft_itoa(user_id), *str_group_id = ft_itoa(group_id);
        printf("%s %s ", str_user_id, str_group_id);
        free(str_user_id);
        free(str_group_id);
    }
}

static void print_time(char *time_stamp){
    char **time_stamp_split = ft_split(time_stamp, ' ');

    printf("%s ", time_stamp_split[1]);
    printf("%2s ", time_stamp_split[2]);
    if (is_past_six_month(get_month_number(time_stamp_split[1]), ft_atoi(time_stamp_split[4])) == false)
        printf("%.5s ", time_stamp_split[3]);
    else{
        time_stamp_split[4][4] = '\0'; 
        printf(" %s ", time_stamp_split[4]);
    }
    ft_free_split(time_stamp_split);
}

static void print_device_type(char *major, char *minor, t_format *format){
    char *major_ext = ft_strjoin(major, ", ");
    char *major_minor = ft_strjoin(major_ext, minor);

    printf("%*s ",format->size_width,  major_minor);
    free(major_ext);
    free(major_minor);
    free(major);
    free(minor);
}

void    print_long_format(t_file *file, t_format *format){
    char        type;

    type = print_perm(file->file_infos.st_mode);
    printf("%*ld ", format->hard_links_width, file->file_infos.st_nlink);
    print_user_n_group(file->file_infos.st_uid, file->file_infos.st_gid, format);
    if (is_device(file) == true)
        print_device_type(ft_itoa(major(file->file_infos.st_rdev)), ft_itoa(minor(file->file_infos.st_rdev)), format);
    else
        printf("%*ld ", format->size_width, file->file_infos.st_size);
    print_time(ctime(&file->file_infos.st_mtime));
    if (type == 'l'){
        char sym_link[PATH_MAX];
        ssize_t link_string_length;
        
        link_string_length = readlink(file->path, sym_link, sizeof sym_link);
        sym_link[link_string_length] = '\0';
        printf("%s -> %s\n", file->name, sym_link);
    }
    else
        printf("%s\n", file->name);
}