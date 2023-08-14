/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 23:32:26 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/16 19:12:12 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	put_hearts(t_map *mlx, t_player *link)
{
	int	i;

	i = -1;
	while (++i < 5 && MODE == 1)
	{
		if ((i * 5 < link->life || link->life - i * 5 == 0
				|| i * 5 == link->life) && link->life > 0)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				link->h[0], 124 + 32 * i, 6);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
				link->h[1], 124 + 32 * i, 6);
	}
}

void	put_moves(t_map *mlx, int moves)
{
	int	s;
	int	pos[2];
	int	i;
	int	div;
	int	dis;

	pos[y] = (mlx-> dim[y] - 1) * 64 + 40;
	pos[x] = (mlx-> dim[x] / 2) * 64;
	s = moves;
	i = -1;
	div = 1;
	dis = 0;
	while (++i < 9)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->num[(s / div) % 10], pos[x] + 85 - dis, pos[y]);
		div *= 10;
		dis += 20;
	}
}

void	attack(t_game *game)
{
	if (game->link->att == 0)
		run_mus("afplay sounds/att.wav");
	if (game->prev_att == 'r')
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->l2[game->link->att], game->link->pos[0],
			game->link->pos[1] - 24);
	else if (game->prev_att == 'b')
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->l1[game->link->att], game->link->pos[0] - 32,
			game->link->pos[1]);
	else if (game->prev_att == 't')
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->l3[game->link->att], game->link->pos[0] - 40,
			game->link->pos[1] - 24);
	else if (game->prev_att == 'l')
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->l4[game->link->att], game->link->pos[0] - 40,
			game->link->pos[1] - 24);
	game->link->att++;
	if (game->link->att == 8)
	{
		game->link->state = 'n';
		game->link->att = 0;
		game->active = 0;
	}
}

void	run_intro_help(t_game *game)
{
	if (game->fps <= ANM * 60)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->in[0], 0, 0);
	if ((game->fps >= ANM * 18 && game->fps < ANM * 20)
		|| (game->fps >= ANM * 48 && game->fps < ANM * 50))
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->in[1], 0, 0);
	if ((game->fps >= ANM * 20 && game->fps < ANM * 48))
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->in[2], 0, 0);
	if (game->fps > ANM * 60)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->back[0], 0, 0);
	if (game->fps >= ANM * 100)
	{
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->utils[2], 1664 / 2 - 888 / 2, 1050);
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->back[game->mlx->b / 5], 0, 0);
	}
}

void	run_intro(t_game *game)
{
	if (game->fps >= ANM * 99 && game->intro++ == 1)
		run_mus("afplay sounds/intro.mp3");
	if (game->mlx->b == 4 * 5)
		game->mlx->b = 5;
	run_intro_help(game);
	if (game->fps >= ANM * 260)
	{
		if (game->mlx->b > 10)
			mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
				game->mlx->utils[4], 1664 / 2 - 666 / 2, 850);
	}
	if (game->fps >= ANM * 70)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->utils[game->mlx->b / 10], 1664 / 2 - 1414 / 2, 64);
	if (game->fps >= ANM * 80)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->mlx->utils[3], 1664 / 2 - 1331 / 2, 64);
	game->mlx->b++;
}
