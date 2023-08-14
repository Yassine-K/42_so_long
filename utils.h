/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:08:26 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 16:14:34 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "getNext/get_next_line.h"
# include "Libft/libft.h"
# include "game.h"

char	**read_map(t_map *mlx, int fd);
int		close_win(t_game *game);
void	fill_map(char **map, t_map *mlx, t_player *link, t_game *game);
int		in_m(int keycode);
void	refill(t_game *game);
void	play_an(t_game *game, char op[3]);
int		key_up(int keycode, t_game *game);
int		key_press(int keycode, t_game *game);
void	check_coll(t_game *game, char c[3]);
void	just_wait(t_game *game, char c);
int		next_p(t_game *game, char *c);
int		refr(t_game *game);
int		check_bord(char **map, t_map *mlx);
void	initial_game(t_game *game);
void	initial_link(t_player *link);
int		initial_map(t_map *mlx, char *s);
void	position_m(int pos[2], int x_p, int y_p);
void	run_mus(char *s);
void	attack(t_game *game);
void	free_mem(t_player *link, t_map *mlx, int i);
void	free_grp_five(t_map *mlx, int i, t_player *link);
void	free_grp_four(t_map *mlx, int i);
void	free_arr(void *mlx, char *s);
int		check_enm(t_game *game);
void	enm_move(t_enm *skull, char **map, t_player *link, t_game *game);
void	play_dead(t_player *link, t_map *mlx, t_game *game);
void	run_intro(t_game *game);
void	put_score(t_map *mlx, int score);
void	put_moves(t_map *mlx, int moves);
int		valid_p(t_map *mlx);
char	**copy_map(t_map *mlx);
void	print_info(char *s, int n);
void	move_switch(t_game *game, int keycode);
void	put_hearts(t_map *mlx, t_player *link);
int		space_empty(t_map *mlx, int i, int j);
int		is_ber(char *s);
void	coll_animation(t_game *game);
void	start_the_game(t_game *game);
void	link_is_dead(t_game *game);
void	put_dead(t_game *g);
void	fall_down(t_game *game);
void	load_maps(t_map *mlx, int fd, char *s);
int		face_way(t_map *mlx, int i, int j);
void	beat_him2(t_game *g, t_enm *skull, int p[2]);
void	add_score(int k[2], t_game *g);

t_enm	*ft_lastenm(t_enm *enm);
void	ft_enmadd_back(t_enm **enms, int life, int adv, int i[4]);
void	ft_enmclear(t_enm **enm);
void	ft_enmiter(t_enm *enm, t_game *game);

#endif
