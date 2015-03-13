/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 18:10:25 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/13 18:38:53 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		examine_buff(char *buff, int cfd, char *starting_dir)
{
	char				**tab;

	tab = ft_strsplit(buff, ' ');
	if (ft_strcmp(tab[0], "ls") == 0)
		do_ls(tab, cfd);
	else if (ft_strcmp(tab[0], "pwd") == 0)
		do_pwd(tab, cfd);
	else if (ft_strcmp(tab[0], "cd") == 0)
		do_cd(tab, cfd, starting_dir);
	else if (ft_strcmp(tab[0], "get") == 0)
		send_file(tab, cfd);
	else if (ft_strcmp(buff, "quit") == 0)
	{
		if (send(cfd, "SUCCESS\nConnection closed.\r\n", 28, MSG_DONTWAIT) == -1)
			err_msg("send() examine_buff failed.\n");
		close(cfd);
		exit(0);
	}
	else
	{
		if (send(cfd, "ERROR\nCommand line.\r\n", 21, MSG_DONTWAIT) == -1)
			err_msg("send() examine_buff failed.\n");
	}
	free(tab);
}

void		forked_process(int cfd)
{
	char				buff[1024];
	char				*starting_dir;
	int 				ret;

	starting_dir = take_cwd();
	while ((ret = recv(cfd, buff, 1023, 0)) > 0)
	{
		// dump(buff, ret);
		buff[ret] = '\0';
		if (ft_strlen(buff) == 0)
			continue ;
		examine_buff(buff, cfd, starting_dir);
	}
	err_msg("Connection closed by client.\n");
}
