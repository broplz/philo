#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_args
{
	int	sleep;
	int	eat;
	int	think;
	int	philos;
}				t_args;

typedef struct	s_philo
{
	int				name;
	struct s_philo	*prev;
	struct s_philo	*next;
	unsigned		left_fork;
	unsigned		right_fork;
}				t_philo;

typedef struct	s_table
{
	int				size;
	t_philo			head;
	t_args			args;
//	pthread_mutex_t	*forks[PHT_SIZE];
}				t_table;

#endif
