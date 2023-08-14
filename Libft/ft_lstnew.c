/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:30:07 by ykhayri           #+#    #+#             */
/*   Updated: 2022/10/11 20:05:54 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_n;

	new_n = (t_list *) malloc(sizeof(t_list));
	if (!new_n)
		return (0);
	if (!content)
		new_n -> content = NULL;
	else
		new_n -> content = content;
	new_n -> next = NULL;
	return (new_n);
}
