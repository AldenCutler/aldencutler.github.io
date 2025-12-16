#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_BASEBALL_PLAYERS 36
#define MAX_FOOTBALL_PLAYERS 44
#define MAX_RUGBY_PLAYERS 60
#define MAX_THREADS 140
#define NUM_LOOPS 2

#define NO_SPORT -1
#define BASEBALL 0
#define FOOTBALL 1
#define RUGBY 2

#define BB "⚾️"
#define FB "🏈"
#define RB "🏉"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

void *baseball(void *arg);
void *football(void *arg);
void *rugby(void *arg);

typedef struct player
{
    int id;
    pthread_t tid;
    int status; // 0 = not playing, 1 = playing
} player_t;

typedef struct field
{
    pthread_mutex_t lock;
    int num_players;
    int sport; // 0 = baseball, 1 = football, 2 = rugby, -1 = no sport
} field_t;

void random_sleep(int min, int max)
{
    int r = rand() % (max - min + 1) + min;
    sleep(r);
}

void init_field(field_t *f)
{
    pthread_mutex_init(&f->lock, NULL);
    f->num_players = 0;
    f->sport = NO_SPORT;
}