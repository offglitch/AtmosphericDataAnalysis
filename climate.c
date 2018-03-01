/**
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  gcc -g -Wall -o climate climate.c
 *           (or run make)
 *
 * Run:      ./climate data_tn.tdv data_wa.tdv
 *
 *
 * Opening file: data_tn.tdv
 * Opening file: data_wa.tdv
 * States found: TN WA
 * -- State: TN --
 * Number of Records: 17097
 * Average Humidity: 49.4%
 * Average Temperature: 58.3F
 * Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
 * Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
 * Lightning Strikes: 781
 * Records with Snow Cover: 107
 * Average Cloud Cover: 53.0%
 * -- State: WA --
 * Number of Records: 48357
 * Average Humidity: 61.3%
 * Average Temperature: 52.9F
 * Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
 * Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
 * Lightning Strikes: 1190
 * Records with Snow Cover: 1383
 * Average Cloud Cover: 54.5%
 *
 * TDV format:
 *
 * CA 1428300000000 9prc 93.0 0.0 100.0 0.0 95644.0  277.58716
 * CA 1430308800000 9prc 4.0  0.0 100.0 0.0 99226.0  282.63037
 * CA 1428559200000 9prr 61.0 0.0 0.0   0.0 102112.0 285.07513
 * CA 1428192000000 9prk 57.0 0.0 100.0 0.0 101765.0 285.21332
 * CA 1428170400000 9prd 73.0 0.0 22.0  0.0 102074.0 285.10425
 * CA 1429768800000 9pr6 38.0 0.0 0.0   0.0 101679.0 283.9342
 * CA 1428127200000 9prj 98.0 0.0 100.0 0.0 102343.0 285.75
 * CA 1428408000000 9pr4 93.0 0.0 100.0 0.0 100645.0 285.82413
 *
 * Each field is separated by a tab character \t and ends with a newline \n.
 *
 * Fields:
 *      state code (e.g., CA, TX, etc),
 *      timestamp (time of observation as a UNIX timestamp),
 *      geolocation (geohash string),
 *      humidity (0 - 100%),
 *      snow (1 = snow present, 0 = no snow),
 *      cloud cover (0 - 100%),
 *      lightning strikes (1 = lightning strike, 0 = no lightning),
 *      pressure (Pa),
 *      surface temperature (Kelvin)
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define NUM_STATES 50

/* TODO: Add elements to the climate_info struct as necessary. */
struct climate_info
{
    char code[3];
    unsigned long num_records;
    long double sum_temperature;
    long double humidity;
    unsigned long snow;
    unsigned int max_temp;
    unsigned long max_timestamp;
    unsigned int min_temp;
    unsigned long min_timestamp;
    unsigned long thunder;
    long double cloud;
};

void analyze_file(FILE *file, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[])
{

    printf("number arguments = %d\n", argc);

    /* TODO: fix this conditional. You should be able to read multiple files. */
    if (argc <=1)
    {
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN \n", argv[0]);
        return EXIT_FAILURE;
    }


    for(int i=1; i<argc; i++){
        printf("Opening file: %s\n", argv[i]);
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = { NULL };
    int i;
    for (i = 1; i < argc; ++i)
    {
        /* TODO: Open the file for reading */
        char *fname = argv[i];
        if( access( fname, F_OK ) != -1 )
        {
            FILE* file = fopen(fname, "r");
            analyze_file(file, states, NUM_STATES);
        }
        else
        {
            printf("File %s does not exist\n", argv[i]);
            continue;
        }
        /* TODO: Analyze the file */
    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    print_report(states, NUM_STATES);

    return 0;
}

/* TODO function documentation */
void analyze_file(FILE *file, struct climate_info **states, int num_states)
{
    const int line_sz = 100;
    char line[line_sz];
    const char* delim = "\t";
    struct climate_info *info;
    int flag = 0, state_index;
    while (fgets(line, line_sz, file) != NULL)
    {
        /* TODO: We need to do a few things here:
         *
         *       * Tokenize the line.
         *       * Determine what state the line is for. This will be the state
         *         code, stored as our first token.
         *       * If our states array doesn't have a climate_info entry for
         *         this state, then we need to allocate memory for it and put it
         *         in the next open place in the array. Otherwise, we reuse the
         *         existing entry.
         *       * Update the climate_info structure as necessary.
         */

        char *token = strtok(line, delim);
        char *tokens[9];
        int idx = 0;
        while( token != NULL )
        {
            tokens[idx++] = token;
            token = strtok(NULL, delim);
        }
        double temp = atof(tokens[8]) * 1.8 - 459.67;
        int snow = atoi(tokens[4]);
        unsigned long timestamp = atoi(tokens[1]);
        int thunder = atoi(tokens[6]);
        float humidity = atof(tokens[3]);
        float cloud_cover = atof(tokens[5]);

        char *code = tokens[0];
        flag = 0;

        for (int i = 0; i < num_states; ++i)
        {
            if (states[i] != NULL && strcmp(code, states[i]->code)==0)
            {
                info = states[i];
                state_index = i;
                flag = 1;
                break;
            }
        }
        //if flag is zero that means we have not found a state for this record
        if(flag == 0) 
        {
            info = (struct climate_info *)malloc (sizeof(struct climate_info));
            strcpy(info->code, code);
            info->cloud = cloud_cover;
            info->humidity = humidity;
            info->max_temp=temp;
            info->max_timestamp = timestamp;
            info->min_temp = temp;
            info->min_timestamp = timestamp;
            info->num_records = 1;
            info->snow = snow;
            info->sum_temperature = temp;
            info->thunder = thunder;
            for (int i = 0; i < num_states; ++i)
            {
                if (states[i] == NULL)
                {
                    states[i] = info;
                    break;
                }
            }
        }
        //state already exist for this record 
        else
        {
            states[state_index]->num_records += 1;
            states[state_index]->sum_temperature += temp;
            states[state_index]->snow += snow;
            states[state_index]->cloud += cloud_cover;
            states[state_index]->thunder += thunder;
            states[state_index]->humidity += humidity;

            if(states[state_index]->min_temp > temp)
            {
                states[state_index]->min_temp = temp;
                states[state_index]->min_timestamp = timestamp;
            }
            if(states[state_index]->max_temp < temp)
            {
                states[state_index]->max_temp = temp;
                states[state_index]->max_timestamp = timestamp;
            }
        }
    }
}

/* TODO function documentation */
void print_report(struct climate_info *states[], int num_states)
{
    printf("States found: ");
    for (int i = 0; i < num_states; ++i)
    {
        if (states[i] != NULL)
        {
            struct climate_info *info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    /* TODO: Print out the summary for each state. See format above. */
    for(int i=0; i<num_states; i++)
    {

        // timestamp = timestamp / 1000;
        if (states[i] != NULL)
        {
            struct climate_info *curr  = states[i];

            //printing values to console
            float avg_humidity = curr->humidity*1.0/curr->num_records;
            float avg_temp = curr->sum_temperature*1.0 /curr->num_records;

            printf("-- State: %s --\n", curr->code);
            
            printf("Number of Records: %lu\n", curr->num_records);
            printf("Average Humidity: %0.1f\n", (avg_humidity) );            
            printf("Average Temperature: %0.1fF\n", (avg_temp) );

            printf("Max Temperature: %0.1fF on %s", avg_humidity,  ctime((const time_t *)&(curr->max_timestamp)));
            printf("Min Temperature: %0.1fF on %s", avg_temp,  ctime((const time_t *)&(curr->min_timestamp)) );
            printf("Lightning Strikes: %lu\n", curr->thunder);

            printf("Records with Snow Cover: %lu\n", curr->snow);
            printf("Average Cloud Cover: %0.1Lf \n\n", curr->cloud*1.0/curr->num_records);
        }
    }


}