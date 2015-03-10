/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 17:12:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/10 17:51:32 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			receive_file(int cfd)
{
	int				ret;
	char			buff_recv[1024];
	int				size_file;

	if ((ret = recv(cfd, buff_recv, 1023, 0)) == -1)
		err_msg("recv() failed receive_file.\n");
	buff_recv[ret] = '\0';
	if (ft_strncmp(buff_recv, "OK", 2) == 0)
	{
		if ((ret = recv(cfd, buff_recv, 1023, 0)) == -1)
			err_msg("recv() failed receive_file.\n");
		buff_recv[ret] = '\0';
		printf("%s\n", buff_recv);
		size_file = ft_atoi(buff_recv);
		printf("%d\n", size_file);
	}
	else
		ft_putstr(buff_recv);
}
