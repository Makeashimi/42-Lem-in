/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:47:39 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/04 23:29:02 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		create_path(t_ant *ant, int i, char *str)
{
	if (!(ant->path[i] = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ft_error("Malloc error");
	ant->path[i] = ft_strcpy(ant->path[i], str);
}

int				next(t_ant *ant, int i, t_room *room, t_path *tmp)
{
	t_room		*tmp_r;

	while (1)
	{
		tmp_r = room;
		while (tmp_r != NULL)
		{
			if (ft_strcmp(tmp_r->name, tmp->from) == 0)
			{
				tmp = get_smaller_path(room, tmp->from);
				create_path(ant, i, tmp->from);
				if (ft_strcmp(tmp->from, ant->start) == 0)
					return (1);
				i++;
			}
			tmp_r = tmp_r->next;
		}
	}
	return (0);
}

int				register_path(t_ant *ant, t_room *room)
{
	t_path		*tmp;
	int			i;

	i = 0;
	tmp = get_smaller_path(room, ant->end);
	if (tmp == NULL)
		ft_error("No path found");
	if (!(ant->path = (char**)malloc(sizeof(char*) * (tmp->distance + 2))))
		ft_error("Malloc error");
	ant->path[tmp->distance + 1] = NULL;
	create_path(ant, i++, ant->end);
	create_path(ant, i++, tmp->from);
	if (next(ant, i, room, tmp) == 1)
		return (tmp->distance);
	return (0);
}

void			write_ant(t_ant *ant, int len)
{
	int		i;

	i = 0;
	while (ant->path[i] != NULL)
	{
		ft_printf("path[%d] : %s\n", i, ant->path[i]);
		i++;
	}
	ft_printf("len : %d\n", len);
	len--;
	i = 1;
	//boucle nb fourmi = ant->nb ? && la derniere case du tableau = ant->end
	while (i <= ant->nb && ft_strcmp(ant->path[len + 1], ant->end) != 0)
	{
		ft_printf("L%d-%s\n", i, ant->path[len]);
		len--;
	}
}
