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
#define LLU long long unsigned
#define PMI	pthread_mutex_init

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
	LLU				start_time;
	PMT				*forks;
	PMT				print;
	PT				monitoring;
	t_philo 		*philo;
}					t_var;

typedef struct		s_philo
{
	PT				thread;
	int				name;
	int				eat_counter;
	unsigned		left_fork;
	unsigned		right_fork;
	LLU				last_eat;
	t_var			*var;
}					t_philo;

#endif