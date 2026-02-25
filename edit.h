#ifndef edit_h
#define edit_h
#include<stdio.h>
#include"type.h"

typedef struct
{
    char *mp3_name;
    FILE *mp3_file_pointer;
    FILE *temp_file_pointer;
    char *data;
    int data_size;
    int size;
    char tag[5];
    char tag_mp3[5];
    
}Edit;

status open_file_to_edit(Edit *edit);
status copy_10_bytes(Edit *edit);
int tag_reader(Edit *edit);
int big_to_little(char raw_size[]);
void little_to_big(int value, unsigned char out[4]);
int org_size(Edit *edit);
void add_size(Edit *edit);
void copy_all_data(Edit *edit);
status Edit_tag(Edit *edit);

#endif