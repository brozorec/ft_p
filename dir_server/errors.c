/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:46:22 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 19:30:31 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		fatal(char *err)
{
	ft_putstr_fd(err, 2);
	exit(-1);
}

void		free_tab(char **tab)
{
	int			i;

	i = 0;
	while (tab && tab[i])
	{
		ft_strdel(&tab[i]);
		++i;
	}
	ft_strdel(tab);
}
