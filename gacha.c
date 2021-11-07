//@author Reiden Rufin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <getopt.h>

#include "gacha.h"
#define OPTLIST "sc:w:"


//------------------------------------------------------------------------------
void execute_gacha(char **array, char* times, char* name)
{
    srand((unsigned int)time(NULL));
    int number_of_pulls = 0;
    int four_star_pity = 0;
    int guaranteed_pity = read_file_contets("guaranteed.txt");
    int d = number_of_lines("pity.txt");
    if(d >= 89)
    {
        printf("Won the with guaranteed pity. Total pity count: %d Character pulled: %s\n", d, name);
        guaranteed = false;
        write_to_guaranteed("guaranteed.txt", guaranteed);
        reset_pity("pity.txt");
        exit(EXIT_SUCCESS);
    }
    for(int i = 0; i < atoi(times); i++)
    {
        number_of_pulls++;
        four_star_pity++;
        float upper = 1.00000;
        float x = ((float)rand()/(float)(RAND_MAX)) * upper;
        
        if(x <= 0.006)
        {
        
            int rng = fifty_fifty(STANDARD_FIVE_STARS_CHARACTERS);
            if((rng == 1 && guaranteed_pity == 1) || d >= 89) //we won 50/50
            {
                printf("Won the 50/50 in exactly %d pulls. Character Pulled: %s\n", number_of_pulls, name);
                guaranteed = false;
                write_to_guaranteed("guaranteed.txt", guaranteed);
            }
            else //we lost 50/50
            {  
                if(guaranteed_pity == 0)
                {
                    time_t t;
                    srand((unsigned) time(&t));
                    int index = rand() %5;

                    printf("Lost the 50/50 in %d pulls. Character Pulled:\t%s\n", number_of_pulls, array[index]);
                    guaranteed = true;
                    write_to_guaranteed("guaranteed.txt", guaranteed);
                    reset_pity("pity.txt");
                }
            }
            reset_pity("pity.txt");
            break;
        }
        else if (x >= 0.92 || (four_star_pity % 10 == 0 && four_star_pity != 0)) //attempt to simulate four stars
        {
            int index = rand () % 20;
            printf("Four star pulled!: %s\n", FOUR_STARS_CHARACTER[index]);
            add_pity();
            four_star_pity = 0;
        }
        else
        {
            int index = rand() % 13;
            printf("Three star pulled: %s\n", THREE_STAR_ARRAY[index]);
            add_pity();
        }
    }
}

void execute_gacha_standard(char** array, char* times)
{
    
    srand((unsigned int)time(NULL));
    int number_of_pulls = 0;
    int four_star_pity = 0;
    int guaranteed_pity = read_file_contets("guaranteed.txt");
    int d = number_of_lines("pity.txt");
    
    if(d >= 89)
    {
        int rng = fifty_fifty(array);
            if((rng == 1 || guaranteed_pity == 1)) //we won a 5* character
            {
                time_t t;
                srand((unsigned) time(&t));
                int index = rand() %5;

                printf("Won a standard character in %d pulls with guaranteed pity. Character Pulled: %s\n", number_of_pulls, array[index]);

                guaranteed = false;
                write_to_guaranteed("guaranteed.txt", guaranteed);
            }
            else //we won a 5* weapon
            {  
                if(guaranteed_pity == 0)
                {
                    time_t t;
                    srand((unsigned) time(&t));
                    int index = rand() %10;

                    printf("Won a standard weapon in %d pulls. Weapon Pulled:\t%s\n", number_of_pulls, array[index]);
                    guaranteed = true;
                    write_to_guaranteed("guaranteed.txt", guaranteed);
                    reset_pity("pity.txt");
                }
            }
            reset_pity("pity.txt");
        exit(EXIT_SUCCESS);
    }
    for(int i = 0; i < atoi(times); i++)
    {
        sleep(1);
        printf("pull count: %d\n", number_of_pulls);
        
        float upper = 1.00000;
        float x = ((float)rand()/(float)(RAND_MAX)) * upper;
        
        if(x <= 0.006 || pity_counter >= 89)
        {
            int rng = fifty_fifty(array);
            if((rng == 1 || guaranteed_pity == 1)) //we won a 5* character
            {
                time_t t;
                srand((unsigned) time(&t));
                int index = rand() %5;

                printf("Won a standard character in %d pulls. Character Pulled: %s\n", number_of_pulls, array[index]);

                guaranteed = false;
                write_to_guaranteed("guaranteed.txt", guaranteed);
                pity_counter = 0;
                reset_pity("pity.txt");
            }
            else //we won a 5* weapon
            {  
                if(guaranteed_pity == 0)
                {
                    time_t t;
                    srand((unsigned) time(&t));
                    int index = rand() %10;
                    int no = number_of_lines("pity.txt");
                    printf("no is %d\n", no);
                    printf("Won a standard weapon in %d pulls. Weapon Pulled: %s\n", number_of_pulls, array[index]);
                    guaranteed = true;
                    write_to_guaranteed("guaranteed.txt", guaranteed);
                    reset_pity("pity.txt");
                }
            }
            reset_pity("pity.txt");
            
        }
        else if (x >= 0.92 || (four_star_pity % 10 == 0 && four_star_pity != 0)) //attempt to simulate four stars
        {
            int index = rand () % 20;
            printf("Four star pulled!: %s\n", FOUR_STARS_CHARACTER[index]);
            add_pity();
            four_star_pity = 0;
        }
        else
        {
            int index = rand() % 13;
            printf("Three star pulled: %s\n", THREE_STAR_ARRAY[index]);
            add_pity();
        }
        number_of_pulls++;
        four_star_pity++;
    }
}

//----------------------------------------------------
int main(int argc, char*argv[])
{
    //add check here = print_usage();

    int opt;
    opterr = 0;
    char* name = NULL;
    char* weap = NULL;
    char*times = argv[argc-1];
    while((opt = getopt(argc, argv, OPTLIST)) != -1)
    {
        if(opt == 's')
        {   
            printf("Rolling...\n");
            
            execute_gacha_standard(STANDARD_FIVE_STARS_CHARACTERS, times);
        }
        else if (opt == 'c')
        {
            name = optarg;
            CHECK_ALLOC(name);
            printf("Rolling...\n");
            
            append_to_array(STANDARD_FIVE_STARS_CHARACTERS, name);
            execute_gacha(STANDARD_FIVE_STARS_CHARACTERS, times, name);
        }
        else if (opt == 'w')
        {
            weap = optarg;
            CHECK_ALLOC(weap);
            printf("Weapon %s\n", weap);
            append_to_array(STANDARD_FIVE_STARS_WEAPONS, weap);
            execute_gacha(STANDARD_FIVE_STARS_WEAPONS, times, weap);
        }
        else
        {
            print_usage();
        }
    }
    return 0;
}


