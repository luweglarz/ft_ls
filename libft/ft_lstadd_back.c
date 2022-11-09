#include "libft.h"\

void ft_lstadd_back(t_list **list, t_list *new_elem){
    t_list *tmp_list = *list;

    if (!*list)
        *list = new_elem;
    else{
        while(tmp_list->next)
            tmp_list = tmp_list->next;
        tmp_list->next = new_elem;
    }
}
