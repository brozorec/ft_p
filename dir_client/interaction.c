/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:14:28 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/12 13:28:47 by bbarakov         ###   ########.fr       */
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
	char				buff_recv[1024];
	char				*msg;
	int 				ret;
	int 				matched;

	msg = 0;
	matched = 0;
	while ((ret = recv(cfd, buff_recv, 1023, 0)) > 0)
	{
		buff_recv[ret] = '\0';
		if (ft_strstr(buff_recv, "\r\n") != 0)
		{
			buff_recv[ret - 2] = '\0';
			msg = ft_realloc(msg, ft_strlen(buff_recv) + 1);
			msg = ft_strcat(msg, buff_recv);
			return (msg);
		}
		else if (matched == 1)
		{
			if (buff_recv[0] == '\n')
				return (msg);
			else
				matched = 0;
		}
		else if (ft_strlen(buff_recv) > 0 && buff_recv[ret - 1] == '\r')
		{
			buff_recv[ret - 1] = '\0';
			matched++;
		}
		msg = ft_realloc(msg, ft_strlen(buff_recv) + 1);
		msg = ft_strcat(msg, buff_recv);
	}
	return (msg);
}

void		examine_input(char *buff_input, int cfd)
{
	if (ft_strncmp(buff_input, "ls", 2) == 0)
	{
		send_msg(buff_input, cfd);
		printf("%s\n", receive_msg(cfd));
	}
	else if (ft_strncmp(buff_input, "pwd", 3) == 0)
	{
		send_msg(buff_input, cfd);
		printf("%s\n", receive_msg(cfd));
	}
	else if (ft_strncmp(buff_input, "get", 3) == 0)
	{
		send_msg(buff_input, cfd);
		receive_file(cfd, buff_input + 4);
	}
	else
	{
		send_msg(buff_input, cfd);
		printf("%s\n", receive_msg(cfd));
	}
}

void		do_interaction(int cfd)
{
	char				*buff;
	int 				ret;

	buff = 0;
	ft_putstr("@>");
	while ((ret = get_next_line(0, &buff)) >= 0)
	{
		if (ft_strlen(buff) == 0)
		{
			ft_putstr("@>");
			continue;
		}
		examine_input(buff, cfd);
		ft_putstr("@>");
	}
	close(cfd);
}
