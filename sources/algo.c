/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/29 22:40:38 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_path(t_room *room)
{
	t_room	*tmp;

	tmp = room;
	while (tmp != NULL)
	{
		//print_room(tmp);
		if (tmp->path == NULL)
			tmp->path = link_path(tmp->path);
		else
			link_path(tmp->path);
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
			if (ft_strcmp(tmp->s1, ant->here) == 0)
				search_room(ant, global->room, tmp->s2, i);
			else
				search_room(ant, global->room, tmp->s1, i);
		}			
		tmp = tmp->next;
	}
}

void	close_here(t_ant *ant, t_room *room)
{
	t_path	*tmp_path;
	t_room	*tmp_room;

	tmp_room = room;
	while (ft_strcmp(tmp_room->name, ant->here) != 0)
	{
		//print_room(tmp_room);
		tmp_room = tmp_room->next;
	}
	tmp_path = tmp_room->path;
	while (tmp_path != NULL)
	{
		//print_room(tmp_room);
		tmp_path->close = 1;
		tmp_path = tmp_path->next;
	}
}

void	smaller_distance(t_ant *ant, t_room *room)
{
	t_room	*tmp;
	t_path	*cpy;
	char	*here;
	int		distance;

	tmp = room;
	here = NULL;
	distance = 2147483647;
	while (tmp != NULL)
	{
		//print_room(tmp);
		cpy = tmp->path;
		while (cpy != NULL)
		{
			//print_path(cpy);
			if (cpy->close == 0 && (cpy->distance >= 0 && cpy->distance < distance))
			{
				distance = cpy->distance;
				here = tmp->name;
				//ft_printf("distance : %d here : %s\n", distance, here);
			}
			cpy = cpy->next;
		}
		tmp = tmp->next;
	}
	ant->here = here;
}

void	start_algo(t_global *global, t_ant *ant)
{
	ant->here = ant->start;
	init_path(global->room);
	search_room(ant, global->room, ant->start, 0);
	//-------------//
	close_here(ant, global->room);
	ft_printf("ant->here avant : %s\n", ant->here);
	find_branch(ant, global, 1);
	smaller_distance(ant, global->room);

	init_path(global->room);
	close_here(ant, global->room);
	ft_printf("ant->here apres : %s\n", ant->here);
	//-----------//

	ft_printf("\n");
	print_test(global->room);
}
