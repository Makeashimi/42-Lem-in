/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 15:46:30 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/29 19:31:00 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*create_path(void)
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

t_path			*link_path(t_path *path)
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
	return (tmp->next);
}
