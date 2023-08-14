/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:04:04 by ykhayri           #+#    #+#             */
/*   Updated: 2022/10/09 16:48:09 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_str(const char *s, unsigned char c, int l)
{
	if (!c)
		return (l);
	while (l >= 0)
	{
		if (s[l] == c)
			return (l);
		l--;
	}
	return (-1);
}

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				j;
	unsigned char	t;

	i = 0;
	t = c;
	j = is_in_str(s, t, ft_strlen(s));
	if (j >= 0)
	{
		s += j;
		return ((char *)s);
	}
	return (0);
}
