/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:46:30 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/30 19:18:34 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*create_path(void)
{
	t_path	*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		ft_error("Malloc error");
	path->close = 0;
	path->from = NULL;
	path->distance = -1;
	path->next = NULL;
	return (path);
}

static t_path	*link_path(t_path *path)
{
	t_path	*tmp;

	tmp = path;
	if (path == NULL)
	{
		path = create_path();
		return (path);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_path();
	return (path);
}

void			init_path(t_room *room)
{
	t_room	*tmp;

	tmp = room;
	while (tmp != NULL)
	{
		tmp->path = link_path(tmp->path);
		tmp = tmp->next;
	}
}
