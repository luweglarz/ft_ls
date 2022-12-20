#include "../includes/ft_ls.h"

int  get_month_number(char *month){
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

bool is_past_six_month(int file_month, int file_year){
    int actual_month, actual_year;
    time_t  actual_time;
    char    **actual_split;

    actual_time = time(&actual_time);
    actual_split = ft_split(ctime(&actual_time), ' ');
    actual_month = get_month_number(actual_split[1]);
    actual_year = ft_atoi(actual_split[4]);
    ft_free_split(actual_split);
    if ((actual_month - file_month + (actual_year - file_year) * 12) > 6)
        return (true);
    return (false);
}