/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/02 21:56:02 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lst	*create_lst(void)
{
	t_lst		*lst;

	if (!(lst = (t_lst*)malloc(sizeof(t_lst))))
		ft_error("Malloc error");
	lst->path = NULL;
	lst->next = NULL;
	return (lst);
}

t_lst			*link_lst(t_lst **lst)
{
	t_lst		*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = create_lst();
		return (*lst);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_lst();
	return (tmp->next);
}

static t_path	*create_path(void)
{
	t_path		*path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		ft_error("Malloc error");
	path->next = NULL;
	return (path);
}

t_path			*link_path(t_lst *lst)
{
	t_path		*tmp;

	tmp = lst->path;
	if (tmp == NULL)
	{
		lst->path = create_path();
		return (lst->path);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_path();
	return (tmp->next);
}

void			save_path(t_lst *lst, char *here)
{
	t_path		*tmp;

	tmp = link_path(lst);
	if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(here) + 1)))
		ft_error("Malloc error");
	tmp->str = ft_strcpy(tmp->str, here);
	tmp->str[ft_strlen(here)] = '\0';
}

static int		tube_len(t_pipe *pipe)
{
	t_pipe		*tmp;
	int			i;

	i = 0;
	tmp = pipe;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}	

void			init_tab(t_pipe *pipe, t_ant *ant)
{
	int 		len;

	len = tube_len(pipe);
	if (!(ant->tab = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	tabset(ant->tab, 0, len);
}
