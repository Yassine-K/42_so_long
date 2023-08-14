/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:25:48 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 15:38:30 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	position_m(int pos[2], int x_p, int y_p)
{
	pos[0] = x_p;
	pos[1] = y_p;
}

void	initial_game(t_game *game)
{
	game->moves = 0;
	game->p_n = 0;
	game->e_k = 0;
	if (MODE == 1)
		game->p_n = 1;
	game->ann = 1;
	game->key = 125;
	game->active = 0;
	game->prev_att = 'b';
	game->start = 1;
	if (MODE == 1)
		game->start = 0;
	game->wait = 0;
	game->lvl = 0;
	game->intro = 0;
	game->tries = 3;
}

void	initial_link(t_player *link)
{
	link->score = 0;
	link->drawn = 0;
	link->att = 0;
	link->state = 'n';
	link->life = 20;
	link->dead = 0;
	link->fall = -1;
}

int	initial_map(t_map *mlx, char *s)
{
	int	fd;

	mlx->add = 1;
	mlx->b = 1;
	mlx->max_sc = 0;
	position_m(mlx->d_pos, 0, 0);
	if (is_ber(s) == 4)
	{
		fd = open(s, O_RDONLY);
		load_maps(mlx, fd, s);
	}
	else
		return (0);
	if (!mlx->map || !check_bord(mlx->map, mlx))
	{
		print_info("Error:\nInvalid map!", -1);
		return (0);
	}
	mlx->check = copy_map(mlx);
	if (!mlx->check)
		return (0);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->dim[0] * PX,
			mlx->dim[1] * PX, mlx->title);
	return (1);
}

int	face_way(t_map *mlx, int i, int j)
{
	int	total;

	total = 3;
	if (mlx->map[j][i + 1] != WL)
		total = 2;
	if (mlx->map[j - 1][i] != WL)
		total = 1;
	if (mlx->map[j][i - 1] != WL)
		total = 0;
	if (mlx->map[j + 1][i] != WL)
		total = 3;
	return (total);
}
