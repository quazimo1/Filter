#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

const int HEADER_SIZE = 512;

int check_jpg (BYTE *BUFFER);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("usage: ./recover name_of_memory_card");
        return 1;
    }
    //opening memory file
    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL)
    {
        printf("couldn't open the file");
        return 1;
    }
    //
    int d = 0;
    int found = 0;
    BYTE BUFFER[HEADER_SIZE];
    while(fread(BUFFER, sizeof(BYTE),  HEADER_SIZE, fin))
    {
        //checking if jpg

        if(check_jpg(BUFFER))
        {
            if(found == 0)
            {
            char *s = malloc(sizeof(BYTE) * 8);
            sprintf(s, "%03i.jpg", d);

            FILE *fout = fopen(s, "w");

            if(fout == NULL)
            {
                printf("couldn't create the file");
                return 1;
            }

            fwrite(BUFFER, sizeof(BYTE),  HEADER_SIZE, fout);
            found++;
            fclose(fout);
            free(s);
            }
            else if(found)
            {
                d++;
                char *s = malloc(sizeof(BYTE) * 8);
                sprintf(s, "%03i.jpg", d);

                FILE *fout = fopen(s, "w");

                if(fout == NULL)
                {
                    printf("couldn't create the file");
                    return 1;
                }

                fwrite(BUFFER, sizeof(BYTE),  HEADER_SIZE, fout);

                fclose(fout);
                free(s);

            }
        }

        else if(found)
        {
            char *s = malloc(sizeof(BYTE) * 8);
            sprintf(s, "%03i.jpg", d);

            FILE *fout = fopen(s, "a");

            if(fout == NULL)
            {
                printf("couldn't create the file");
                return 1;
            }

            fwrite(BUFFER, sizeof(BYTE),  HEADER_SIZE, fout);
            fclose(fout);
            free(s);

        }
        memset(BUFFER, 0, HEADER_SIZE);
    }

    fclose(fin);
}




int check_jpg (BYTE *BUFFER)
{
    if(BUFFER[0] == 0xff && BUFFER[1] == 0xd8 && BUFFER[2] == 0xff)
    {
        if((BUFFER[3] & 0xf0) == 0xe0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }
}