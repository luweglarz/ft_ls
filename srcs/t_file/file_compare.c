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

bool time_compare(t_file *file1, t_file *file2){
    if (file1->file_infos.st_mtim.tv_sec == file2->file_infos.st_mtim.tv_sec){
        if (file1->file_infos.st_mtim.tv_nsec == 0 || file2->file_infos.st_mtim.tv_nsec == 0)
            return (alphabetic_compare(file1->name, file2->name));
        return (file1->file_infos.st_mtim.tv_nsec < file2->file_infos.st_mtim.tv_nsec);
    }
    return (file1->file_infos.st_mtim.tv_sec < file2->file_infos.st_mtim.tv_sec);
}