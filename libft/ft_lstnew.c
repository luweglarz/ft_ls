#include "libft.h"

t_list      *ft_lstnew(void *content){
    t_list *new_elem;

    if (!(new_elem = ft_calloc(1, sizeof(t_list))))
        return NULL;
    new_elem->content = content;
    new_elem->next = NULL;
    return new_elem;
}