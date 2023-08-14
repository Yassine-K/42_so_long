/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:43:44 by ykhayri           #+#    #+#             */
/*   Updated: 2023/02/09 22:12:57 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

void	ft_putnbr(int nb)
{
	unsigned int	i;
	char			nbr;

	nbr = '0';
	i = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		i *= -1;
	}
	if (i >= 0 && i <= 9)
	{
		ft_putchar(nbr + i);
	}
	if (i > 9 && i < 100)
	{
		ft_putchar(nbr + i / 10);
		ft_putnbr(i % 10);
	}
	if (i > 99)
	{
		ft_putnbr(i / 10);
		ft_putchar(nbr + i % 10);
	}
}

void	print_info(char *s, int n)
{
	ft_putstr(s);
	if (n > 0)
	{
		ft_putchar(' ');
		ft_putnbr(n);
		ft_putchar('\n');
	}
}

void	put_score(t_map *mlx, int score)
{
	int	s;
	int	pos_x;

	s = score;
	pos_x = mlx-> dim[0] * 64 - 64 * 3;
	if (score < 100)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->num[(s / 100) % 10], pos_x + 45, 6);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->num[(s / 10) % 10], pos_x + 65, 6);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,
			mlx->num[s % 10], pos_x + 85, 6);
	}
}
