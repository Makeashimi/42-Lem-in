/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/03 19:04:30 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_room(t_room *room)
{
	ft_printf("room %p {path : %p, name: %s, next: %p};\n", room, room->path, room->name, room->next);
}

void	print_path(t_path *path)
{
	ft_printf("\tpath : %p {close: %d, from : %s, distance : %d next: %p};\n", path, path->close, path->from, path->distance, path->next);
}

void	print_test(t_room *room)
{
	t_path	*path;
	t_path	*tmp_path;
	t_room	*tmp_room;
	int		i = 0;
	int		j = 0;

	tmp_room = room;
	ft_printf("-------------------------------------------------------------------\n");
	while (tmp_room)
	{
		ft_printf("|");
		// ft_printf("%p", tmp_room);
		ft_printf(GREEN"  %s\t"EOC, tmp_room->name);
		tmp_room = tmp_room->next;
	}
	ft_printf("\n-------------------------------------------------------------------\n");
	path = room->path;
	while (path)
	{
		tmp_room = room;
		while (tmp_room)
		{
			tmp_path = tmp_room->path;
			j = 0;
			while (j < i)
			{
				tmp_path = tmp_path->next;
				j++;
			}
			ft_printf("|");
			// ft_printf("%p", tmp_path);
			if (tmp_path->distance != -1)
				ft_printf(ORANGE" D: %d\t"EOC, tmp_path->distance);
			else
				ft_printf(" D: %d\t", tmp_path->distance);
			tmp_room = tmp_room->next;
		}
		ft_printf("\n");
		tmp_room = room;
		while (tmp_room)
		{
			tmp_path = tmp_room->path;
			j = 0;
			while (j < i)
			{
				tmp_path = tmp_path->next;
				j++;
			}
			ft_printf("|");
			// ft_printf("%p", tmp_path);
			if (tmp_path->from)
				ft_printf(PURPLE" F: %s\t"EOC, tmp_path->from);
			else
				ft_printf(" F: \t");
			tmp_room = tmp_room->next;
		}
		ft_printf("\n");
		tmp_room = room;
		while (tmp_room)
		{
			tmp_path = tmp_room->path;
			j = 0;
			while (j < i)
			{
				tmp_path = tmp_path->next;
				j++;
			}
			ft_printf("|");
			// ft_printf("%p", tmp_path);
			if (tmp_path->close)
				ft_printf(RED" C: %d\t"EOC, tmp_path->close);
			else
				ft_printf(" C: %d\t", tmp_path->close);
			tmp_room = tmp_room->next;
		}
		ft_printf("\n-------------------------------------------------------------------\n");
		path = path->next;
		i++;
	}
	ft_printf("\n");
}

t_path		*get_smaller_path(t_room *room, char *str)
{
	t_room		*tmp_room;
	t_path		*tmp;
	t_path		*take;
	int			distance;

	take = NULL;
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

int		copy_last(t_ant *ant, t_room *room)
{	
	t_room		*tmp_r;
	t_path		*tmp;
	t_path		*take;

	take = get_smaller_path(room, ant->here);
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

int		check_end(t_ant *ant, t_room *room)
{
	while (room != NULL)
	{
		if (ft_strcmp(room->name, ant->end) != 0 && room->path->close == 0)
			return (1);
		room = room->next;
	}
	return (0);
}
