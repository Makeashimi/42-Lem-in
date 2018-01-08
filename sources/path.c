/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:47:39 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/08 20:46:42 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		create_path(t_ant *ant, int i, char *str)
{
	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], str);
}

void			next(t_ant *ant, int i, t_room *room, t_path *tmp)
{
	t_room		*tmp_r;

	while (1)
	{
		tmp_r = room;
		while (tmp_r != NULL)
		{
			if (ft_strcmp(tmp_r->name, tmp->from) == 0)
			{
				tmp = get_smaller_path(room, tmp->from, NULL);
				create_path(ant, i, tmp->from);
				if (ft_strcmp(tmp->from, ant->start) == 0)
					return ;
				i++;
			}
			tmp_r = tmp_r->next;
		}
	}
}

void			register_path(t_ant *ant, t_room *room)
{
	t_path		*tmp;
	int			i;

	i = 0;
	tmp = get_smaller_path(room, ant->end, NULL);
	if (tmp == NULL)
		ft_error("No path found");
	if (!(ant->path = (char**)malloc(sizeof(char*) * (tmp->distance + 2))))
		ft_error("Malloc error");
	ant->path[tmp->distance + 1] = NULL;
	create_path(ant, i++, ant->end);
	create_path(ant, i++, tmp->from);
	if (ft_strcmp(tmp->from, ant->start) != 0)
		next(ant, i, room, tmp);
	ant->len = tmp->distance;
}
