/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 14:14:57 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/15 16:09:14 by bbarakov         ###   ########.fr       */
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

char 		*resolve_path(char *path)
{
	char 			*new_path;
	int 			i;
	int				j;

	i = 0;
	j = 0;
	new_path = ft_strnew(ft_strlen(path));
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] != '.' && j-- > 0)
			new_path[j--] = '\0';
		else if (path[i] == '.' && path[i + 1] == '.')
		{
			if (j > 0)
				new_path[--j] = '\0';
			while (new_path[j] != '/' && j >= 0)
				new_path[j--] = '\0';
			if (j >= 0)
				new_path[j] = '\0';
			++i;
			--j;
		}
		else
			new_path[j] = path[i];
		++j;
		++i;
	}
	ft_strdel(&path);
	return (new_path);
}

void		change_dir(char *dir, int cfd)
{
	extern char 	**environ;

	if (chdir(dir) == -1)
	{
		if (send(cfd, "ERROR\nNo such directory.\r\n", 26, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
		return ;
	}
	change_env_var("PWD=", dir, &environ);
	if (send(cfd, "SUCCESS\nCurrent working directory of server changed to:\n", 56, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, dir, ft_strlen(dir), MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
	if (send(cfd, "\r\n", 2, MSG_DONTWAIT) == -1)
		err_msg("send() do_cd failed.\n");
}

void		do_cd(char **tab, int cfd, char *dir_base)
{
	char 				*new_dir;
	char 				*current_dir;
	int					len;

	if (tab[1] == 0 || tab[2] != 0)
	{
		if (send(cfd, "ERROR\nUsage cd: cd <path>\r\n", 27, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
	}
	len = ft_strlen(tab[1]) - 1;
	if (tab[1][len] == '/')
		tab[1][len] = '\0';
	current_dir = take_cwd(0);
	new_dir = resolve_path(ft_str3join(current_dir, "/", tab[1]));
	ft_strdel(&current_dir);
	len = ft_strlen(dir_base);
	if (ft_strncmp(dir_base, new_dir, len) == 0 && (new_dir[len] == '\0' || new_dir[len] == '/'))
	{
		change_dir(new_dir, cfd);
	}
	else
	{
		if (send(cfd, "ERROR\nNot allowed to change to this directory.\r\n", 48, MSG_DONTWAIT) == -1)
			err_msg("send() do_cd failed.\n");
	}
	ft_strdel(&new_dir);
}
