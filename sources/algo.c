/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/03 20:35:38 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	search_room(t_ant *ant, t_room *room, char *str, int i)
{
	t_room	*tmp;
	t_path	*tmp_p;

	tmp = room;
	while (ft_strcmp(tmp->name, str) != 0)
		tmp = tmp->next;
	tmp_p = tmp->path;
	while (tmp_p->next != NULL)
		tmp_p = tmp_p->next;
	if (tmp_p->close == 0)
	{
		tmp_p->from = ft_strdup(ant->here);
		tmp_p->distance = i;
	}
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

int 	check_close(t_path *path)
{
	while (path != NULL)
	{
		if (path->close == 1)
			return (1);
		path = path->next;
	}
	return (0);
}

void	close_here(t_ant *ant, t_room *room)
{
	t_path	*tmp_path;
	t_room	*tmp_room;

	tmp_room = room;
	while (tmp_room != NULL)
	{
		if (check_close(tmp_room->path) == 1 || ft_strcmp(tmp_room->name, ant->here) == 0)
		{
			tmp_path = tmp_room->path;
			while (tmp_path != NULL)
			{
				tmp_path->close = 1;
				tmp_path = tmp_path->next;
			}
		}
		tmp_room = tmp_room->next;
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
		cpy = tmp->path;
		while (cpy != NULL)
		{
			if (ft_strcmp(tmp->name, ant->end) != 0 && cpy->close == 0 && (cpy->distance >= 0 && cpy->distance < distance))
			{
				distance = cpy->distance;
				here = tmp->name;
			}
			cpy = cpy->next;
		}
		tmp = tmp->next;
	}
	ant->here = here;
}

void	get_path(t_ant *ant, t_room *room)
{
	t_room		*tmp_r;
	t_path		*tmp;
	int			i;

	i = 0;
	tmp = get_smaller_path(room, ant->end);
	if (tmp == NULL)
		ft_error("No path found");
	if (!(ant->path = (char**)malloc(sizeof(char*) * (tmp->distance + 2))))
		ft_error("Malloc error");
	ant->path[tmp->distance + 1] = NULL;

	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(ant->end) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], ant->end);
	ft_printf("ant->path[i] : %s\n", ant->path[i]);

	i++;
	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(tmp->from) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], tmp->from);
	ft_printf("ant->path[i] : %s\n", ant->path[i]);

	i++;
	while (1)
	{
		tmp_r = room;
		while (tmp_r != NULL)
		{
			if (ft_strcmp(tmp_r->name, tmp->from) == 0)
			{
				tmp = get_smaller_path(room, tmp->from);
				if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(tmp->from) + 1)))
					ft_error("Malloc error");
				ant->path[i] = ft_strcpy(ant->path[i], tmp->from);
				ft_printf("ant->path[i] : %s\n", ant->path[i]);
				if (ft_strcmp(tmp->from, ant->start) == 0)
					return ;
				i++;
			}
			tmp_r = tmp_r->next;
		}
	}
}

void	ant()
{

}

void	start_algo(t_global *global, t_ant *ant)
{
	int		distance;
	int		i;

	i = 0;
	distance = 1;
	ant->here = ant->start;
	init_path(global->room);
	while (check_end(ant, global->room) == 1)
	{
		if (i == 0)
			search_room(ant, global->room, ant->start, 0);
		else
			distance = copy_last(ant, global->room) + 1;
		close_here(ant, global->room);
		find_branch(ant, global, distance);
		smaller_distance(ant, global->room);
		init_path(global->room);
		//print_test(global->room);
		if (ant->here == NULL && check_end(ant, global->room) == 1)
			break ;
		i++;
	}
	get_path(ant, global->room);
	//ant();
}
