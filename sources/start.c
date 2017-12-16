/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/16 22:33:55 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_here(t_lst *lst, char *here)
{
	t_path 		*tmp;
	t_pathcpy 	*tmpcpy;

	tmp = link_path(lst);
	tmpcpy = link_pathcpy(lst);
	if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(here))))
		ft_error("Malloc error");
	if (!(tmpcpy->strcpy = (char*)malloc(sizeof(char) * ft_strlen(here))))
		ft_error("Malloc error");
	tmp->str = ft_strcpy(tmp->str, here);
	tmpcpy->strcpy = ft_strcpy(tmpcpy->strcpy, here);
	tmp->str[ft_strlen(here)] = '\0';
	tmpcpy->strcpy[ft_strlen(here)] = '\0';
	ft_printf("str : %s\n", tmp->str);
	ft_printf("strcpy : %s\n", tmpcpy->strcpy);
}

t_lst	*get_previous(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*previous;

	tmp = lst;
	previous = tmp;
	while (tmp->next != NULL)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	return (previous);
}

/*
void	what_inside_pathcpy(t_lst *lst)
{
	t_lst		*tmplst;
	t_lst		*previous;
	t_path 		*tmppath;
	t_pathcpy	*tmpcpy;

	//tmplst contient le nouveau maillon accuillant mon nouveau chemin
	tmplst = link_lst(&lst);
	//previous contient le previous->pathcpy precedent
	previous = get_previous(lst);
	if (previous == NULL)
		return ;
	tmppath = tmplst->path;
	tmpcpy = previous->pathcpy;
	while (tmpcpy != NULL)
	{
		ft_printf("path : %s\n", tmpcpy->strcpy);
		tmpcpy = tmpcpy->next;
	}
	while (tmpcpy != NULL)
	{
		tmppath = link_path(lst);
		if (!(tmppath->str = (char*)malloc(sizeof(char) * ft_strlen(tmpcpy->strcpy))))
			ft_error("Malloc error");
		tmppath->str = ft_strcpy(tmppath->str, tmpcpy->strcpy);
		tmppath->str[ft_strlen(tmpcpy->strcpy)] = '\0';
		tmpcpy = tmpcpy->next;
	}
	tmppath = tmplst->path;
	while (tmppath != NULL)
	{
		ft_printf("str ici : %s\n", tmppath->str);
		tmppath = tmppath->next;
	}
}*/

char	*search_path(t_global *global, t_ant *ant, char *here)
{
	t_pipe	*tmp;

	tmp = global->pipe;
	ant->i = 0;
	
	while (tmp != NULL)
	{
		if (ant->tab[ant->i] == 0 && (ft_strcmp(tmp->s1, here) == 0 || ft_strcmp(tmp->s2, here) == 0))
		{
			save_here(global->lst, here);
			if (ft_strcmp(here, ant->end) == 0)
				return (here);
			if (ft_strcmp(tmp->s1, here) == 0)
				here = tmp->s2;
			else
				here = tmp->s1;
			ant->tab[ant->i] = 1;
		}
		ant->i++;
		tmp = tmp->next;
	}
	return (here);
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
			ft_printf("maillon a supprimer : %s\n", tmp->strcpy);
			ft_printf("maillon d'avant : %s\n", previous->strcpy);
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
	}
	return (here);
}

void	start_algo(t_global *global, t_ant *ant)
{
	//t_lst	*tmp;
	char	*here;
	//int i = 0;

	here = ant->start;
	init_tab(global->pipe, ant);
	global->lst = link_lst(&global->lst);
	//tmp = global->lst;
	while (check_tab_zero(global, ant->tab) == 1)
	{
		//what_inside_pathcpy(global->lst);
		while (ft_strcmp(here, ant->end) != 0)
			here = search_path(global, ant, here);
		ft_printf("fin de la premiere boucle : %s\n", here);
		here = move_back(global, ant, here);
		ft_printf("fin de la deuxieme boucle : %s\n", here);
	}

	/*while (i < 14)
	{
		ft_printf("%d\n", ant->tab[i]);
		i++;
	}*/

	while (global->lst->pathcpy != NULL)
	{
		ft_printf("strcpy : %s\n", global->lst->pathcpy->strcpy);
		global->lst->pathcpy = global->lst->pathcpy->next;
	}
	//ft_printf("here final : %s\n", here);
}