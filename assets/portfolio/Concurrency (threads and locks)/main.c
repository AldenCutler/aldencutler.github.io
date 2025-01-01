#include "seed.h"
#include "sports.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

// global variables
pthread_mutex_t bb_lock = PTHREAD_MUTEX_INITIALIZER;        /* locks the bb_ready counter */
pthread_mutex_t fb_lock = PTHREAD_MUTEX_INITIALIZER;        /* locks the fb_ready counter */
pthread_mutex_t rb_lock = PTHREAD_MUTEX_INITIALIZER;        /* locks the rb_ready counter */
pthread_cond_t bb_cond = PTHREAD_COND_INITIALIZER;          /* signals baseball players to enter the field  */
pthread_cond_t fb_cond = PTHREAD_COND_INITIALIZER;          /* signals football players to enter the field  */
pthread_cond_t rb_cond = PTHREAD_COND_INITIALIZER;          /* signals rugby players to enter the field     */
pthread_cond_t game_over = PTHREAD_COND_INITIALIZER;        /* signals the end of the game                  */
pthread_cond_t field_ready = PTHREAD_COND_INITIALIZER;      /* signals the field is ready for a new game    */

int bb_ready = 0;                                           /* number of ready baseball players */
int fb_ready = 0;                                           /* number of ready football players */
int rb_ready = 0;                                           /* number of ready rugby players    */

field_t field;

/**
 * This is the thread function for the baseball players.
 * @param arg A pointer to a player structure
 * @return NULL
 */
void *baseball(void *arg)
{
    // arg is a pointer to the player
    player_t *p = (struct player *)arg;

    // NUM_LOOPS can be changed in sports.h
    for (int loop = 0; loop < NUM_LOOPS; loop++)
    {
        // get ready
        random_sleep(1, 3);
        printf(BB " %3d ready\n" RESET, p->id);

        // increment ready count
        pthread_mutex_lock(&bb_lock);
        bb_ready++;

        // check if there are enough players to start the game
        if (bb_ready == MAX_BASEBALL_PLAYERS / 2)
        {
            /* SIGNALER MUST HAVE FIELD LOCK */
            pthread_mutex_lock(&field.lock);

                // wait for the field to be ready
                while (field.sport != NO_SPORT && field.sport != BASEBALL)
                {
                    pthread_cond_wait(&field_ready, &field.lock);
                }
                printf(BB " %3d %sstarting game\n" RESET, p->id, GREEN);

                // set up the field
                field.sport = BASEBALL;         // set the sport
                // assert(field.num_players == 0); // for debugging, should always be true
                field.num_players = 1;          // signaler is the first player
                bb_ready--;                     // decrement ready count to show that the signaler has joined the game

                // signal as many players as possible to join the game
                while (bb_ready > 0)
                {
                    pthread_cond_signal(&bb_cond);
                    field.num_players++;
                    bb_ready--;
                }
                // printf("ready: %d\n", bb_ready);                // for debugging
                // printf("num_players: %d\n", field.num_players); // for debugging
                pthread_mutex_unlock(&bb_lock);

                // simulate game time
                random_sleep(2, 5);

                // signal game over
                printf(BB " %3d %sgame over\n" RESET, p->id, RED);
                pthread_cond_broadcast(&game_over);

                // reset field and signal that it is ready for a new game
                field.num_players = 0;
                field.sport = NO_SPORT;
                pthread_cond_broadcast(&field_ready);

            pthread_mutex_unlock(&field.lock);
            /* RELEASE FIELD LOCK */
        }
        // otherwise, wait for the signal
        else
        {
            // wait for entry signal
            pthread_cond_wait(&bb_cond, &bb_lock);
            printf(BB " %3d %sjoining game\n" RESET, p->id, BLUE);

            // wait for game over signal
            pthread_cond_wait(&game_over, &bb_lock);
            pthread_mutex_unlock(&bb_lock);
        }
    }

    return NULL;
}

/**
 * This is the thread function for the football players.
 * @param arg: a pointer to a player structure
 * @return: NULL
 */
void *football(void *arg)
{
    // arg is a pointer to the player
    player_t *p = (struct player *)arg;

    // NUM_LOOPS can be changed in sports.h
    for (int loop = 0; loop < NUM_LOOPS; loop++)
    {
        // get ready
        random_sleep(1, 3);
        printf(FB " %3d ready\n" RESET, p->id);

        // increment ready count
        pthread_mutex_lock(&fb_lock);
        fb_ready++;

        // check if there are enough players to start the game
        if (fb_ready == MAX_FOOTBALL_PLAYERS / 2)
        {
            /* SIGNALER MUST HAVE FIELD LOCK */
            pthread_mutex_lock(&field.lock);

                // wait for the field to be ready
                while (field.sport != NO_SPORT && field.sport != FOOTBALL)
                {
                    pthread_cond_wait(&field_ready, &field.lock);
                }
                while (field.sport == FOOTBALL)     // not sure if this is necessary, but it can't hurt. I think it would be useful in the case where every player is ready and the previous game was football
                {
                    pthread_cond_wait(&game_over, &fb_lock);
                }

                // start the game
                printf(FB " %3d %sstarting game\n" RESET, p->id, GREEN);
                field.num_players = 1; // signaler is the first player
                fb_ready--;

                // signal as many players as possible to join the game
                while (fb_ready > 0)
                {
                    pthread_cond_signal(&fb_cond);
                    field.num_players++;
                    fb_ready--;
                }
                pthread_mutex_unlock(&fb_lock);
                field.sport = FOOTBALL;
                // assert(field.num_players == 0);                      // for debugging, should always be true
                // printf("ready: %d\n", fb_ready);                     // for debugging
                // printf("num_players: %d\n", field.num_players);      // for debugging

                // simulate game time
                random_sleep(2, 5);

                // signal game over
                // pthread_mutex_lock(&fb_lock);
                printf(FB " %3d %sgame over\n" RESET, p->id, RED);
                pthread_cond_broadcast(&game_over);
                // pthread_mutex_unlock(&fb_lock);

                // reset field and signal that it is ready for a new game
                field.num_players = 0;
                field.sport = NO_SPORT;
                pthread_cond_broadcast(&field_ready);

            pthread_mutex_unlock(&field.lock);
            /* RELEASE FIELD LOCK */
        }
        // otherwise, wait for the signal
        else
        {
            // wait for entry signal
            pthread_cond_wait(&fb_cond, &fb_lock);
            printf(FB " %3d %sjoining game\n" RESET, p->id, BLUE);

            // wait for game over signal
            pthread_cond_wait(&game_over, &fb_lock);
            pthread_mutex_unlock(&fb_lock);
        }
    }

    return NULL;
}


/**
 * This is the thread function for the rugby players. *
 * @param arg: a pointer to a player structure
 * @return: NULL
 */
void *rugby(void *arg)
{
    // arg is a pointer to the player
    player_t *p = (struct player *)arg;

    // NUM_LOOPS can be changed in sports.h
    for (int loop = 0; loop < NUM_LOOPS; loop++)
    {
        // get ready
        random_sleep(1, 3);
        printf(RB " %3d ready\n" RESET, p->id);

        // increment ready count
        pthread_mutex_lock(&rb_lock);
        rb_ready++;

        // check if there are enough players to start the game
        if (rb_ready % 2 == 0)
        {
            /* SIGNALER MUST HAVE FIELD LOCK */
            pthread_mutex_lock(&field.lock);

            // wait for the field to be ready
            while (field.sport != NO_SPORT && field.sport != RUGBY)
            {
                pthread_cond_wait(&field_ready, &field.lock);
            }

            // if number of ready players is even and no game is ongoing, start the game
            if (field.sport == NO_SPORT)
            {
                printf(RB " %3d %sstarting game\n" RESET, p->id, GREEN);
                
                // set up the field
                field.sport = RUGBY;
                // assert(field.num_players == 0);                  // for debugging, should always be true
                field.num_players = 1;
                rb_ready--;

                // signal as many players as possible to join the game
                while (rb_ready > 0 && field.num_players < MAX_RUGBY_PLAYERS / 2)
                {
                    pthread_cond_signal(&rb_cond);
                    field.num_players++;
                    rb_ready--;
                }
                // printf("ready: %d\n", rb_ready);                // for debugging
                // printf("num_players: %d\n", field.num_players); // for debugging

                // unlock to allow other players to join
                pthread_mutex_unlock(&field.lock);
                pthread_mutex_unlock(&rb_lock);

                // simulate game time
                random_sleep(2, 5);

                // signal game over
                printf(RB " %3d %sgame over\n" RESET, p->id, RED);
                pthread_cond_broadcast(&game_over);

                // reset field and signal that it is ready for a new game
                pthread_mutex_lock(&field.lock);
                    field.num_players = 0;
                    field.sport = NO_SPORT;
                    pthread_cond_broadcast(&field_ready);
                pthread_mutex_unlock(&field.lock);
            }
            // else if number of ready players is even and a rugby game is ongoing, join the game
            else if (field.sport == RUGBY)
            {
                // if there is space in the game, signal another player to join along with this player
                if (field.num_players < MAX_RUGBY_PLAYERS / 2)
                {
                    pthread_mutex_unlock(&field.lock);
                    pthread_cond_signal(&rb_cond);
                    printf("pair joining:\n" RESET);
                    printf(RB " %3d %sjoining game and signaling another player\n" RESET, p->id, BLUE);
                    field.num_players += 2;
                    rb_ready -= 2;
                }
                // else, wait for signal to join the game
                else
                {
                    pthread_mutex_unlock(&field.lock);
                    pthread_cond_wait(&rb_cond, &rb_lock);
                    printf(RB " %3d %sjoining game\n" RESET, p->id, BLUE);
                }

                // wait for game over signal
                pthread_cond_wait(&game_over, &rb_lock);
                pthread_mutex_unlock(&rb_lock);
            }
        }
        // otherwise, wait for the signal
        else
        {
            // wait for entry signal
            pthread_cond_wait(&rb_cond, &rb_lock);
            printf(RB " %3d %sjoining game\n" RESET, p->id, BLUE);

            // wait for game over signal
            pthread_cond_wait(&game_over, &rb_lock);
            pthread_mutex_unlock(&rb_lock);
        }
    }

    return NULL;
}

int main()
{

    printf("#########################################\n");
    printf("# Welcome to the Worcester Gompei Park! #\n");
    printf("#########################################\n");

    // initialize seed, field, and players
    printf("Intializing seed, field, and players...\n");
    srand(getseed());
    printf("Seed: %d\n", getseed());
    init_field(&field);
    player_t players[MAX_THREADS];

    // create threads
    printf("Creating threads...\n");
    for (int i = 0; i < MAX_THREADS; i++)
    {
        players[i].id = i;
        players[i].status = 0;

        // create baseball players
        if (i < MAX_BASEBALL_PLAYERS)
        {
            pthread_create(&players[i].tid, NULL, baseball, &players[i]);
        }
        // create football players
        else if (i < MAX_BASEBALL_PLAYERS + MAX_FOOTBALL_PLAYERS)
        {
            pthread_create(&players[i].tid, NULL, football, &players[i]);
        }
        // create rugby players
        else
        {
            pthread_create(&players[i].tid, NULL, rugby, &players[i]);
        }
    }

    // wait for threads to finish
    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(players[i].tid, NULL);
        printf("Thread %d finished.\n", i);
    }

    printf("\nAll threads finished. Cleaning up and exiting.\n");

    // clean up and exit
    pthread_mutex_destroy(&field.lock);
    pthread_mutex_destroy(&bb_lock);
    pthread_mutex_destroy(&fb_lock);
    pthread_mutex_destroy(&rb_lock);
    pthread_cond_destroy(&bb_cond);
    pthread_cond_destroy(&fb_cond);
    pthread_cond_destroy(&rb_cond);
    pthread_cond_destroy(&game_over);
    pthread_cond_destroy(&field_ready);

    return 0;
}