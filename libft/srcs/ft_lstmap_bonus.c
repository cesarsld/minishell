/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjaimes <cjaimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:41:26 by cjaimes           #+#    #+#             */
/*   Updated: 2019/10/21 17:16:47 by cjaimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;
	t_list	*new1;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	data = f(lst->content);
	if (!(new = ft_lstnew(data)))
		return (NULL);
	first = new;
	lst = lst->next;
	while (lst)
	{
		data = f(lst->content);
		if (!(new1 = ft_lstnew(data)))
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		new->next = new1;
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
