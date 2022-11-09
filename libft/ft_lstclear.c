#include "libft.h"

void ft_lstclear(t_list **list, void (*del)(void*)){
    t_list *tmp_list = *list;

    if (list && del){
        while(*list){
            tmp_list = (*list)->next;
            (*del)((*list)->content);
            free(*list);
            *list = tmp_list;
        }
    }
}