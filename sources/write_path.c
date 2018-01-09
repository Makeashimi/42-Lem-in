/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 20:30:43 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 15:45:56 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				init_nb(t_ant *ant, int previous_fourmi)
{
	int		nb;

	if (previous_fourmi > ant->nb)
		return (-1);
	if (ant->len < ant->nb)
		nb = ant->len - 1;
	else
		nb = ant->nb - 1;
	return (nb);
}

void			end_ant(t_ant *ant, int previous_fourmi, int cpylen, int i)
{
	int		nb;
	int		fourmi;
	int		cal;

	if ((nb = init_nb(ant, previous_fourmi)) && nb == -1)
		return ;
	while (nb >= 0)
	{
		cpylen = 0;
		fourmi = previous_fourmi + i;
		cal = nb;
		if (cal > 0)
			ft_printf("\n");
		while (cal > 0)
		{
			if (cal != nb)
				ft_printf(" ");
			color_ant(fourmi, ant->path[cpylen]);
			fourmi++;
			cpylen++;
			cal--;
		}
		nb--;
		i++;
	}
}

void			middle_ant(t_ant *ant, int cpylen)
{
	int		fourmi;
	int		space;
	int		i;

	i = 1;
	fourmi = 2;
	while (fourmi <= ant->nb)
	{
		cpylen = 0;
		space = 0;
		fourmi = i + 1;
		ft_printf("\n");
		while (cpylen < ant->len)
		{
			if (space > 0)
				ft_printf(" ");
			color_ant(fourmi, ant->path[cpylen]);
			space++;
			fourmi++;
			cpylen++;
		}
		i++;
	}
	end_ant(ant, i + 1, 0, 0);
}

void			print_ants(t_ant *ant, int *cal, int *fourmi, int *cpylen)
{
	if (*cal != 0)
		ft_printf(" ");
	color_ant(*fourmi, ant->path[*cpylen]);
	*fourmi = *fourmi + 1;
	*cpylen = *cpylen + 1;
	*cal = *cal + 1;
}

void			begin_ant(t_ant *ant, int nb, int fourmi, int cpylen)
{
	int		cal;
	int		i;

	i = 0;
	while (1)
	{
		cal = 0;
		fourmi = 1;
		cpylen = (ant->len - 1) - i;
		if (cpylen < 0)
			break ;
		if (i > 0)
			ft_printf("\n");
		while (cal < nb)
			print_ants(ant, &cal, &fourmi, &cpylen);
		i++;
		if (nb + 1 <= ant->nb)
			nb++;
	}
	if (i < ant->nb)
		middle_ant(ant, 0);
	else
		end_ant(ant, fourmi + 1, 0, 0);
}
