/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:36:43 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/16 19:11:39 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	play_dead(t_player *link, t_map *mlx, t_game *game)
{
	link->att += 0;
	mlx->add += 0;
	game->active += 0;
}

void	beat_him(t_game *game, t_enm *skull)
{
	game->active += 0;
	skull->adv += 0;
}

void	run_mus(char *s)
{
	int	i;

	i = s[0];
	i += 0;
}

void	take_the_beating(t_game *game)
{
	game->active += 0;
}

void	enm_move(t_enm *skull, char **map, t_player *link, t_game *game)
{
	int	i;

	i = map[0][0];
	i += 0;
	link->att += 0;
	skull->adv += 0;
	game->active += 0;
}
