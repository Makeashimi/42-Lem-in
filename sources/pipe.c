/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:41:10 by jcharloi          #+#    #+#             */
/*   Updated: 2018/01/09 20:05:35 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_pipe	*create_pipe(t_ant *ant, t_global *global)
{
	t_pipe		*pipe;

	if (!(pipe = (t_pipe*)malloc(sizeof(t_pipe))))
		error(ant, global, "Malloc error");
	ft_memset(pipe, 0, sizeof(t_pipe));
	return (pipe);
}

static t_pipe	*link_pipe(t_pipe *pipe, t_ant *ant, t_global *global)
{
	t_pipe		*tmp;

	tmp = pipe;
	if (tmp == NULL)
	{
		pipe = create_pipe(ant, global);
		return (pipe);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_pipe(ant, global);
	return (pipe->next);
}

int				find_pipe(char *str)
{
	int		i;

	i = 0;
	if (str_nbr_i(str, ' ') != 0 || str_nbr_i(str, '-') != 1)
		return (0);
	if (str[i] == '-')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			i++;
			break ;
		}
		i++;
	}
	if (str[i] == 0)
		return (0);
	return (1);
}

static void		get_pipe(t_pipe *pipe, char *str)
{
	int		i;
	int		o;

	i = 0;
	o = 0;
	pipe->s1 = (char*)malloc(sizeof(char) * ft_strsrchi(str, '-') + 1);
	while (str[i] != '-')
	{
		pipe->s1[i] = str[i];
		i++;
	}
	pipe->s1[i] = '\0';
	i++;
	pipe->s2 = (char*)malloc(sizeof(char) * ft_strlen(str + i) + 1);
	while (str[i] != '\0')
	{
		pipe->s2[o] = str[i];
		i++;
		o++;
	}
	pipe->s2[o] = '\0';
}

void			check_pipe(t_ant *ant, t_global *global, t_ant *cpy, t_pipe *pipe)
{
	if (cpy == NULL)
		error(ant, global, "No pipe");
	while (cpy != NULL)
	{
		while (cpy != NULL && cpy->str[0] == '#')
			cpy = cpy->next;
		if (cpy == NULL || find_pipe(cpy->str) == 0)
			break ;
		pipe = link_pipe(pipe, ant, global);
		if (global->pipe == NULL)
			global->pipe = pipe;
		get_pipe(pipe, cpy->str);
		cpy = cpy->next;
	}
}
