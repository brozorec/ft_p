/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:46:22 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 17:00:06 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		close_connection(int cfd)
{
	char		*buff_input;

	ft_putstr("\nDo you want to exit? (y/..) ");
	get_next_line(0, &buff_input);
	if (ft_strcmp(buff_input, "y") == 0)
	{
		ft_strdel(&buff_input);
		close(cfd);
		exit(0);
	}
	ft_putstr("@>");
}

void		err_msg(char *err)
{
	ft_putstr_fd(err, 2);
}

void		fatal(char *str)
{
	err_msg(str);
	exit(-1);
}
