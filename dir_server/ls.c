/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 15:52:44 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/13 14:29:45 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			read_dir_loop(DIR *dirp, int cfd)
{
	struct dirent		*entry;
	char				cwd[4096];

	while (1)
	{
		errno = 0;
		if ((entry = readdir(dirp)) != 0)
		{
			if (send(cfd, entry->d_name, ft_strlen(entry->d_name), MSG_DONTWAIT) == -1)
				err_msg("send() readdir failed.\n");
			if (send(cfd, "\n", 1, MSG_DONTWAIT) == -1)
				err_msg("send() readdir failed.\n");
		}
		if (entry == 0 && errno == 0)
			break ;
	}
	if (send(cfd, "SUCCESS\nThe content of ", 23, MSG_DONTWAIT) == -1)
		err_msg("send() readdir failed.\n");
	getcwd(cwd, 4095);
	if (send(cfd, cwd, ft_strlen(cwd), MSG_DONTWAIT) == -1)
		err_msg("send() readdir failed.\n");
	if (send(cfd, " was listed.\r\n", 14, MSG_DONTWAIT) == -1)
		err_msg("send() readdir failed.\n");
}

void			do_ls(char **tab, int cfd)
{
	DIR					*dirp;

	if (tab[1] != 0)
	{
		if (send(cfd, "ERROR\nUsage ls: ls <no options>\r\n", 33, MSG_DONTWAIT) == -1)
			err_msg("send() readdir failed.\n");
		return ;
	}
	if ((dirp = opendir(".")) != 0)
	{
		read_dir_loop(dirp, cfd);
		closedir(dirp);
	}
	else
		err_msg("opendir() failed.\n");
}
