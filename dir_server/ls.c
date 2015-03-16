/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:52:44 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 19:36:26 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			read_dir_loop(DIR *dirp, int cfd)
{
	struct dirent		*entry;
	char				*cwd;

	while (1)
	{
		errno = 0;
		if ((entry = readdir(dirp)) != 0)
		{
			if (send(cfd, entry->d_name, ft_strlen(entry->d_name), 0) == -1)
				fatal("Connection closed by client.\n");
			if (send(cfd, "\n", 1, MSG_DONTWAIT) == -1)
				fatal("Connection closed by client.\n");
		}
		if (entry == 0 && errno == 0)
			break ;
	}
	ft_memdel((void **)&entry);
	if (send(cfd, "SUCCESS\nThe content of ", 23, MSG_DONTWAIT) == -1)
		fatal("Connection closed by client.\n");
	cwd = take_env_var();
	if (send(cfd, cwd, ft_strlen(cwd), MSG_DONTWAIT) == -1)
		fatal("Connection closed by client.\n");
	ft_strdel(&cwd);
	if (send(cfd, " was listed.\r\n", 14, MSG_DONTWAIT) == -1)
		fatal("Connection closed by client.\n");
}

void			do_ls(char **tab, int cfd)
{
	DIR					*dirp;

	if (tab[1] != 0)
	{
		send_msg("ERROR\nUsage ls: ls <no options>", cfd);
		return ;
	}
	if ((dirp = opendir(".")) != 0)
	{
		read_dir_loop(dirp, cfd);
		closedir(dirp);
	}
	else
		ft_putstr_fd("Cannot open current directory.\n", 2);
}
