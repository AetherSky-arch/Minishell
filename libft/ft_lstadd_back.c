/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:23:40 by arguez            #+#    #+#             */
/*   Updated: 2024/02/08 16:02:22 by arguez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *added)
{
	t_list	*current;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = added;
	else
	{
		current = ft_lstlast(*(lst));
		current->next = added;
	}
}
