#include "../includes/ft_ls.h"

static char get_alpha(char c){
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

bool alphabetic_compare(char *s1, char *s2){
    int i = 0;
    int j = 0;

    while(s1[i] && s2[j]){
        while(ft_isalnum(get_alpha(s1[i])) == 0)
            i++;
        while(ft_isalnum(get_alpha(s2[j])) == 0)
            j++;
        if (get_alpha(s1[i]) != get_alpha(s2[j]))
            break ;
        i++;
        j++;
    }
    return (get_alpha(s1[i]) > get_alpha(s2[j]));
}

bool time_compare(char *s1, char *s2){
    struct stat     s1_stat;
    struct stat     s2_stat;
    
    if (stat(s1, &s1_stat) == -1)
        fatal_error();
    if (stat(s2, &s2_stat) == -1)
        fatal_error();
    return (s1_stat.st_ctime < s2_stat.st_ctime);
}