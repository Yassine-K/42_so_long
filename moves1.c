/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:47:14 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 18:17:14 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	in_m(int keycode)
{
	if (keycode == R || keycode == D)
		return ('r');
	else if (keycode == L || keycode == A)
		return ('l');
	else if (keycode == T || keycode == W)
		return ('t');
	else if (keycode == B || keycode == S)
		return ('b');
	return (0);
}

void	next_coll(t_game *g, char *c, char elm)
{
	int	k[2];

	k[x] = (g->link->pos[x] - (g->link->pos[x]) % 64) / 64;
	k[y] = (46 + g->link->pos[y] - (46 + g->link->pos[y]) % 64) / 64;
	if (c[1] == 't' || c[1] == 'b')
		k[x] = g->link->pos[x] / 64;
	if (c[1] == 'r')
		k[x] = (16 + g->link->pos[x] - (16 + g->link->pos[x]) % 64) / 64;
	if (c[1] == 't')
		k[y] = (46 + g->link->pos[y] - (46 + g->link->pos[y]) % 64) / 64;
	if (c[1] == 'b')
		k[y] = (g->link->pos[y] + MV + (g->link->pos[y] + MV) % 64) / 64;
	if (g->mlx->map[(k[y])][k[x]] == elm && ((MODE && ((g->link->score <
		g->mlx->t_sc && (k[x] != g->mlx->key[x] || k[y] != g->mlx->key[y]))
		|| (g->link->score == g->mlx->t_sc - 1 && k[x] == g->mlx->key[x]
		&& k[y] == g->mlx->key[y]))) || !MODE))
		add_score(k, g);
	if (g->link->score == g->mlx->t_sc && g->link->pos[y]
		== g->mlx->d_pos[y] && g->link->pos[x] / 64 == g->mlx->d_pos[x]
		&& MODE == 1 && g->lvl < LV && g->mlx->path != NULL)
		g->link->fall = 0;
	else if (g->link->score == g->mlx->t_sc && g->link->pos[y]
		== g->mlx->d_pos[y] && g->link->pos[x] / 64 == g->mlx->d_pos[x])
		close_win(g);
}

void	start_the_game(t_game *g)
{
	if (g->start++ == 1)
		run_mus("afplay sounds/cast.mp3");
	if (g->active && g->link->life > 0 && g->link->fall == -1)
	{
		if (g->active == 'r' && next_p(g, "xr"))
			play_an(g, "ar0");
		else if (g->active == 'b' && next_p(g, "yb"))
			play_an(g, "ab1");
		else if (g->active == 'l' && next_p(g, "xl"))
			play_an(g, "sl0");
		else if (g->active == 't' && next_p(g, "yt"))
			play_an(g, "st1");
		else if (g->key == 49 && MODE == 1)
			attack(g);
		else
			just_wait(g, in_m(g->key));
	}
	else if (g->link->life > 0 && g->link->fall == -1)
		just_wait(g, in_m(g->key));
	else if (g->link->life < 1 && g->link->fall == -1)
		play_dead(g->link, g->mlx, g);
	else
		fall_down(g);
}

void	refill(t_game *g)
{
	g->mlx->f++;
	if (g->mlx->f == 8)
		g->mlx->f = 0;
	g->last_sp = 'a';
	mlx_clear_window(g->mlx->mlx, g->mlx->mlx_win);
	if (g->start)
	{
		fill_map(g->mlx->map, g->mlx, g->link, g);
		put_dead(g);
		if (MODE == 1)
		{
			mlx_put_image_to_window(g->mlx->mlx, g->mlx->mlx_win,
				g->mlx->num[11], g->mlx-> dim[0] * 64 - 64 * 3, 6);
			mlx_put_image_to_window(g->mlx->mlx, g->mlx->mlx_win,
				g->mlx->num[10], g->mlx-> dim[0] * 64 - 64 * 3 + 24, 7);
			put_score(g->mlx, g->link->score);
			put_moves(g->mlx, g->moves);
		}
	}
	else
		run_intro(g);
}

void	check_coll(t_game *game, char c[3])
{
	char	*s;
	int		k[2];

	s = ft_strdup(c);
	s[2] = '\0';
	k[0] = game->link->pos[0] / 64;
	k[1] = (game->link->pos[1] + 48) / 64;
	if (s[1] == 'l' || s[1] == 'r')
		s[0] = 'x';
	else
		s[0] = 'y';
	next_coll(game, s, CO);
	free(s);
}
