/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:39:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/17 17:31:16 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		sig_pipe(int sig)
{
	if (sig == 13)
	{
		err_msg("Connection closed by server.\n");
		return ;
	}
}

int			create_socket(char *host_name, char *port)
{
	int					cfd;
	struct addrinfo		hints;
	struct addrinfo		*res;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host_name, port, &hints, &res) != 0)
		fatal("Connection failed.\n");
	if ((cfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
		err_msg("socket() failed.\n");
	if (connect(cfd, res->ai_addr, res->ai_addrlen) < 0)
		fatal("Connection failed.\n");
	return (cfd);
}

int			main(int ac, char **av)
{
	int					cfd;

	signal(SIGPIPE, sig_pipe);
	if (ac != 3)
		fatal("Usage: client <addr> <port>\n");
	cfd = create_socket(av[1], av[2]);
	do_interaction(cfd);
	return (0);
}
