/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:47:39 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/05 21:34:40 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		create_path(t_ant *ant, int i, char *str)
{
	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], str);
}

int				next(t_ant *ant, int i, t_room *room, t_path *tmp)
{
	t_room		*tmp_r;

	while (1)
	{
		tmp_r = room;
		while (tmp_r != NULL)
		{
			if (ft_strcmp(tmp_r->name, tmp->from) == 0)
			{
				tmp = get_smaller_path(room, tmp->from);
				create_path(ant, i, tmp->from);
				if (ft_strcmp(tmp->from, ant->start) == 0)
					return (1);
				i++;
			}
			tmp_r = tmp_r->next;
		}
	}
	return (0);
}

int				register_path(t_ant *ant, t_room *room)
{
	t_path		*tmp;
	int			i;

	i = 0;
	tmp = get_smaller_path(room, ant->end);
	if (tmp == NULL)
		ft_error("No path found");
	if (!(ant->path = (char**)malloc(sizeof(char*) * (tmp->distance + 2))))
		ft_error("Malloc error");
	ant->path[tmp->distance + 1] = NULL;
	create_path(ant, i++, ant->end);
	create_path(ant, i++, tmp->from);
	if (next(ant, i, room, tmp) == 1)
		return (tmp->distance);
	return (0);
}

void			write_ant(t_ant *ant, int len)
{
	int		i;

	i = 0;
	while (ant->path[i] != NULL)
	{
		ft_printf("path[%d] : %s\n", i, ant->path[i]);
		i++;
	}
	int		cal;
	int		nb;
	int		fourmi;
	int		LEN;
	int		cpylen;

	LEN = len;
	nb = 1;
	i = 0;
	len--;
	cpylen = len;
	while (nb <= ant->nb)
	{
		cal = 0;
		fourmi = 1;
		len = cpylen - i;
		//ft_printf("\nlen : %d", len);
		if (len < 0)
			break ;
		ft_printf("\n");
		while (cal < nb)
		{
			if (cal != 0)
				ft_printf(" ");
			ft_printf("L%d-%s", fourmi, ant->path[len]);
			fourmi++;
			len++;
			cal++;
		}
		i++;
		nb++;
	}
	int nb2 = 0;
	nb = 1;
	fourmi = 2;
	while (fourmi <= ant->nb)
	{
		i = 0;
		nb2 = 0;
		fourmi = nb + 1;
		ft_printf("\n");
		//ft_printf("LEN : %d\n", LEN);
		while (nb2 < LEN)
		{
			ft_printf("L%d-%s ", fourmi, ant->path[i]);
			nb2++;
			fourmi++;
			i++;
		}
		nb++;
	}
	fourmi--;
	nb++;
	fourmi = nb;
	nb = --LEN;
	cpylen = fourmi;
	while (nb >= 0)
	{
		cal = nb;
		fourmi = cpylen;
		i = 0;
		ft_printf("\n");
		while (cal > 0)
		{
			if (cal != nb)
				ft_printf(" ");
			ft_printf("L%d-%s", fourmi, ant->path[i]);
			i++;
			fourmi++;
			cal--;
		}
		cpylen++;
		nb--;
	}
}
