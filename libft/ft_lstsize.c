#include "libft.h"

int ft_lstsize(t_list *list){
    int    i = 0;
    t_list *tmp_list = list;

    while(tmp_list){
        tmp_list = tmp_list->next;
        i++;
    }
    return (i);
}