/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 23:11:53 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 16:16:26 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	has_c(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			j++;
		i++;
	}
	return (j);
}

int	is_ber(char *s)
{
	int	len;
	int	v;

	len = ft_strlen(s);
	v = 0;
	if (len > 4)
	{
		if (s[len - 4] == '.')
			v++;
		if (s[len - 3] == 'b')
			v++;
		if (s[len - 2] == 'e')
			v++;
		if (s[len - 1] == 'r')
			v++;
	}
	if (v != 4)
		print_info("Error:\nInvalid file name!", -1);
	return (v);
}

int	is_invalid(char *map)
{
	int	i;

	i = 0;
	if (has_c(map, CO) == 0 || has_c(map, PL) != 1
		|| has_c(map, EX) != 1 || has_c(map, WL) < 1)
		i++;
	return (i);
}

char	**read_map(t_map *m, int fd)
{
	char	*map;
	char	*tmp;

	tmp = get_next_line(fd);
	if (tmp == 0)
		return (0);
	map = "";
	position_m(m->dim, (int) ft_strlen(tmp) - 1, 0);
	while (tmp != 0)
	{
		if ((tmp[m->dim[0]] == '\n' && (int) ft_strlen(tmp) - m->dim[0] != 1)
			|| (tmp[m->dim[0]] != '\n' && (int) ft_strlen(tmp) - m->dim[0] != 0)
			|| m->dim[0] < 3)
			return (0);
		map = ft_strjoin(map, tmp);
		tmp = get_next_line(fd);
		m->dim[1]++;
	}
	free(tmp);
	m->max_sc = has_c(map, CO);
	m->t_sc += has_c(map, CO);
	if (m->dim[1] < 3 || is_invalid(map) > 0)
		return (0);
	return (ft_split(map, '\n'));
}

int	refr(t_game *game)
{
	if (!(game->fps % ANM))
	{
		coll_animation(game);
		refill(game);
		if ((game->mlx->dim[x] * 64 != 1664
				|| game->mlx->dim[y] * 64 != 1152) && !game->start)
			game->start = 1;
		if (game->start)
		{
			if (game->skull && MODE == 1)
			{
				ft_enmiter(game->skull, game);
			}
			start_the_game(game);
		}
	}
	game->fps++;
	return (0);
}
