/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:09:53 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/19 19:44:23 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	load_res(t_game *game, char *obj[12], char *s, int lim)
{
	int		i;
	int		j;
	int		k[2];
	char	*path;

	path = ft_strdup(s);
	j = 0;
	while (s[j] > '9' || s[j] < '0')
		j++;
	i = -1;
	while (++i < lim)
	{
		path[j] = (i + 1) / 10 + 48;
		path[j + 1] = (i + 1) % 10 + 48;
		obj[i] = mlx_xpm_file_to_image(game->mlx->mlx, path, &k[0], &k[1]);
		if (!obj[i])
			close_win(game);
	}
	free(path);
}

void	load_player(t_player *link, t_game *game)
{
	load_res(game, link->ld, "textures/Link/LD/LD01.xpm", 11);
	load_res(game, link->ll, "textures/Link/LL/LL01.xpm", 11);
	load_res(game, link->lr, "textures/Link/LR/LR01.xpm", 11);
	load_res(game, link->lt, "textures/Link/LT/LT01.xpm", 11);
	load_res(game, link->l1, "textures/Link/LAB/LAB01.xpm", 8);
	load_res(game, link->l2, "textures/Link/LAR/LAR01.xpm", 8);
	load_res(game, link->l3, "textures/Link/LAT/LAT01.xpm", 8);
	load_res(game, link->l4, "textures/Link/LAL/LAL01.xpm", 8);
	load_res(game, link->lf, "textures/Link/LF/LF01.xpm", 6);
	load_res(game, link->lk, "textures/Link/LK/LK01.xpm", 5);
	load_res(game, link->h, "textures/Map/h01.xpm", 2);
}

void	load_images(t_map *mlx, t_player *link, t_game *game)
{
	int	a[2];

	game->dark = mlx_xpm_file_to_image(game->mlx->mlx,
			"textures/Map/dark.xpm", &a[0], &a[1]);
	load_player(link, game);
	load_res(game, mlx->num, "textures/nums/n01.xpm", 12);
	load_res(game, mlx->back, "textures/swo/l01.xpm", 5);
	load_res(game, mlx->utils, "textures/swo/s01.xpm", 5);
	load_res(game, mlx->enm1, "textures/Enm/EnmB/E01.xpm", 4);
	load_res(game, mlx->enm2, "textures/Enm/EnmA/E01.xpm", 4);
	load_res(game, mlx->wall, "textures/Map/w01.xpm", 4);
	load_res(game, mlx->corn, "textures/Map/c01.xpm", 4);
	load_res(game, mlx->fire, "textures/Map/f01.xpm", 4);
	load_res(game, mlx->door_o, "textures/Map/o01.xpm", 4);
	load_res(game, mlx->door_c, "textures/Map/d01.xpm", 4);
	load_res(game, mlx->floor, "textures/Map/fl01.xpm", 3);
	load_res(game, mlx->in, "textures/swo/in01.xpm", 3);
	load_res(game, mlx->tmp, "textures/Map/tmp01.xpm", 2);
	load_res(game, mlx->coll, "textures/Map/k01.xpm", 2);
	load_res(game, mlx->pl, "textures/nums/pl01.xpm", 2);
}

int	check_bord(char **map, t_map *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->dim[1])
	{
		j = -1;
		while (map[i][++j] && map[i][j] != '\n')
		{
			if (map[i][j] == 'P')
			{
				mlx->p_pos[x] = j;
				mlx->p_pos[y] = i;
			}
			if ((i == 0 || i == mlx->dim[1] - 1) && map[i][j] != '1')
				return (0);
			if (i > 0 && i < mlx->dim[1] - 1 && (j == 0 || j == mlx->dim[0] - 1)
				&& map[i][j] != '1')
				return (0);
			if ((map[i][j] != WL && map[i][j] != SP && map[i][j] != CO
					&& map[i][j] != EX && map[i][j] != PL))
				return (0);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_map		mlx;
	t_player	link;
	t_game		game;

	if (!av[1] || ac != 2)
		return (2);
	mlx.anm_sp = 0;
	mlx.f = 0;
	mlx.title = "The Legend of Zelda: The Minish Cap";
	if (!initial_map(&mlx, av[1]) || !valid_p(&mlx))
		return (2);
	initial_link(&link);
	initial_game(&game);
	game.mlx = &mlx;
	game.link = &link;
	game.skull = NULL;
	load_images(&mlx, &link, &game);
	mlx_hook(mlx.mlx_win, 2, 1, key_press, &game);
	mlx_hook(mlx.mlx_win, 3, 0, key_up, &game);
	mlx_hook(mlx.mlx_win, 17, 0, close_win, &game);
	mlx_loop_hook(mlx.mlx, refr, &game);
	mlx_loop(mlx.mlx);
	return (0);
}
