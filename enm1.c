/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enm_bonus1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:52:52 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/19 23:17:38 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_enm	*ft_newenm(int life, int adv, int i[4])
{
	t_enm	*new_en;

	new_en = (t_enm *) malloc(sizeof(t_enm));
	if (!new_en)
		return (0);
	new_en->life = life;
	new_en->adv = adv;
	new_en->next = NULL;
	position_m(new_en->pos, i[x] * 64, i[y] * 64);
	return (new_en);
}

t_enm	*ft_lastenm(t_enm *enm)
{
	if (!enm)
		return (0);
	while (enm -> next != NULL)
		enm = enm -> next;
	return (enm);
}

void	ft_enmadd_back(t_enm **enms, int life, int adv, int i[4])
{
	t_enm	*new;

	new = ft_newenm(life, adv, i);
	if (*enms == NULL)
		*enms = new;
	else
		ft_lastenm(*enms)->next = new;
}

void	ft_enmclear(t_enm **enm)
{
	t_enm	*tmp;

	if (enm)
	{
		tmp = *enm;
		while (*enm)
		{
			tmp = tmp -> next;
			free(*enm);
			*enm = tmp;
		}
	}
}

void	ft_enmiter(t_enm *enm, t_game *game)
{
	while (enm)
	{
		if (enm->life)
		{
			enm_move(enm, game->mlx->map, game->link, game);
			if (!enm->next)
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
					game->mlx->enm2[game->mlx->f / 2], enm->pos[x],
					enm->pos[y] + game->mlx->anm_sp / 2 - 8);
			else
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->mlx_win,
					game->mlx->enm1[game->mlx->f / 2], enm->pos[x],
					enm->pos[y] + game->mlx->anm_sp / 2 - 8);
		}
		enm = enm -> next;
	}
}
