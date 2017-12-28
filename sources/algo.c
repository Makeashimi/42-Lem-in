/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/28 21:06:38 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_path(t_room *room)
{
	t_room	*tmp;

	tmp = room;
	while (tmp != NULL)
	{
		tmp->path = link_path(room->path);
		tmp = tmp->next;
	}
}

void	search_room(t_ant *ant, t_room *room, char *str, int i)
{
	t_room	*tmp;

	tmp = room;
	while (ft_strcmp(tmp->name, str) != 0)
		tmp = tmp->next;
	tmp->path->from = ft_strdup(ant->here);
	tmp->path->distance = i;
}

void	find_branch(t_ant *ant, t_global *global, int i)
{
	t_pipe	*tmp;

	tmp = global->pipe;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->s1, ant->here) == 0 || ft_strcmp(tmp->s2, ant->here) == 0)
		{
			ft_printf("here : %s\n", ant->here);
			if (ft_strcmp(tmp->s1, ant->here) == 0)
				search_room(ant, global->room, tmp->s2, i);
			else
				search_room(ant, global->room, tmp->s1, i);
		}			
		tmp = tmp->next;
	}
}

void	smaller_distance()
{
	
}

void	start_algo(t_global *global, t_ant *ant)
{
	t_room *tmp = global->room;

	ant->here = ant->start;
	init_path(global->room);
	search_room(ant, global->room, ant->start, 0);

	find_branch(ant, global, 1);
	while (tmp != NULL)
	{
		ft_printf("path->from : %s et path->distance : %d\n", tmp->path->from, tmp->path->distance);
		tmp = tmp->next;
	}
	ft_printf("\n");
	smaller_distance();
}
