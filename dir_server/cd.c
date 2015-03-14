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
	char 			buff[1024];

	dir_up = ft_str3join(take_env_var(), "/", dir);
	if (chdir(dir_up) == -1)
	{
		if (send(cfd, "ERROR\nNo such directory.\r\n", 26, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
		return ;
	}
	dir_up = getcwd(buff, 1023);
	change_env_var("PWD=", dir_up, &environ);
	if (send(cfd, "SUCCESS\nCurrent working directory of server changed to:\n", 56, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, dir_up, ft_strlen(dir_up), MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, "\r\n", 2, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
}

int			examine_path(char *path)
{
	int				i;
	int				level;

	i = 0;
	level = 0;
	while (path[i])
	{
		if (path[i] != '/' && path[i] != '.')
		{
			++level;
			while (path[i] && path[i] != '/')
				++i;
			if (path[i] == '\0')
				return (level);
		}
		else if (path[i] == '.' && path[i + 1] == '.')
		{
			++i;
			--level;
		}
		++i;
	}
	return (level);
}

int			do_cd(char **tab, int cfd, int current_level)
{
	int				level;
	int				new_level;

	new_level = current_level;
	if (tab[1] == 0 || tab[2] != 0)
	{
		if (send(cfd, "ERROR\nUsage cd: cd <path>\r\n", 27, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
		return (new_level);
	}
	level = examine_path(tab[1]);
	printf("%d\n", current_level);
	printf("%d\n", level);
	if ((current_level + level) >= 0)
	{
		change_dir(tab[1], cfd);
		new_level = current_level + level;
	}
	else
	{
		if (send(cfd, "ERROR\nNot allowed to change to this directory.\r\n", 48, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
	}
	return (new_level);
}
