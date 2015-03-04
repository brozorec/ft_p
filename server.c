/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:23:03 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/04 20:20:52 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			create_socket(int port)
{
	int					sfd;
	struct protoent		*proto;
	struct sockaddr_in	host_addr;

	if ((proto = getprotobyname("tcp")) == 0)
		err_msg("getprotobyname() failed.\n");
	if ((sfd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		err_msg("socket() failed.\n");
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(port);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ft_memset(&(host_addr.sin_zero), '\0', 8);
	if (bind(sfd, (const struct sockaddr *)&host_addr, sizeof(host_addr)) == -1)
		err_msg("bind() failed.\n");
	if (listen(sfd, 10) == -1)
		err_msg("listen() failed.\n");
	return (sfd);
}

int			main(int ac, char **av)
{
	int				sfd;
	int				port;

	if (ac != 2)
		usage(av[0]);
	if ((port = ft_atoi(av[1])) == 0)
		usage(av[0]);
	sfd = create_socket(port);
	close(sfd);
	return (0);
}



