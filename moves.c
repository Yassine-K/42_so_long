/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:38:00 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/20 18:08:44 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	play_an_help(t_game *game, char op[3], int k, int i)
{
	if (op[0] == 'a')
	{
		game->link->pos[i] += MV;
		if (op[1] == 'r' && MODE == 1)
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
				game->link->lr[k], game->link->pos[0], game->link->pos[1]);
		else if (MODE == 1)
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
				game->link->ld[k], game->link->pos[0], game->link->pos[1]);
	}
	else
	{
		game->link->pos[i] -= MV;
		if (op[1] == 'l' && MODE == 1)
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
				game->link->ll[k], game->link->pos[0], game->link->pos[1]);
		else if (MODE == 1)
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
				game->link->lt[k], game->link->pos[0], game->link->pos[1]);
	}
	if (MODE != 1)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->ld[0], game->link->pos[0], game->link->pos[1]);
}

void	play_an(t_game *game, char op[3])
{
	int	k;

	game->active = op[1];
	k = game->ann;
	game->last_sp = op[1];
	game->prev_att = op[1];
	play_an_help(game, op, k, op[2] - 48);
	check_coll(game, op);
	game->ann++;
	if (game->ann == 11)
		game->ann = 1;
	game->moves++;
	print_info("Moves:", game->moves);
}

int	key_up(int keycode, t_game *game)
{
	game->ann = 1;
	if (keycode != 49 && in_m(keycode) == game->active)
		game->active = 0;
	if (in_m(keycode) && keycode != 49)
		game->prev_att = in_m(keycode);
	game->key = keycode;
	return (0);
}

int	next_p(t_game *g, char *c)
{
	int	k[3];

	k[x] = (g->link->pos[x] - 16 - (g->link->pos[x] - 16) % 64) / 64;
	k[y] = (48 + g->link->pos[y] - (48 + g->link->pos[y]) % 64) / 64;
	if (c[1] == 't' || c[1] == 'b')
	{		
		k[x] = (32 + g->link->pos[x] - (32 + g->link->pos[x]) % 64) / 64;
		k[2] = g->link->pos[x] / 64;
	}
	if (c[1] == 'r')
		k[x] = (57 + g->link->pos[x] - (57 + g->link->pos[x]) % 64) / 64;
	if (c[1] == 't')
		k[y] = (g->link->pos[y] - (g->link->pos[y]) % 64) / 64;
	if (c[1] == 'b')
		k[y] = (16 + g->link->pos[y] + 16
				+ (16 + g->link->pos[y] + 16) % 64) / 64;
	if (c[1] != 't' && c[1] != 'b')
		k[2] = k[x];
	if (g->mlx->map[(k[y])][k[x]] != WL && g->mlx->map[(k[y])][k[2]] != WL)
		return (1);
	g->active = 0;
	if (g->link->life > 0)
		just_wait(g, in_m(g->key));
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	game->key = keycode;
	if (keycode == ESC)
		close_win(game);
	game->active = 0;
	if (game->link->fall == -1 && game->start)
		move_switch(game, keycode);
	if (keycode == 49)
	{
		game->link->state = 'a';
		game->active = 1;
	}
	else
	{
		game->link->state = 'n';
		game->link->att = 0;
	}
	if (keycode == 36 && !game->start && game->fps >= ANM * 260)
	{
		game->start = 1;
		run_mus("afplay sounds/sel.wav");
	}
	return (keycode);
}
