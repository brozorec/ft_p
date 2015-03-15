/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:14:28 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/15 18:25:44 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"


void		send_msg(char *buff, int cfd)
{
	int 				ret;

	if ((ret = send(cfd, buff, ft_strlen(buff), MSG_DONTWAIT)) == -1)
		err_msg("send() send_msg failed.\n");
}

char		*receive_msg(int cfd)
{
	int 				matched;
	char				buff_recv[2];
	char				*msg;
	char				*save;

	msg = 0;
	matched = 0;
	while (recv(cfd, &buff_recv[0], 1, 0) > 0)
	{
		buff_recv[1] = '\0';
		if (buff_recv[0] == '\r')
			++matched;
		else if (matched == 1)
		{
			if (buff_recv[0] == '\n')
			{
				msg[ft_strlen(msg) - 1] = '\0';
				return (msg);
			}
			else
				matched = 0;
		}
		save = ft_strdup(msg);
		free(msg);
		msg = ft_strjoin(save, buff_recv);
		free(save);
	}
	return (msg);
}

void		examine_input(char *buff_input, int cfd)
{
	char				*buff;

	if (ft_strncmp(buff_input, "get", 3) == 0)
	{
		send_msg(buff_input, cfd);
		receive_file(cfd, buff_input + 4);
	}
	else if (ft_strncmp(buff_input, "put", 3) == 0)
	{
		send_msg(buff_input, cfd);
		receive_file(cfd, buff_input + 4);
	}
	else
	{
		send_msg(buff_input, cfd);
		buff = receive_msg(cfd);
		ft_putendl(buff);
		ft_strdel(&buff);
	}
	if (ft_strcmp(buff_input, "quit") == 0)
		exit(0);
}

void		do_interaction(int cfd)
{
	char				*buff;
	int 				ret;

	buff = 0;
	ft_putstr("@>");
	while ((ret = get_next_line(0, &buff)) > 0)
	{
		if (ft_strlen(buff) == 0)
		{
			ft_putstr("@>");
			continue;
		}
		examine_input(buff, cfd);
		ft_strdel(&buff);
		ft_putstr("@>");
	}
	close(cfd);
}
