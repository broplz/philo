#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

#define PT pthread_t
#define PMT pthread_mutex_t
#define PML pthread_mutex_lock
#define PMU pthread_mutex_unlock
#define PHILO_AMOUNT ft_atoi(av[1])
#define ULL unsigned long long

typedef struct s_philo	t_philo;

typedef struct		s_var
{
	int				p_amount;
	int				sleep_time;
	int				eat_time;
	int				think_time;
	int				number_of_meals;
	int				dead;
	int				full;
	PMT				*forks;
	PMT				print;
	t_philo 		*philo;
}					t_var;

typedef struct		s_philo
{
	PT				thread;
	int				name;
	unsigned		left_fork;
	unsigned		right_fork;
	ULL				last_eat;
	t_var			*var;
}					t_philo;

//typedef struct		s_table
//{
//	PMT				*forks;
//}					t_table;

//typedef struct		s_args
//{
//	t_var			var;
//	t_philo			*philo;
//	t_table			*table;
//}					t_args;

#endif