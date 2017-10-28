/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsrchi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:41:33 by jcharloi          #+#    #+#             */
/*   Updated: 2017/01/05 15:54:29 by jcharloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strsrchi(const char *s, int c)
{
	unsigned char	*ptr_s;
	int				i;

	ptr_s = (unsigned char*)s;
	i = 0;
	while (ptr_s[i] != '\0')
	{
		if (ptr_s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
