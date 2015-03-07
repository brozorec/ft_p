/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 16:56:25 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/07 18:42:52 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

void		print_cwd(void)
{
	char		cwd[4096];
	char		*path;

	if ((path = take_env_var()) != 0)
	{
		ft_putstr(path);
		ft_putstr("\n");
		free(path);
	}
	else
	{
		getcwd(cwd, 4095);
		ft_putstr(cwd);
		ft_putstr("\n");
	}
}

void		do_pwd(char **tab, int cfd)
{

	if (tab[1] != 0)
	{
		if (send(cfd, "ERROR\nUsage pwd: pwd <no options>\n", 34, MSG_DONTWAIT) == -1)
			err_msg("send() pwd failed.\n");
		return ;
	}
	print_cwd();
	if (send(cfd, "SUCCESS\n", 8, MSG_DONTWAIT) == -1)
		err_msg("send() pwd failed.\n");
}
