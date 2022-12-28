#include "../../includes/ft_ls.h"

bool alphabetic_compare(char *s1, char *s2){
    int i = 0;
    int j = 0;
    
    if ((s1[0] == '.' && s1[1] == '\0') && (s2[0] == '.' && s2[1] == '.' && s2[2] == '\0'))
        return (false);
    else if ((s1[0] == '.' && s1[1] == '.' && s1[2] == '\0') && (s2[0] == '.' && s2[1] == '\0'))
        return (true);
    while(s1[i] && s2[j]){
        if (s1[i] != s2[j])
            break ;
        i++;
        j++;
    }
    return (s1[i] > s2[j]);
}

bool time_compare(struct stat file1, struct stat file2){
    return (file1.st_mtime < file2.st_mtime);
}