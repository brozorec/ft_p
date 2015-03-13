/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 14:14:57 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/13 19:01:21 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void		change_env_var(char *var, char *value, char ***env)
{
	int					i;
	int					cmp;

	i = 0;
	cmp = ft_strlen(var);
	while (*env && (*env)[i])
	{
		if (ft_strncmp((*env)[i], var, cmp) == 0)
		{
			(*env)[i] = 0;
			(*env)[i] = ft_strjoin(var, value);
			return ;
		}
		++i;
	}
}

void		change_dir(char *dir, int cfd)
{
	extern char 	**environ;
	char 			*dir_up;

	dir_up = ft_str3join(take_env_var(), "/", dir);
	if (chdir(dir_up) == -1)
	{
		if (send(cfd, "ERROR\nNo such directory.\r\n", 26, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
		return ;
	}
	change_env_var("PWD=", dir_up, &environ);
	if (send(cfd, "SUCCESS\nCurrent working directory of server changed to:\n", 56, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, dir_up, ft_strlen(dir_up), MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, "\r\n", 2, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
}

void		do_cd(char **tab, int cfd, char *starting_dir)
{
	if (tab[1] == 0 || tab[2] != 0)
	{
		if (send(cfd, "ERROR\nUsage cd: cd <path>\r\n", 27, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
		return ;
	}
	if (ft_strcmp(tab[1], "..") != 0)
		change_dir(tab[1], cfd);
}
