/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/08 20:46:25 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			start_end_linked(t_ant *ant)
{
	int		fourmi;

	fourmi = 1;
	if (ft_strcmp(ant->path[0], ant->end) == 0 &&
		ft_strcmp(ant->path[1], ant->start) == 0)
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

int			check_close(t_path *path)
{
	while (path != NULL)
	{
		if (path->close == 1)
			return (1);
		path = path->next;
	}
	return (0);
}

t_path		*get_smaller_path(t_room *room, char *str, t_path *take)
{
	t_room		*tmp_room;
	t_path		*tmp;
	int			distance;

	tmp_room = room;
	distance = 2147483647;
	while (tmp_room != NULL)
	{
		if (ft_strcmp(tmp_room->name, str) == 0)
		{
			tmp = tmp_room->path;
			while (tmp != NULL)
			{
				if (tmp->distance > 0 && tmp->distance < distance)
				{
					distance = tmp->distance;
					take = tmp;
				}
				tmp = tmp->next;
			}
		}
		tmp_room = tmp_room->next;
	}
	return (take);
}

int			copy_last(t_ant *ant, t_room *room)
{
	t_room		*tmp_r;
	t_path		*tmp;
	t_path		*take;

	take = get_smaller_path(room, ant->here, NULL);
	tmp_r = room;
	while (tmp_r != NULL)
	{
		if (ft_strcmp(tmp_r->name, ant->here) == 0)
		{
			tmp = tmp_r->path;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->distance = take->distance;
			tmp->from = take->from;
		}
		tmp_r = tmp_r->next;
	}
	return (take->distance);
}

int			check_end(t_ant *ant, t_room *room)
{
	while (room != NULL)
	{
		if (ft_strcmp(room->name, ant->end) != 0 && room->path->close == 0)
			return (1);
		room = room->next;
	}
	return (0);
}
