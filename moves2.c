/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 21:46:44 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 17:48:04 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	move_switch(t_game *game, int keycode)
{
	if (in_m(keycode) == 'r' && next_p(game, "xr"))
		game->active = 'r';
	else if (in_m(keycode) == 'l' && next_p(game, "xl"))
		game->active = 'l';
	else if (in_m(keycode) == 't' && next_p(game, "yt"))
		game->active = 't';
	else if (in_m(keycode) == 'b' && next_p(game, "yb"))
		game->active = 'b';
}

void	link_is_dead(t_game *game)
{
	if (game->fps - game->wait >= 10000)
	{
		if (game->tries > 0)
		{
			game->tries--;
			game->wait = 0;
			game->link->drawn = 0;
			game->link->life = 20;
			game->link->dead = 0;
			game->key = -1;
		}
		if (game->tries - 1 == -1 && game->wait == 0)
			game->wait = game->fps;
		if (((game->fps - game->wait) % 40000) && game->link->life == 0)
			close_win(game);
	}
}

void	put_dead(t_game *g)
{
	if (MODE == 1)
	{
		if (g->link->life > 0)
			mlx_put_image_to_window(g->mlx->mlx,
				g->mlx->mlx_win, g->mlx->pl[0], 32, 6);
		else
			mlx_put_image_to_window(g->mlx->mlx,
				g->mlx->mlx_win, g->mlx->pl[1], 35, 6);
		mlx_put_image_to_window(g->mlx->mlx,
			g->mlx->mlx_win, g->mlx->num[10], 62, 6);
		if (g->tries > -1)
			mlx_put_image_to_window(g->mlx->mlx,
				g->mlx->mlx_win, g->mlx->num[g->tries], 82, 6);
	}
}

int	space_empty(t_map *mlx, int i, int j)
{
	int	total;

	total = 4;
	if (mlx->map[j - 1][i] == WL)
		total--;
	if (mlx->map[j + 1][i] == WL)
		total--;
	if (mlx->map[j][i - 1] == WL)
		total--;
	if (mlx->map[j][i + 1] == WL)
		total--;
	return (total);
}

void	coll_animation(t_game *game)
{
	if (MODE == 1)
	{
		if (game->mlx->anm_sp == 16)
			game->mlx->add = 1;
		if (game->mlx->anm_sp == -8)
			game->mlx->add = 0;
		if (game->mlx->add)
			game->mlx->anm_sp -= 1;
		else
			game->mlx->anm_sp += 1;
	}
}
