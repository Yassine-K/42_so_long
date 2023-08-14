/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:48:50 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/21 16:16:26 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define WL '1'
# define SP '0'
# define CO 'C'
# define EX 'E'
# define PL 'P'
# define PX 64
# define MV 16

# define ESC 53
# define L 123
# define R 124
# define B 125
# define T 126
# define A 0
# define S 1
# define D 2
# define W 13
# define ANM 400
# define LV 4

typedef struct s_map
{
	void	*mlx;
	void	*mlx_win;
	char	*enm1[4];
	char	*enm2[4];
	char	*door_o[4];
	char	*door_c[4];
	char	*coll[2];
	char	*floor[3];
	char	*wall[4];
	char	*corn[4];
	char	*fire[4];
	char	*back[5];
	char	*in[3];
	char	*utils[5];
	char	*pl[2];
	char	*num[12];
	char	*tmp[3];
	char	**map;
	char	**check;
	char	*title;
	char	*path;
	int		p_pos[4];
	int		d_pos[2];
	int		dim[2];
	int		key[2];
	int		max_sc;
	int		t_sc;
	int		anm_sp;
	int		add;
	int		f;
	int		b;
}	t_map;

typedef struct s_player
{
	char	*ll[11];
	char	*lr[11];
	char	*lt[11];
	char	*ld[11];
	char	*l1[8];
	char	*l2[8];
	char	*l3[8];
	char	*l4[8];
	char	*lf[6];
	char	*lk[5];
	char	*h[2];
	char	state;
	int		score;
	int		pos[2];
	int		size[2];
	int		drawn;
	int		dead;
	int		att;
	int		life;
	int		fall;
}	t_player;

typedef struct s_enm
{
	int				life;
	int				pos[2];
	int				size[2];
	int				adv;
	struct s_enm	*next;
}	t_enm;

typedef struct s_game
{
	t_map		*mlx;
	t_player	*link;
	t_enm		*skull;
	char		*dark;
	char		last_sp;
	int			moves;
	int			ann;
	int			fps;
	int			active;
	int			key;
	int			prev_att;
	int			start;
	int			intro;
	int			wait;
	int			tries;
	int			lvl;
	int			p_n;
	int			e_k;
}	t_game;

enum e_data {x = 0, y, c};

#endif
