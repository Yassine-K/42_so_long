/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:40:30 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 17:22:06 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_arr(void *mlx, char *s)
{
	if (s)
	{
		mlx_destroy_image(mlx, s);
	}
}

void	free_grp_four(t_map *mlx, int i)
{
	free_arr(mlx->mlx, mlx->enm1[i]);
	free_arr(mlx->mlx, mlx->enm2[i]);
	free_arr(mlx->mlx, mlx->wall[i]);
	free_arr(mlx->mlx, mlx->corn[i]);
	free_arr(mlx->mlx, mlx->fire[i]);
	free_arr(mlx->mlx, mlx->door_o[i]);
	free_arr(mlx->mlx, mlx->door_c[i]);
	if (i < 3)
	{
		free_arr(mlx->mlx, mlx->floor[i]);
		free_arr(mlx->mlx, mlx->in[i]);
	}
}

void	free_grp_five(t_map *mlx, int i, t_player *link)
{
	free_arr(mlx->mlx, link->lk[i]);
	free_arr(mlx->mlx, mlx->back[i]);
	free_arr(mlx->mlx, mlx->utils[i]);
	if (i < 4)
		free_grp_four(mlx, i);
}

void	free_mem(t_player *link, t_map *mlx, int i)
{
	if (mlx->path != NULL)
		free(mlx->path);
	while (++i < 12)
	{
		free_arr(mlx->mlx, mlx->num[i]);
		if (i < 5)
			free_grp_five(mlx, i, link);
		if (i < 6)
			free_arr(mlx->mlx, link->lf[i]);
		if (i < 8)
		{
			free_arr(mlx->mlx, link->l1[i]);
			free_arr(mlx->mlx, link->l2[i]);
			free_arr(mlx->mlx, link->l3[i]);
			free_arr(mlx->mlx, link->l4[i]);
		}
		if (i < 11)
		{
			free_arr(mlx->mlx, link->lr[i]);
			free_arr(mlx->mlx, link->ld[i]);
			free_arr(mlx->mlx, link->lt[i]);
			free_arr(mlx->mlx, link->ll[i]);
		}
	}
}

int	close_win(t_game *game)
{
	int	i;

	i = -1;
	free_mem(game->link, game->mlx, -1);
	free_arr(game->mlx->mlx, game->dark);
	ft_enmclear(&game->skull);
	while (++i < game->mlx->dim[1])
	{
		if (game->lvl < LV)
			free(game->mlx->map[i]);
		if (i < 2)
		{
			free_arr(game->mlx->mlx, game->mlx->tmp[i]);
			free_arr(game->mlx->mlx, game->link->h[i]);
			free_arr(game->mlx->mlx, game->mlx->coll[i]);
			free_arr(game->mlx->mlx, game->mlx->pl[i]);
		}
	}
	free(game->mlx->map);
	mlx_destroy_window(game->mlx->mlx, game->mlx->mlx_win);
	system("killall afplay &> /dev/null");
	exit(0);
	return (0);
}
