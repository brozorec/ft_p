/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 16:56:25 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 19:20:01 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char		*take_env_var(void)
{
	extern char			**environ;
	char				*path;
	int					i;

	i = 0;
	while (environ && environ[i])
	{
		if (ft_strncmp(environ[i], "PWD=", 4) == 0)
		{
			path = ft_strdup(&environ[i][4]);
			return (path);
		}
		++i;
	}
	return (0);
}

char		*take_cwd(int flag_print)
{
	char		cwd[4096];
	char		*path;

	if ((path = take_env_var()) != 0)
	{
		if (flag_print == 1)
		{
			ft_putstr(path);
			ft_putstr("\n");
		}
	}
	else
	{
		getcwd(cwd, 4095);
		if (flag_print == 1)
		{
			ft_putstr(cwd);
			ft_putstr("\n");
		}
		path = ft_strdup(cwd);
	}
	return (path);
}

void		do_pwd(char **tab, int cfd)
{
	char		*path;

	if (tab[1] != 0)
	{
		send_msg("ERROR\nUsage pwd: pwd <no options>", cfd);
		return ;
	}
	path = take_cwd(1);
	if (send(cfd, "SUCCESS\nCurrent working ", 24, 0) == -1)
		fatal("Connection closed by client.\n");
	if (send(cfd, "directory of server is as follows:\n", 35, 0) == -1)
		fatal("Connection closed by client.\n");
	if (send(cfd, path, ft_strlen(path), 0) == -1)
		fatal("Connection closed by client.\n");
	if (send(cfd, "\r\n", 2, 0) == -1)
		fatal("Connection closed by client.\n");
	ft_strdel(&path);
}
