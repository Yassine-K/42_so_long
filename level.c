/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:34:55 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 17:48:57 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_map(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->mlx->dim[1])
		free(g->mlx->map[i]);
	free(g->mlx->map);
}

void	fall_down(t_game *g)
{
	int	i;

	if (g->link->fall == 0)
		run_mus("afplay sounds/fall.wav");
	i = g->link->fall;
	position_m(g->link->pos, g->mlx->d_pos[x] * 64, g->mlx->d_pos[y]);
	mlx_put_image_to_window(g->mlx->mlx, g->mlx->mlx_win,
		g->link->lf[i], g->link->pos[0], g->link->pos[1]);
	g->link->fall++;
	if (g->link->fall == 6)
	{
		g->link->fall = -1;
		g->lvl++;
		ft_enmclear(&g->skull);
		g->p_n = 1;
		free_map(g);
		g->mlx->path[9] = g->lvl + 48;
		if (g->lvl < LV)
			g->mlx->map = read_map(g->mlx, open(g->mlx->path, O_RDONLY));
		else
			close_win(g);
		g->link->drawn = 0;
	}
}

void	load_maps(t_map *mlx, int fd, char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	mlx->t_sc = 0;
	len = ft_strlen("maps/map00.ber");
	while (s[i] == "maps/map00.ber"[i])
		i++;
	mlx->path = NULL;
	if (MODE == 1 && i - 1 == len && len == ft_strlen(s))
	{
		mlx->path = ft_strdup("maps/map00.ber");
		mlx->map = read_map(mlx, open(mlx->path, O_RDONLY));
	}
	else
		mlx->map = read_map(mlx, fd);
}

void	beat_him2(t_game *g, t_enm *skull, int p[2])
{
	if ((g->prev_att == 'l' && skull->adv > 0
			&& g->mlx->map[p[y]][(p[x] - 32) / 64] != WL)
			|| (g->prev_att == 'r' && skull->adv < 0
			&& g->mlx->map[p[y]][(p[x] + 32) / 64] != WL))
		skull->pos[x] += 32 * (skull->adv / 8);
	else if ((g->prev_att == 't' && ((p[y] - 16) / 64) - 1
			== g->link->pos[y] / 64) || (g->prev_att == 'b'
			&& ((p[y] + 80) / 64) - 1 == g->link->pos[y] / 64))
	{
		if (g->mlx->map[p[y]][(p[x] + 80) / 64] != WL)
			skull->pos[x] += 80;
		else if (g->mlx->map[p[y]][(p[x] - 80) / 64] != WL)
			skull->pos[x] -= 80;
	}
}

void	add_score(int k[2], t_game *g)
{
	g->mlx->map[k[y]][k[x]] = SP;
	g->link->score++;
	run_mus("afplay sounds/col.wav");
}
