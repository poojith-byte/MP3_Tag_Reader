#ifndef VIEW_H
#define VIEW_H
#include<stdio.h>
#include"type.h"

    typedef struct 
    {
        char *mp3_name;
        FILE *fmp3;
    }MP3;
    typedef struct
    {
        char tag[5];
        char *data;
        int size;
    } Tag_Data;

    status read_and_evaluate(char *argv,MP3 *mp3);
    //status start_view();
    status start_view(MP3 *mp3,Tag_Data *tag_data);

#endif