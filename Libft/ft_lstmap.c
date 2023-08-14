/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:24:50 by ykhayri           #+#    #+#             */
/*   Updated: 2022/10/09 18:04:39 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *))
{
	t_list	*l;
	t_list	*k;

	if (!lst)
		return (NULL);
	k = ft_lstnew(f(lst -> content));
	lst = lst -> next;
	while (lst)
	{
		l = ft_lstnew(f(lst -> content));
		if (!l)
			ft_lstclear(&k, del);
		ft_lstadd_back(&k, l);
		lst = lst -> next;
	}
	return (k);
}
