/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 17:18:19 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/07 18:06:57 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void		open_and_send(char *file, int cfd)
{
	int			fd;
	char		buff[1024];
	int			ret;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		if (send(cfd, "ERROR\nNo such file.\n", 20, MSG_DONTWAIT) == -1)
			err_msg("send() open_and_send failed.\n");
		return ;
	}
	while ((ret = read(fd, buff, 1023)) > 0)
	{
		buff[ret] = '\0';
		if (send(cfd, buff, ft_strlen(buff), MSG_DONTWAIT) == -1)
			err_msg("send() open_and_send failed.\n");
	}
	close(fd);
}

void		send_file(char **tab, int cfd)
{
	if (tab[1] == 0 || tab[2] != 0)
	{
		if (send(cfd, "ERROR\nUsage get: get <file>\n", 28, MSG_DONTWAIT) == -1)
			err_msg("send() send failed.\n");
		return ;
	}
	open_and_send(tab[1], cfd);
}
