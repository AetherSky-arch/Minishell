/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: arguez <marvin@42.fr>			    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2023/11/10 14:45:24 by arguez	       #+#    #+#	      */
/*   Updated: 2023/11/13 19:17:16 by arguez           ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*start;

	if ((!lst) || (!f) || (!del))
		return (0);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	start = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (start);
}
