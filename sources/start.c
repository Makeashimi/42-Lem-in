/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/19 23:36:07 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst	*get_previous(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*previous;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	previous = tmp;
	return (previous);
}

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
	ft_printf("path : %s\n", tmp->str);
	ft_printf("pathcpy : %s\n", tmpcpy->strcpy);
}

void	what_inside_pathcpy(t_lst *previous, t_lst *lst)
{
	t_pathcpy	*tmpcpy;
	//previous = pathcpy
	t_path 		*tmp;
	//lst = dernier maillon vide path

	if (previous == NULL)
		return ;
	tmpcpy = previous->pathcpy;
	tmp = lst->path;
	while (tmpcpy->next != NULL)
	{
		tmp = link_path(lst);
		if (!(tmp->str = (char*)malloc(sizeof(char) * ft_strlen(tmpcpy->strcpy))))
			ft_error("Malloc error");
		tmp->str = ft_strcpy(tmp->str, tmpcpy->strcpy);
		tmp->str[ft_strlen(tmpcpy->strcpy)] = '\0';
		tmpcpy = tmpcpy->next;
	}
}

char	*search_path(t_global *global, t_ant *ant, char *here)
{
	t_pipe	*tmp;

	tmp = global->pipe;
	ant->i = 0;
	while (tmp != NULL)
	{
		if (ant->tab[ant->i] == 0 && (ft_strcmp(tmp->s1, here) == 0 || ft_strcmp(tmp->s2, here) == 0))
		{
			save_here(get_previous(global->lst), here);
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
			//ft_printf("maillon a supprimer : %s\n", tmp->strcpy);
			//ft_printf("maillon d'avant : %s\n", previous->strcpy);
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
	t_lst	*previous;
	t_lst	*tmp;
	char	*here;
	//int i = 0;

	here = ant->start;
	init_tab(global->pipe, ant);
	//while (check_tab_zero(global, ant->tab) == 1)
	//{
		previous = get_previous(global->lst);
		tmp = link_lst(&global->lst);
		what_inside_pathcpy(previous, tmp);
		while (ft_strcmp(here, ant->end) != 0)
			here = search_path(global, ant, here);
		//ft_printf("fin de la premiere boucle : %s\n", here);
		here = move_back(global, ant, here);
		//ft_printf("fin de la deuxieme boucle : %s\n", here);
		previous = get_previous(global->lst);
		tmp = link_lst(&global->lst);
		what_inside_pathcpy(previous, tmp);
		while (ft_strcmp(here, ant->end) != 0)
			here = search_path(global, ant, here);
		//ft_printf("fin de la premiere boucle : %s\n", here);
		here = move_back(global, ant, here);
		//ft_printf("fin de la deuxieme boucle : %s\n", here);
		print_lst(global->lst);
		ft_printf("\n");
	//}

	/*while (i < 14)
	{
		ft_printf("%d\n", ant->tab[i]);
		i++;
	}*/

	while (global->lst != NULL)
	{
		while (global->lst->path != NULL)
		{
			ft_printf("strcpy : %s\n", global->lst->path->str);
			global->lst->path = global->lst->path->next;
		}
		ft_printf("\n");
		global->lst = global->lst->next;
	}
}