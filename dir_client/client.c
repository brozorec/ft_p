/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 12:39:43 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/09 18:29:29 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

void		send_msg(char *buff, int cfd)
{
	int 				ret;

	if ((ret = send(cfd, buff, ft_strlen(buff) + 1, MSG_DONTWAIT)) == -1)
		err_msg("send() send_msg failed.\n");
}

int 		receive_msg(int cfd)
{
	char				buff_recv[11];
	int 				ret;

	ret = recv(cfd, buff_recv, 10, 0);
	if (ret > 0)
	{
		buff_recv[ret] = '\0';
		ft_putstr(buff_recv);
	}
	return (ret);
}

void		do_interaction(int cfd)
{
	// char				buff_recv[11];
	char				*buff;
	int 				ret;

	buff = 0;
	// send(cfd, "ok", 2, 0);
	// recv(cfd, buff_recv, 10, MSG_DONTWAIT);
	ft_putstr("@>");
	while ((ret = get_next_line(0, &buff)) > 0)
	{
		// buff[ret] = '\r';
		// buff[ret + 1] = '\n';
		send_msg(buff, cfd);
		while (receive_msg(cfd) != -1)
			continue;
		ft_putstr("@>");
	}
	close(cfd);
}

int			main(int ac, char **av)
{
	int					cfd;
	int					port;

	if (ac != 3)
		usage(av[0]);
	if ((port = ft_atoi(av[2])) == 0)
		err_msg("Enter valid port.\n");
	cfd = create_socket(av[1], port);
	do_interaction(cfd);
	return (0);
}
