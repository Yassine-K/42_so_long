/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:56:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/17 23:25:39 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_val(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

char	**copy_map(t_map *mlx)
{
	char	**map;
	int		i;

	i = -1;
	map = (char **) malloc((mlx->dim[y] + 1) * sizeof(char *));
	if (!map)
		return (0);
	while (++i < mlx->dim[y])
	{
		map[i] = ft_strdup(mlx->map[i]);
		if (!map[i])
		{
			free_val(map);
			return (0);
		}
	}
	map[i] = 0;
	return (map);
}

void	discover(t_map *mlx, int px, int py)
{
	if (mlx->check[py][px] == CO)
		mlx->p_pos[2]++;
	if (mlx->check[py][px] == EX)
		mlx->p_pos[3]++;
	mlx->check[py][px] = WL;
	if (mlx->check[py + 1][px] != WL)
		discover(mlx, px, py + 1);
	if (mlx->check[py - 1][px] != WL)
		discover(mlx, px, py - 1);
	if (mlx->check[py][px - 1] != WL)
		discover(mlx, px - 1, py);
	if (mlx->check[py][px + 1] != WL)
		discover(mlx, px + 1, py);
}

int	valid_p(t_map *mlx)
{
	int	valid;

	valid = 0;
	mlx->p_pos[2] = 0;
	mlx->p_pos[3] = 0;
	discover(mlx, mlx->p_pos[x], mlx->p_pos[y]);
	if (mlx->p_pos[2] == mlx->max_sc && mlx->p_pos[3] == 1)
		valid = 1;
	if (valid == 0)
		print_info("Error:\nThere is no valid path!", -1);
	free_val(mlx->check);
	return (valid);
}

void	just_wait(t_game *game, char c)
{
	if (c == 'r' && MODE == 1)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->lr[0], game->link->pos[0], game->link->pos[1]);
	else if (c == 'b' && MODE == 1)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->ld[0], game->link->pos[0], game->link->pos[1]);
	else if (c == 'l' && MODE == 1)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->ll[0], game->link->pos[0], game->link->pos[1]);
	else if (c == 't' && MODE == 1)
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->lt[0], game->link->pos[0], game->link->pos[1]);
	else if (game->key == 49 && MODE == 1)
		just_wait(game, game->prev_att);
	else
		mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
			game->link->ld[0], game->link->pos[0], game->link->pos[1]);
}
