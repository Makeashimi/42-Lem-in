/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:47:39 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/07 21:07:13 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		create_path(t_ant *ant, int i, char *str)
{
	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], str);
}

void			next(t_ant *ant, int i, t_room *room, t_path *tmp)
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
					return ;
				i++;
			}
			tmp_r = tmp_r->next;
		}
	}
}

void			register_path(t_ant *ant, t_room *room)
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
	if (ft_strcmp(tmp->from, ant->start) != 0)
		next(ant, i, room, tmp);
	ant->len = tmp->distance;
}

void			end_ant(t_ant *ant, int previous_fourmi, int cpylen)
{
	int		nb;
	int		fourmi;
	int		cal;
	int		i;

	if (previous_fourmi > ant->nb)
		return ;
	i = 0;
	if (ant->len < ant->nb)
		nb = ant->len - 1;
	else
		nb = ant->nb - 1;
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
			ft_printf("L%d-%s", fourmi, ant->path[cpylen]);
			fourmi++;
			cpylen++;
			cal--;
		}
		nb--;
		i++;
	}
}

void		middle_ant(t_ant *ant, int cpylen)
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
			ft_printf("L%d-%s", fourmi, ant->path[cpylen]);
			space++;
			fourmi++;
			cpylen++;
		}
		i++;
	}
	end_ant(ant, i + 1, 0);
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
		{
			if (cal != 0)
				ft_printf(" ");
			ft_printf("L%d-%s", fourmi, ant->path[cpylen]);
			fourmi++;
			cpylen++;
			cal++;
		}
		i++;
		if (nb + 1 <= ant->nb)
			nb++;
	}
	if (i < ant->nb)
		middle_ant(ant, 0);
	else
		end_ant(ant, fourmi + 1, 0);
}


int		start_end_linked(t_ant *ant)
{
	int		fourmi;

	fourmi = 1;
	if (ft_strcmp(ant->path[0], ant->end) == 0 && ft_strcmp(ant->path[1], ant->start) == 0)
	{
		while (fourmi <= ant->nb)
		{
			if (fourmi > 1)
				ft_printf(" ");
			ft_printf("L%d-%s", fourmi, ant->end);
			fourmi++;
		}
		return (1);
	}
	return (0);
}
