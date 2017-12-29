/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/29 22:26:06 by jcharloi         ###   ########.fr       */
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

	tmp_room = room;
	ft_printf("-------------------------------------------------------------------\n");
	while (tmp_room)
	{
		ft_printf("|");
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
			ft_printf("|");
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
			ft_printf("|");
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
			ft_printf("|");
			if (tmp_path->close)
				ft_printf(RED" C: %d\t"EOC, tmp_path->close);
			else
				ft_printf(" C: %d\t", tmp_path->close);
			tmp_room = tmp_room->next;
		}
		ft_printf("\n-------------------------------------------------------------------\n");
		path = path->next;
	}
	ft_printf("\n");
}
