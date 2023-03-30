#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
    // FILL ME IN
    pthread_mutex_init( &(station->m), NULL);
    pthread_cond_init( &(station->arrive), NULL);
    pthread_cond_init( &(station->depart), NULL);
    station->seated=0;
    station->empty_seats=0;
    station->wating_passengers=0;
}

void
station_load_train(struct station *station, int count)
{
    // FILL ME IN
    pthread_mutex_lock(&(station->m));
    if(count!=0&&station->wating_passengers!=0)
    {station->empty_seats= count;
     while(station->empty_seats!=0&&station->wating_passengers!=0)
     {pthread_cond_broadcast(&(station->arrive));
    pthread_cond_wait(&(station->depart),&(station->m));}
    }
    pthread_mutex_unlock(&(station->m));
}

void
station_wait_for_train(struct station *station)
{
    // FILL ME IN
    pthread_mutex_lock(&(station->m));
    station->wating_passengers++;
    while(station->empty_seats==0)
        pthread_cond_wait(&(station->arrive),&(station->m));
    station->wating_passengers--;
    station->empty_seats--;
    station->seated--;
    pthread_mutex_unlock(&(station->m));
}

void
station_on_board(struct station *station)
{
    // FILL ME IN
    pthread_mutex_lock(&(station->m));
    station->seated++;
    pthread_mutex_unlock(&(station->m));
    if(station->seated==0)
        if(station->empty_seats==0||station->wating_passengers==0)
            pthread_cond_signal(&(station->depart));
}
