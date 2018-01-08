/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 16:25:23 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/07 20:47:48 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** --------------- PARSING DU FOND ----------------
** 			- Pas de start/end
**			- 2x start ou/et end
**			- 2x meme nom de salle/coordonnees
**			- Une salle qui n'est pas dans un tube
*/

int		cmp_room_coordinate(t_room *tmp, int x, int y)
{
	t_room	*cpy;

	cpy = tmp;
	while (cpy != NULL)
	{
		if (cpy->x == x && cpy->y == y)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}

int		cmp_room_name(t_room *tmp, char *str)
{
	t_room	*cpy;

	cpy = tmp;
	while (cpy != NULL)
	{
		if (ft_strcmp(cpy->name, str) == 0)
			return (1);
		cpy = cpy->next;
	}
	return (0);
}

void	compare_room(t_global *global)
{
	t_room *tmp;

	tmp = global->room;
	while (tmp != NULL)
	{
		if (cmp_room_name(tmp->next, tmp->name) == 1)
			ft_error("Two times the same name of a room");
		if (cmp_room_coordinate(tmp->next, tmp->x, tmp->y) == 1)
			ft_error("Two times the same coordinate of a room");
		tmp = tmp->next;
	}
}

void	get_start(t_ant *ant, t_ant *cpy)
{
	t_ant	*tmp;

	tmp = cpy;
	while (tmp != NULL && ft_strcmp(tmp->str, "##start") != 0)
		tmp = tmp->next;
	if (tmp == NULL || tmp->next == NULL)
		ft_error("ERROR : No start room");
	tmp = tmp->next;
	check_form(tmp->str);
	ant->start = (char*)malloc(sizeof(char) * ft_strsrchi(tmp->str, ' ') + 1);
	ant->start = strcpy_until(ant->start, tmp->str, ' ');
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->str, "##start") == 0)
			ft_error("ERROR : Multiple start room");
		tmp = tmp->next;
	}
}

void	get_end(t_ant *ant, t_ant *cpy)
{
	t_ant	*tmp;

	tmp = cpy;
	while (tmp != NULL && ft_strcmp(tmp->str, "##end") != 0)
		tmp = tmp->next;
	if (tmp == NULL || tmp->next == NULL)
		ft_error("ERROR : No end room");
	tmp = tmp->next;
	check_form(tmp->str);
	ant->end = (char*)malloc(sizeof(char) * ft_strsrchi(tmp->str, ' ') + 1);
	ant->end = strcpy_until(ant->end, tmp->str, ' ');
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->str, "##end") == 0)
			ft_error("ERROR : Multiple end room");
		tmp = tmp->next;
	}
}
