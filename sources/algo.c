/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:53 by jcharloi          #+#    #+#             */
/*   Updated: 2017/12/23 22:37:29 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A GERER :
** Le cas où quand je fais demi-tour et que je replace ma recherche de chemin
** et qu'il me retrouve le meme chemin où je dois refaire demi-tour :
**		- Lorsque ant->boucle est à 1, je cherche une room dont l'un des tubes est à 3
**		tout en revenant en arriere, je dois enregistrer la room d'avant pour que
**		quand je cherche a nouveau un chemin, je ne passe pas 2x dans la room d'avant
*/

#include "lem_in.h"

void	free_last_lst(t_global *global)
{
	t_lst	*tmp;

	tmp = global->lst;
	while (tmp->next != NULL && tmp->next->next != NULL)
		tmp = tmp->next;
	free(tmp->next->path);
	tmp->next->path = NULL;
	free(tmp->next);
	tmp->next = NULL;
}

void	show_paths(t_global *global)
{
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

void	start_algo(t_global *global, t_ant *ant)
{
	ant->here = ant->start;
	//init ant->tab
	init_tab(global->pipe, ant);
	//get all paths
	get_paths(global, ant);
	//free last link
	free_last_lst(global);
	//show every path
	show_paths(global);
}
