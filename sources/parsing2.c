/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:00:06 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:13:31 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** --------------- PARSING DU FOND ----------------
** 		- Nom du tube different d'une salle
**		- Deux fois le meme nom de salle dans un tube
**		- Deux fois le meme tube
*/

static int	cmp_pipe(t_room *room, char *str)
{
	t_room		*tmp;

	tmp = room;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	is_two_pipe(t_pipe *pipe, char *s1, char *s2)
{
	t_pipe		*tmp;

	tmp = pipe;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->s1, s1) == 0 && ft_strcmp(tmp->s2, s2) == 0)
			return (1);
		if (ft_strcmp(tmp->s1, s2) == 0 && ft_strcmp(tmp->s2, s1) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	compare_valid_pipe(t_global *global)
{
	t_pipe		*tmp;
	t_pipe		*previous;

	tmp = global->pipe;
	while (tmp != NULL)
	{
		if (cmp_pipe(global->room, tmp->s1) == 0 ||
			cmp_pipe(global->room, tmp->s2) == 0)
		{
			remove_pipe(tmp);
			if (tmp == global->pipe)
				global->pipe = NULL;
			else
				previous->next = NULL;
			break ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

void		compare_pipe(t_ant *ant, t_global *global)
{
	t_pipe		*tmp;

	tmp = global->pipe;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->s1, tmp->s2) == 0)
			error(ant, global, "Two times the same room");
		if (is_two_pipe(tmp->next, tmp->s1, tmp->s2) == 1)
			error(ant, global, "Two times the same pipe");
		tmp = tmp->next;
	}
	compare_valid_pipe(global);
}
