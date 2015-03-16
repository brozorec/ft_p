/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:14:28 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 18:24:46 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			send_msg(char *buff, int cfd)
{
	int					i;

	i = 0;
	while (buff[i])
	{
		if (send(cfd, &buff[i], 1, MSG_DONTWAIT) == -1)
			return (0);
		++i;
	}
	if (send(cfd, "\r\n", 2, MSG_DONTWAIT) == -1)
		return (0);
	return (1);
}

char		*check_for_match(char *buff_recv, char *msg, int *matched)
{
	if (buff_recv[0] == '\r')
		++(*matched);
	else if (*matched == 1)
	{
		if (buff_recv[0] == '\n')
		{
			msg[ft_strlen(msg) - 1] = '\0';
			return (msg);
		}
		else
			*matched = 0;
	}
	return (0);
}

char		*receive_msg(int cfd)
{
	int					matched;
	char				buff_recv[2];
	char				*msg;
	char				*save;

	msg = 0;
	matched = 0;
	while (recv(cfd, &buff_recv[0], 1, 0) > 0)
	{
		buff_recv[1] = '\0';
		if ((save = check_for_match(buff_recv, msg, &matched)) != 0)
			return (save);
		save = ft_strdup(msg);
		free(msg);
		msg = ft_strjoin(save, buff_recv);
		free(save);
	}
	if (msg == 0)
		msg = ft_strdup("Connection was closed by server.");
	return (msg);
}

void		examine_input(char *buff_input, int cfd)
{
	char				*buff;
	int					ret;

	if (ft_strncmp(buff_input, "put", 3) == 0)
		send_file(cfd, buff_input);
	else
	{
		ret = send_msg(buff_input, cfd);
		if (ft_strncmp(buff_input, "get", 3) == 0 && ret == 1)
			receive_file(cfd, buff_input + 4);
		else if (ret == 1)
		{
			buff = receive_msg(cfd);
			ft_putendl(buff);
			ft_strdel(&buff);
		}
		if (ft_strcmp(buff_input, "quit") == 0)
		{
			ft_strdel(&buff_input);
			exit(0);
		}
	}
}

void		do_interaction(int cfd)
{
	char				*buff_input;
	int					ret;

	buff_input = 0;
	ft_putstr("@>");
	while ((ret = get_next_line(0, &buff_input)) >= 0)
	{
		if (ret == 0)
		{
			close_connection(cfd);
			continue ;
		}
		if (ft_strlen(buff_input) == 0)
		{
			ft_putstr("@>");
			continue;
		}
		examine_input(buff_input, cfd);
		ft_strdel(&buff_input);
		ft_putstr("@>");
	}
	close(cfd);
}
