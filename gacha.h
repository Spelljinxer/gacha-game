//@author Reiden Rufin
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>


#define NUM_CHARACTERS 6 //we add one of the limited
#define NUM_WEAPONS 12 //we add two of the limited weapons
#define NUM_4STAR_STANDARD 50
#define NUM_3STAR 14

#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }
 
bool guaranteed = false;
int pity_counter = 0;


//-------------------------------------------


char* STANDARD_FIVE_STARS_CHARACTERS[NUM_CHARACTERS] = {
    "Keqing",
    "Qiqi",
    "Jean",
    "Diluc",
    "Mona"
};

char* STANDARD_FIVE_STARS_WEAPONS[NUM_WEAPONS] = {
    "Skyward Harp",
    "Skyward Atlas",
    "Skyward Spine",
    "Skyward Pride",
    "Skyward Blade",
    "Amos' Bow",
    "Lost Prayer to the Sacred Winds",
    "Primordial Jade Winged-Spear",
    "Wolf's Gravestone",
    "Aquila Favonia",
};


char* FOUR_STARS_CHARACTER[NUM_4STAR_STANDARD] = {
    "Rosaria",
    "Lisa",
    "Amber",
    "Diona",
    "Xinyan",
    "Yanfei",
    "Sayu",
    "Sara",
    "Sucrose",
    "Noelle",
    "Chongyun",
    "Beidou",
    "Ningguang",
    "Xiangling",
    "Xingqiu",
    "Fischl",
    "Bennet",
    "Razor",
    "Barbara",
    "Kaeya"
};

char *FOUR_STAR_WEAPONS[NUM_4STAR_STANDARD] = {
    "Rust",
    "Sacrificial Bow",
    "Sacrificial Fragments",
    "Sacrificial Greatsword",
    "The Stringless",
    "The Widsith",
    "The Bell",
    "The Flute",
    "Favonius Warbow",
    "Favonius Lance",
    "Favonius Codex",
    "Favonius Greatsword",
    "Favonius Sword",
    "Dragon's Bane",
    "Rainslasher",
    "Lion's Roar",
    "Eye of Perception"
};

char* THREE_STAR_ARRAY[NUM_3STAR] = {
    "Slingshot",
    "Thrilling Tales of Dragon Slayers",
    "Sharpshooter's Oath",
    "Ferrous Shadow",
    "Skyrider Sword",
    "Cool Steel",
    "Debate Club",
    "Black Tassel",
    "Bloodtainted Greatsword",
    "Magic Guide",
    "Emerald Orb",
    "Raven Bow",
    "Harbinger of Dawn"
};

void print_usage()
{
    printf("Usage: ./gacha -> -s(standard banner) -c (character banner) -w (weapon banner) n(number of pulls you want to do)\n");
    exit(EXIT_SUCCESS);
}



void append_to_array(char **array, char*string)
{
    int i = 0;
    while(array[i] != NULL)
    {
        i++;
    }
    array[i] = string;
}




void write_to_guaranteed(char*filename, int data)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error: cannot open file %s\n", filename);
        exit(1);
    }
    fprintf(fp, "%d", data);
    fclose(fp);
}

//read the contents of @param filename
    //returning the final value of the file
    //if the file is empty, return 0
int read_file_contets(char*filename)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return 0;
    }
    int value = 0;
    char c;
    while((c = fgetc(fp)) != EOF)
    {
        value = value * 10 + (c - '0');
    }
    fclose(fp);
    return value;
}

void write_to_file(char* filename, int data) 
{
    FILE* fp = fopen(filename, "aw");
    fprintf(fp, "%d\n", data);
    fclose(fp);
}

int add_pity()
{
    pity_counter++;
    write_to_file("pity.txt", pity_counter);
    return pity_counter;
}


//clear the contents of the file @param filename
int reset_pity(char* filename)
{
    FILE* fp = fopen(filename, "w");
    fclose(fp);
    return 0;
}

int fifty_fifty(char**array)
{
    time_t t;
    srand((unsigned) time(&t));
    int random = rand() % 2;
    return random;
}

//returns number of lines in @param filename
int number_of_lines(char*filename)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return 0;
    }
    int lines = 0;
    char c;
    while((c = fgetc(fp)) != EOF)
    {
        if(c == '\n')
        {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}
