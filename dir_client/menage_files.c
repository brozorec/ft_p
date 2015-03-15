/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:12:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/15 18:31:19 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

// void			get_content_file(int cfd, char *name_file)
// {
// 	char			*buff;
// 	int				fd_file;
// 	int				ret;

// 	if ((fd_file = open(name_file, O_TRUNC | O_CREAT | O_RDWR, S_IRWXU)) == -1)  // ACCESSPERMS
// 		err_msg("open() get_content_file failed.\n");
// 	if ((buff = receive_msg(cfd)) != 0)
// 	{
// 		if ((ret = write(fd_file, buff, ft_strlen(buff))) == -1 )
// 			err_msg("write() get_content_file failed.\n");
// 		close(fd_file);
// 		ft_strdel(&buff);
// 	}
// 	buff = receive_msg(cfd);
// 	ft_putendl(buff);
// 	ft_strdel(&buff);
// }

void			get_content_file(int cfd, char *name_file, int size)
{
	char			*buff;
	char			buff_file[2];
	int				fd_file;
	int				ret;
	int				i;

	i = 0;
	if ((fd_file = open(name_file, O_TRUNC | O_CREAT | O_RDWR, ACCESSPERMS)) == -1)
		err_msg("open() get_content_file failed.\n");
	while (i < size)
	{
		if ((ret = recv(cfd, buff_file, 1, 0)) != 0)
		{
			buff_file[1] = '\0';
			i += ret;
			if (write(fd_file, buff_file, 1) == -1 )
				err_msg("write() get_content_file failed.\n");
		}

	}
	close(fd_file);
	buff = receive_msg(cfd);
	ft_putendl(buff);
	ft_strdel(&buff);
}

void			receive_file(int cfd, char *file)
{
	char			*buff;
	char			*name;
	int				size;

	buff = receive_msg(cfd);
	if (ft_strncmp(buff, "OK", 2) == 0)
	{
		ft_strdel(&buff);
		buff = receive_msg(cfd);
		size = ft_atoi(buff);
		if ((name = ft_strrchr(file, '/')) != 0)
			get_content_file(cfd, name + 1, size);
		else
			get_content_file(cfd, file, size);
	}
	else
	{
		ft_putendl(buff);
		ft_strdel(&buff);
	}
}
