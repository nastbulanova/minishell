/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:28:12 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/29 11:06:59 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*void	ft_del(char *lst)
{
	lst = 0;
}

int main()
{
    t_list  *list;
    t_list  *list1;
    t_list  *list2;
    t_list  *list3;
    t_list  *head;
    int i;
    char content[] = "Hey";
    head = list;
    
    ////////////// ft_lstnew
    printf("ft_lstnew\n");
    list1 = ft_lstnew(content);
    i = 0;
    char *content_str = (char *)(list1->content);
    while(content_str[i] != '\0')
    {
        printf("%c", content_str[i]);
        i ++;
    }
    printf("\n%p\n", list1->next);

    ////////////// ft_lstadd_front
    list = head;
    printf("ft_lstadd_front\n");
    ft_lstadd_front(&list, list1);
    while(list)
    {
        i = 0;
        char *content_str = (char *)(list->content);
        while(content_str[i] != '\0')
        {
            printf("%c", content_str[i]);
            i ++;
        }
        printf("\n%p\n", list->next);
        list = list->next;
    }

    ////////////// ft_lstsize
    list = head;
    printf("ft_lstsize\n");
    printf("Size = %d\n", ft_lstsize(&list));

    ////////////// ft_lstlast and ft_lstadd_back
    list = head;
    printf("ft_lstlast and ft_lstadd_back\n");
    list2->content = "Hello, added back";
	list2->next = NULL;
    ft_lstadd_back(&list, list2);
    while(list)
    {
        i = 0;
        char *content_str = (char *)list->content;
        while(content_str[i] != '\0')
        {
            printf("%c", content_str[i]);
            i ++;
        }
        printf("\n%p\n", list->next);
        list = list->next;
    }

    //////////// ft_lstdelone
    list = head;
    printf("ft_lstdelone\n");
    ft_lstdelone(list, ()); //// что здесь?
    while(list)
    {
        i = 0;
        char *content_str = (char *)list->content;
        while(content_str[i] != '\0')
        {
            printf("%c", content_str[i]);
            i ++;
        }
        printf("\n%p\n", list->next);
        list = list->next;
    }

}*/
