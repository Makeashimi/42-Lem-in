/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:00:06 by jcharloi          #+#    #+#             */
/*   Updated: 2017/11/25 21:08:09 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** --------------- PARSING DU FOND ----------------
** 		- Nom du tube different d'une salle
**		- Deux fois le meme nom de salle dans un tube
**		-
*/

int		cmp_pipe(t_room *room, char *str)
{
	t_room *tmp;

	tmp = room;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	compare_pipe(t_global *global)
{
	t_pipe		*tmp;

	tmp = global->pipe;
	while (tmp != NULL)
	{
		if (cmp_pipe(global->room, tmp->s1) == 0)
			ft_error("Wrong name of pipe");
		if (cmp_pipe(global->room, tmp->s2) == 0)
			ft_error("Wrong name of pipe");
		if (ft_strcmp(tmp->s1, tmp->s2) == 0)
			ft_error("Two times the same room");
		tmp = tmp->next;
	}
}
