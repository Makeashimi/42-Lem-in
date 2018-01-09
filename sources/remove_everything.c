/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_everything.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:25:05 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:23:12 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			error(t_ant *ant, t_global *global, char *str)
{
	if (ant != NULL)
		remove_ant(ant);
	if (global->room != NULL)
		remove_room(global->room);
	if (global->pipe != NULL)
		remove_pipe(global->pipe);
	if (global != NULL)
	{
		free(global);
		global = NULL;
	}
	ft_printf("%s\n", str);
	exit(-1);
}

void			remove_ant(t_ant *ant)
{
	t_ant 		*tmp;
	t_ant		*next;

	tmp = ant;
	if (ant->start != NULL)
		free(ant->start);
	ant->start = NULL;
	if (ant->end != NULL)
		free(ant->end);
	ant->end = NULL;
	if (ant->here != NULL)
		free(ant->here);
	ant->here = NULL;
	if (ant->path != NULL)
		ft_tabdel(&ant->path);
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = next;
	}
	ant = NULL;
	ft_printf("ant : %p\n", ant);
}

void			remove_path(t_path *path)
{
	t_path		*tmp;
	t_path		*next;

	tmp = path;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->from != NULL)
			free(tmp->from);
		free(tmp);
		tmp = next;
	}
}

void			remove_room(t_room *room)
{
	t_room		*tmp;
	t_room		*next;

	tmp = room;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->name);
		remove_path(tmp->path);
		tmp->path = NULL;
		free(tmp);
		tmp = next;
	}
	room = NULL;
	ft_printf("room : %p\n", room);
}

void			remove_pipe(t_pipe *pipe)
{
	t_pipe		*tmp;
	t_pipe		*next;

	tmp = pipe;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->s1);
		free(tmp->s2);
		free(tmp);
		tmp = next;
	}
	pipe = NULL;
	ft_printf("pipe : %p\n", pipe);
}
