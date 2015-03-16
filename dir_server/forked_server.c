/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 18:10:25 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 19:32:36 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			send_msg(char *buff, int cfd)
{
	int 				i;

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
	else if ((*matched) == 1)
	{
		if (buff_recv[0] == '\n')
		{
			msg[ft_strlen(msg) - 1] = '\0';
			return (msg);
		}
		else
			(*matched) = 0;
	}
	return (0);
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
		if ((save = check_for_match(buff_recv, msg, &matched)) != 0)
			return (save);
		save = ft_strdup(msg);
		free(msg);
		msg = ft_strjoin(save, buff_recv);
		free(save);
	}
	if (msg == 0)
		msg = ft_strdup("Connection was closed by client.");;
	return (msg);
}

void		examine_buff(char *buff, int cfd, char *dir_base)
{
	char				**tab;

	tab = ft_strsplit(buff, ' ');
	if (ft_strcmp(tab[0], "ls") == 0)
		do_ls(tab, cfd);
	else if (ft_strcmp(tab[0], "pwd") == 0)
		do_pwd(tab, cfd);
	else if (ft_strcmp(tab[0], "cd") == 0)
		do_cd(tab, cfd, dir_base);
	else if (ft_strcmp(tab[0], "get") == 0)
		send_file(tab, cfd);
	else if (ft_strcmp(tab[0], "put") == 0)
		receive_file(tab[1], cfd);
	else if (ft_strcmp(buff, "quit") == 0)
	{
		send_msg("SUCCESS\nConnection closed.", cfd);
		close(cfd);
		ft_strdel(&dir_base);
		free_tab(tab);
		exit(0);
	}
	else
		send_msg("ERROR\nCommand line.", cfd);
	free_tab(tab);
}

void		forked_process(int cfd)
{
	char				*buff;
	char				*dir_base;

	dir_base = take_cwd(0);
	while ((buff = receive_msg(cfd)) != 0)
	{
		if (ft_strlen(buff) == 0)
			continue ;
		examine_buff(buff, cfd, dir_base);
		ft_strdel(&buff);
	}
	ft_strdel(&dir_base);
	fatal("Connection closed by client.\n");
	close(cfd);
}
