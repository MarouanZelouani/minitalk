/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:59:03 by mzelouan          #+#    #+#             */
/*   Updated: 2024/04/20 21:34:45 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int		g_len;

void	send_signal(int server_pid, unsigned char c)
{
	int	i;
	int	bit;

	i = 8;
	while (i--)
	{
		bit = c >> i & 1;
		if (bit == 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				ft_print_error("Error : kill function!\n");
		}
		else if (bit == 0)
		{
			if (kill(server_pid, SIGUSR2) == -1)
				ft_print_error("Error : kill function!\n");
		}
		usleep(1000);
	}
}

void	signal_handler(int signal)
{
	static int	counter;

	counter = 0;
	if (signal == SIGUSR1)
		counter++;
	if (counter == g_len)
		ft_putstr_fd("message was send with success !\n", 1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;
	int					i;

	i = -1;
	if (ac != 3 || !av[1][0] || !av[2][0])
		ft_print_error("Usage : ./client <server_pid> <message>\n");
	g_len = ft_strlen(av[2]);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_print_error("Error : sigaction function\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_print_error("Error : sigaction function");
	server_pid = ft_atoi(av[1]);
	if (check_pid(av[1]) || server_pid <= 0)
		ft_print_error("Error : Bad ID\n");
	while (av[2][++i])
		send_signal(server_pid, av[2][i]);
	send_signal(server_pid, '\0');
	return (0);
}
