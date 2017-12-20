/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:20:28 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/20 22:37:29 by jcharloi         ###   ########.fr       */
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

static t_pathcpy	*create_pathcpy(void)
{
	t_pathcpy		*pathcpy;

	if (!(pathcpy = (t_pathcpy*)malloc(sizeof(t_pathcpy))))
		ft_error("Malloc error");
	pathcpy->next = NULL;
	return (pathcpy);
}

t_pathcpy			*link_pathcpy(t_lst *lst)
{
	t_pathcpy		*tmp;

	tmp = lst->pathcpy;
	if (tmp == NULL)
	{
		lst->pathcpy = create_pathcpy();
		return (lst->pathcpy);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_pathcpy();
	return (tmp->next);
}

int		tube_len(t_pipe *pipe)
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

int		check_tab_zero(t_global *global, int *tab)
{
	int		len;
	int		i;

	i = 0;
	len = tube_len(global->pipe);
	while (i < len)
	{
		if (tab[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

void			init_tab(t_pipe *pipe, t_ant *ant)
{
	int 		len;

	len = tube_len(pipe);
	if (!(ant->tab = (int*)malloc(sizeof(int) * len)))
		ft_error("Malloc error");
	tabset(ant->tab, 0, len);
}

void	remove_path(t_lst *lst, char *here)
{
	t_pathcpy	*tmp;
	t_pathcpy	*previous;
	int		test;

	test = 0;
	while (ft_strcmp(lst->pathcpy->strcpy, here) == 0)
	{
		tmp = lst->pathcpy->next;
		free(lst->pathcpy);
		lst->pathcpy = tmp;
	}
	tmp = lst->pathcpy;
	previous = lst->pathcpy;
	while (tmp != NULL)
	{
		//ft_printf("maillon a supprimer : %s\nprevious : %s\n", tmp->strcpy, previous->strcpy);
		if (ft_strcmp(tmp->strcpy, here) == 0)
		{
			previous->next = tmp->next;
			free(tmp);
			tmp = previous->next;
			test = 0;
		}
		if (test > 0)
			previous = previous->next;
		if (tmp != NULL)
			tmp = tmp->next;
		test++;
	}
}

char	*move_back(t_global *global, t_ant *ant, char *here)
{
	t_pipe	*tmp;

	while (1)
	{
		tmp = global->pipe;
		ant->i = 0;
		while (tmp != NULL)
		{
			if (ant->tab[ant->i] == 0 && ft_strcmp(here, ant->end) != 0 && (ft_strcmp(here, tmp->s1) == 0 || ft_strcmp(here, tmp->s2) == 0))
				return (here);
			if (ant->tab[ant->i] == 1 && (ft_strcmp(here, tmp->s1) == 0 || ft_strcmp(here, tmp->s2) == 0))
			{
				remove_path(global->lst, here);
				ant->tab[ant->i] = 2;
				if (ft_strcmp(tmp->s1, here) == 0)
					here = tmp->s2;
				else
					here = tmp->s1;
			}
			ant->i++;
			tmp = tmp->next;
		}
		if (check_tab_zero(global, ant->tab) != 1)
			return (here);
	}
	return (here);
}
