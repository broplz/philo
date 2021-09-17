#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

#define PMT pthread_mutex_t
#define PML pthread_mutex_lock
#define PMU pthread_mutex_unlock

typedef struct		s_var
{
	int				p_amount;
	int				sleep_time;
	int				eat_time;
	int				think_time;
	int				number_of_meals;
}					t_var;

typedef struct		s_philo
{
	int				name;
	unsigned		left_fork;
	unsigned		right_fork;
}					t_philo;

typedef struct		s_table
{
	pthread_mutex_t	*forks;
}					t_table;

typedef struct		s_args
{
	t_philo			*philo;
	t_table			*table;
	t_var			var;
}					t_args;

#endif