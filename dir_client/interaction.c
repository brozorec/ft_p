/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:14:28 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/10 17:46:36 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"


void		send_msg(char *buff, int cfd)
{
	int 				ret;

	if ((ret = send(cfd, buff, ft_strlen(buff), MSG_DONTWAIT)) == -1)
		err_msg("send() send_msg failed.\n");
}

void		print_received_msg(int cfd)
{
	char				buff_recv[1024];
	int 				ret;
	int 				matched;

	matched = 0;
	while ((ret = recv(cfd, buff_recv, 1023, 0)) > 0)
	{
		buff_recv[ret] = '\0';
		if (ft_strstr(buff_recv, "\r\n") != 0)
		{
			ft_putstr(buff_recv);
			return ;
		}
		if (matched == 1)
		{
			if (buff_recv[0] == '\n')
			{
				ft_putstr(buff_recv);
				return ;
			}
			else
				matched = 0;
		}
		if (ft_strlen(buff_recv) > 0 && buff_recv[ret - 1] == '\r')
		{
			buff_recv[ret - 1] = '\0';
			matched++;
		}
		ft_putstr(buff_recv);
	}

}

void		examine_input(char *buff_input, int cfd)
{
	if (ft_strncmp(buff_input, "ls", 2) == 0)
	{
		send_msg(buff_input, cfd);
		print_received_msg(cfd);
	}
	else if (ft_strncmp(buff_input, "pwd", 3) == 0)
	{
		send_msg(buff_input, cfd);
		print_received_msg(cfd);
	}
	else if (ft_strncmp(buff_input, "get", 3) == 0)
	{
		send_msg(buff_input, cfd);
		receive_file(cfd);
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
