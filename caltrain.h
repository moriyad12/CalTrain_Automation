#include <pthread.h>

struct station {
	long long seated;
    long long empty_seats;
    long long wating_passengers;
    pthread_mutex_t m;
    pthread_cond_t arrive;
    pthread_cond_t depart;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
