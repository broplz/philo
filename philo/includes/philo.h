#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_node {
	char *next;
	char *prev;
} t_node;

typedef struct s_circle_list {
	t_node *head;
	t_node *tail;
} t_circle_list;

typedef struct s_philo {
	int			name;
	unsigned	left_fork;
	unsigned	right_fork;
	t_table		*table;
} t_philo;

typedef struct s_table {
	pthread_mutex_t *forks[PHT_SIZE];
	t_c_list *circle;
	t_philo	*philo;
} t_table;

#endif
