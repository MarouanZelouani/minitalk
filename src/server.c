/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:59:08 by mzelouan          #+#    #+#             */
/*   Updated: 2024/04/20 21:36:21 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	signal_handler(int signal, siginfo_t *client, void *ucontext)
{
	static unsigned char	received_byte;
	static int				bit_counter;

	(void)ucontext;
	if (signal == SIGUSR1)
		received_byte |= (1 << (7 - bit_counter));
	bit_counter++;
	if (bit_counter == 8)
	{
		write(1, &received_byte, 1);
		if (kill(client->si_pid, SIGUSR1) == -1)
			ft_print_error("Error : kill function\n");
		if (received_byte == '\0')
			write(1, "\n", 1);
		received_byte = 0;
		bit_counter = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	ft_putstr_fd("Server ID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_print_error("Error : sigaction function");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_print_error("Error : sigaction function");
	ft_putstr_fd("Server is running...\n", 1);
	while (1)
		sleep(1);
	return (0);
}
