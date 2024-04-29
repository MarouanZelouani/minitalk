/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:59:03 by mzelouan          #+#    #+#             */
/*   Updated: 2024/04/29 08:55:22 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char		*g_msg;

static void	stor(int *i, int *j)
{
	(*j)++;
	(*i) = 7;
	if (*j == ft_strlen(g_msg) + 1)
	{
		free(g_msg);
		ft_print("mgs wsal\n");
	}
}

void	signal_handler(int signal, siginfo_t *server, void *ucontext)
{
	unsigned char	c;
	static int		i = 7;
	static int		j = 0;

	(void)signal;
	(void)ucontext;
	c = g_msg[j];
	if ((c >> i & 1) == 1)
	{
		if (kill(server->si_pid, SIGUSR1) == -1)
			ft_print("Error : kill function!\n");
	}
	else if ((c >> i & 1) == 0)
	{
		if (kill(server->si_pid, SIGUSR2) == -1)
			ft_print("Error : kill function!\n");
	}
	i--;
	if (i < 0)
		stor(&i, &j);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	if (ac != 3 || !av[1][0] || !av[2][0])
		ft_print("Usage : ./client <server_pid> <message>\n");
	server_pid = ft_atoi(av[1]);
	if (check_pid(av[1]) || server_pid <= 0)
		ft_print("Error : Bad ID\n");
	g_msg = ft_strdup(av[2]);
	if (kill(server_pid, SIGUSR1))
		ft_print("Error: kill function!\n");
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_print("Error : sigaction function");
	while (1)
		pause();
}
