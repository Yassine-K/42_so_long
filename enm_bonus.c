/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enm_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:36:43 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 18:29:22 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	play_dead(t_player *link, t_map *mlx, t_game *game)
{
	int	k;

	game->active = 0;
	k = link->pos[1];
	if (!game->wait)
		game->wait = game->fps;
	if (link->dead / 2 == 0)
		k -= 6;
	else if (link->dead / 2 == 1)
		k += 4;
	else
		k += 20;
	if (link->dead < 10)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			link->lk[link->dead / 2], link->pos[0], k);
		link->dead++;
	}
	else
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			link->lk[4], link->pos[0], k);
	link_is_dead(game);
}

void	beat_him(t_game *g, t_enm *skull)
{
	int	p[2];

	position_m(p, skull->pos[x], skull->pos[y] / 64);
	if (!(g->prev_att == 'l' && skull->adv < 0)
		&& !(g->prev_att == 'r' && skull->adv > 0))
	{
		if (((g->prev_att == 't' || g->prev_att == 'b') && g->link->att == 4)
			|| (g->prev_att != 't' && g->prev_att != 'b'))
		{
			skull->adv *= -1;
			skull->life--;
			if (skull->life > 0)
				run_mus("afplay sounds/eh.wav");
			else
			{
				g->link->score++;
				run_mus("afplay sounds/ek.wav");
			}
		}
	}
	beat_him2(g, skull, p);
}

void	run_mus(char *s)
{
	if (MODE == 1)
	{
		if (fork() == 0)
		{
			system(s);
			exit(1);
		}
	}
}

void	take_the_beating(t_game *g, t_enm *enm)
{
	int	p[2];

	position_m(p, g->link->pos[x], g->link->pos[y] / 64);
	if (g->mlx->map[p[y]][(p[x] + 16 + 16) / 64] != WL
		&& enm->adv > 0 && enm->pos[x] + 64 <= p[x])
		g->link->pos[x] += 16;
	else if (g->mlx->map[p[y]][(p[x] - 16) / 64] != WL
		&& enm->adv < 0 && enm->pos[x] - 64 <= p[x])
		g->link->pos[x] -= 16;
	g->link->life--;
	if (!enm->next)
		g->link->life -= 2;
	if (g->link->life > 0)
		run_mus("afplay sounds/hurt.wav");
	else
		run_mus("afplay sounds/ld.wav");
}

void	enm_move(t_enm *skull, char **map, t_player *link, t_game *game)
{
	int	p[2];
	int	e[2];

	position_m(p, link->pos[x], link->pos[y] + 48);
	if (game->prev_att == 'r')
		position_m(p, p[x] + 32, link->pos[y] + 48);
	position_m(e, skull->pos[x], skull->pos[y]);
	if ((map[e[y] / 64][((e[x] + 64 + 1) / 64)] == WL && skull->adv > 0)
		|| (map[e[y] / 64][((e[x]) / 64)] == WL && skull->adv < 0))
		skull->adv *= -1;
	skull->pos[x] += skull->adv;
	if (link->life > 0)
	{
		if ((p[x] >= e[x] - 16 && p[x] - 64 <= e[x] + 16
				&& p[y] / 64 == e[y] / 64) || (p[y] >= e[y] - 16
				&& p[y] - 64 <= e[y] + 16 && p[x] / 64 == e[x] / 64))
		{
			if (game->key != 49)
				game->active = 0;
			if (link->state == 'a' && link->att < 7)
				beat_him(game, skull);
			else if (link->state != 'a' && (p[y] / 64 == e[y] / 64))
				take_the_beating(game, skull);
		}
	}
}
