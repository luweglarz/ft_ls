#include "ft_ls.h"

bool alphabetic_compare(char *s1, char *s2){
    if (ft_strcmp(s1, s2) < 0)
        return (false);
    return (true);
}

bool time_compare(t_file *file1, t_file *file2){
    if (file1->file_infos.st_mtim.tv_sec == file2->file_infos.st_mtim.tv_sec){
        if (file1->file_infos.st_mtim.tv_nsec == 0 || file2->file_infos.st_mtim.tv_nsec == 0 ||
            file1->file_infos.st_mtim.tv_nsec == file2->file_infos.st_mtim.tv_nsec)
            return (alphabetic_compare(file1->name, file2->name));
        return (file1->file_infos.st_mtim.tv_nsec < file2->file_infos.st_mtim.tv_nsec);
    }
    return (file1->file_infos.st_mtim.tv_sec < file2->file_infos.st_mtim.tv_sec);
}