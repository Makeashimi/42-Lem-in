/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:46:30 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:15:51 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*create_path(t_ant *ant, t_global *global)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		error(ant, global, "Malloc error");
	ft_memset(path, 0, sizeof(t_path));
	path->distance = -1;
	return (path);
}

static t_path	*link_path(t_ant *ant, t_global *global, t_path *path)
{
	t_path	*tmp;

	tmp = path;
	if (path == NULL)
	{
		path = create_path(ant, global);
		return (path);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_path(ant, global);
	return (path);
}

void			init_path(t_ant *ant, t_global *global, t_room *room)
{
	t_room	*tmp;

	tmp = room;
	while (tmp != NULL)
	{
		tmp->path = link_path(ant, global, tmp->path);
		tmp = tmp->next;
	}
}
