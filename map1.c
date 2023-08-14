/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:00:47 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 18:12:27 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	put_wall(t_map *m, int i, int j)
{
	if (j == 0 && i == 0)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->corn[3], i * PX, j * PX);
	else if (j == 0 && i == m->dim[0] - 1)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->corn[1], i * PX, j * PX);
	else if (j == m->dim[1] - 1 && i == m->dim[0] - 1)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->corn[2], i * PX, j * PX);
	else if (j == m->dim[1] - 1 && i == 0)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->corn[0], i * PX, j * PX);
	else if (j < m->dim[1] - 1 && j > 0 && i == 0)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->wall[0], i * PX, j * PX);
	else if (j < m->dim[1] - 1 && j > 0 && i == m->dim[0] - 1)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->wall[2], i * PX, j * PX);
	else if (i < m->dim[0] - 1 && i > 0 && j == m->dim[1] - 1)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->wall[3], i * PX, j * PX);
	else if (i < m->dim[0] - 1 && i > 0 && j == 0)
		mlx_put_image_to_window(m->mlx, m->mlx_win, m->wall[1], i * PX, j * PX);
	else if (space_empty(m, i, j) > 2)
		mlx_put_image_to_window(m->mlx, m->mlx_win,
			m->fire[m->f / 2], i * PX, j * PX);
	else
		mlx_put_image_to_window(m->mlx, m->mlx_win,
			m->floor[0], i * PX, j * PX);
}

void	part1(char **map, t_map *mlx, t_player *l, int i[4])
{
	if (i[x] % 2 && MODE == 1)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->floor[1], i[x] * PX, i[y] * PX);
	else if (MODE == 1)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->floor[2], i[x] * PX, i[y] * PX);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->tmp[1], i[x] * PX, i[y] * PX);
	if (MODE == 1 && map[i[y]][i[x]] == WL)
		put_wall(mlx, i[x], i[y]);
	else if (map[i[y]][i[x]] == WL)
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->tmp[0], i[x] * PX, i[y] * PX);
	if (map[i[y]][i[x]] == CO)
	{
		if (++i[c] == mlx->max_sc)
			position_m(mlx->key, i[x], i[y]);
		if (mlx->key[y] == i[y] && mlx->key[x] == i[x]
			&& MODE == 1 && l->score == mlx->t_sc - 1)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				mlx->coll[0], i[x] * PX + 20, i[y] * PX + 16 - mlx->anm_sp);
	}
}

void	part2(t_map *mlx, t_player *link, int i[4])
{
	if (mlx->map[i[y]][i[x]] == EX)
	{
		i[3] = face_way(mlx, i[x], i[y]);
		if (link->score == mlx->t_sc)
		{
			if (++link->drawn == 2)
				run_mus("afplay sounds/door.wav");
			mlx->d_pos[x] = i[x];
			mlx->d_pos[y] = i[y] * PX;
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				mlx->door_o[i[3]], i[x] * PX, i[y] * PX);
		}
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				mlx->door_c[i[3]], i[x] * PX, i[y] * PX);
	}
	if (mlx->map[i[y]][i[x]] == PL && link->drawn == 0)
	{
		position_m(link->pos, i[x] * PX, i[y] * PX);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			link->ld[0], link->pos[0], link->pos[1]);
		link->drawn++;
	}
}

void	part3(char **map, t_map *mlx, t_game *game, int i[4])
{
	if (map[i[y]][i[x]] == CO && i[c] < mlx->max_sc && MODE && game->p_n)
	{
		if (i[c] % 2 && (map[i[y]][i[x] - 1] == SP
			|| map[i[y]][i[x] + 1] == SP))
		{
			ft_enmadd_back(&game->skull, 3, 8, i);
			mlx->t_sc++;
		}
		else if (map[i[y]][i[x] - 1] == SP || map[i[y]][i[x] + 1] == SP)
		{
			ft_enmadd_back(&game->skull, 3, -8, i);
			mlx->t_sc++;
		}
	}
	else if (map[i[y]][i[x]] == CO && i[c] == mlx->max_sc && MODE && game->p_n)
	{
		ft_enmadd_back(&game->skull, 5, 8, i);
		game->p_n = 0;
		mlx->t_sc++;
	}
}

void	fill_map(char **map, t_map *mlx, t_player *link, t_game *game)
{
	int	i[4];

	i[y] = -1;
	i[c] = 0;
	while (++i[y] < mlx->dim[1])
	{
		i[x] = -1;
		while (++i[x] < mlx->dim[0])
		{
			part1(map, mlx, link, i);
			part2(mlx, link, i);
			if (MODE == 1)
				part3(map, mlx, game, i);
			if (map[i[y]][i[x]] == CO && ((MODE && (mlx->key[y] != i[y]
				|| mlx->key[x] != i[x])) || !MODE))
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					mlx->coll[1], i[x] * PX + 20,
					i[y] * PX + 16 - mlx->anm_sp);
			if (link->life == 0 && game->tries <= 0)
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
					game->dark, i[x] * PX, i[y] * PX);
		}
	}
	put_hearts(mlx, link);
}
