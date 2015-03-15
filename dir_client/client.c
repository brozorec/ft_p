/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:39:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/15 18:14:30 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		sig_pipe(int sig)
{
	if (sig == 13)
		exit(0);
}

int			create_socket(char *addr, int port)
{
	int					cfd;
	struct protoent		*proto;
	struct sockaddr_in	client_addr;

	if ((proto = getprotobyname("tcp")) == 0)
		err_msg("getprotobyname() failed.\n");
	if ((cfd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		err_msg("socket() failed.\n");
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	client_addr.sin_addr.s_addr = inet_addr(addr);
	ft_memset(&(client_addr.sin_zero), '\0', 8);
	if (connect(cfd, (const struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
		err_msg("connect() failed.\n");
	return (cfd);
}

int			main(int ac, char **av)
{
	int					cfd;
	int					port;

	signal(SIGPIPE, sig_pipe);
	if (ac != 3)
		usage(av[0]);			// av[1] = hostaddr
	if ((port = ft_atoi(av[2])) == 0)
		err_msg("Enter valid port.\n");
	cfd = create_socket(av[1], port);
	do_interaction(cfd);
	return (0);
}
