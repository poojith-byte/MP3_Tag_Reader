#include"type.h"
#include"edit.h"
#include<stdio.h>
#include <string.h>

status open_file_to_edit(Edit *edit)
{
    edit->mp3_file_pointer = fopen(edit->mp3_name,"rb");
    if(edit->mp3_file_pointer==NULL){
        //printf("couldnot able to open\n");
        return e_failure;
    }
    edit->temp_file_pointer = fopen("temp.mp3","wb");
    if(edit->temp_file_pointer==NULL){
         //printf("couldnot able to open temp file\n");
        return e_failure;
    }

    return e_sucess;
}
status copy_10_bytes(Edit *edit){
    unsigned char head[10];
    fread(head,1,10,edit->mp3_file_pointer);
    if(fwrite(head,1,10,edit->temp_file_pointer)!=10)
    {
        //printf("could not read 10 bytes \n ");
        return e_failure;
    }
    return e_sucess;
}

int tag_reader(Edit *edit)
{
    memset(edit->tag_mp3, 0, 5);
    fread(edit->tag_mp3,1,4,edit->mp3_file_pointer);
    edit->tag_mp3[4] = '\0';
    //printf("tag mp3 %s\n",edit->tag_mp3);
    if(strcmp(edit->tag_mp3,edit->tag)==0){
        return 1;
    }
    //printf("%s\n",edit->tag_mp3);
    return 0;
}
int big_to_little(char raw_size[])
// add big to little function here 
{   int new_size=0;
    for(int i=0;i<4;i++)
    {
        new_size = (new_size<<8)|(unsigned char)raw_size[i];
    }
    return new_size;
}

void little_to_big(int value,unsigned char out[4]){
    out[0] = (value >> 24) & 0xFF;
    out[1] = (value >> 16) & 0xFF;
    out[2] = (value >> 8)  & 0xFF;
    out[3] = value & 0xFF;
}
int org_size(Edit *edit)
{
    char mp3_data_tag_size[4];//to stor the mp3 data size
    fread(mp3_data_tag_size,1,4,edit->mp3_file_pointer); // copying the mp3 data size
    int org_size = big_to_little(mp3_data_tag_size); // converting the big to lit
    edit->size = org_size; // storing the mp3 data size to edit.Size
    char char_data_size[4]; // creating a character array to tore the new data size
    little_to_big(edit->data_size+1,char_data_size); // converting the edit.data size to big (adding 1 for encoding byte)
    fwrite(char_data_size,1,4,edit->temp_file_pointer); // transfering the new data size to temp.mp3
    return 0;

}
void add_size(Edit *edit)
{
    char mp3_data_tag_size[4];//to stor the mp3 data size
    fread(mp3_data_tag_size,1,4,edit->mp3_file_pointer); // copying the mp3 data size
    edit->size = big_to_little(mp3_data_tag_size);
    fwrite(mp3_data_tag_size,1,4,edit->temp_file_pointer);

}
void copy_all_data(Edit *edit)
{
    int ch;
    while((ch = fgetc(edit->mp3_file_pointer))!=EOF){
        fputc(ch,edit->temp_file_pointer);
    }
}
status Edit_tag(Edit *edit)
{
    if(open_file_to_edit(edit) == e_sucess); //printf("file opned\n");
    if(copy_10_bytes(edit) ==e_sucess) ;//printf("10 bytes copyed\n");
    int i;
    for(i=0;i<6;i++)
    {
        unsigned char flag[2]={0};
        int check = tag_reader(edit);
        //printf("check is %d\n",check);
        switch(check){
            case 1:
                fwrite(edit->tag_mp3,1,4,edit->temp_file_pointer);
                org_size(edit);
                fread(flag,1,2,edit->mp3_file_pointer);
                fwrite(flag,1,2,edit->temp_file_pointer);
                unsigned char encoding;
                fread(&encoding,1,1,edit->mp3_file_pointer);
                fwrite(&encoding,1,1,edit->temp_file_pointer);
                fwrite(edit->data,1,edit->data_size,edit->temp_file_pointer);
                fseek(edit->mp3_file_pointer,edit->size-1,SEEK_CUR);
                break;
            case 0:
                fwrite(edit->tag_mp3,1,4,edit->temp_file_pointer);
                add_size(edit);
                fread(flag,1,2,edit->mp3_file_pointer);
                fwrite(flag,1,2,edit->temp_file_pointer);
                unsigned char data[edit->size];
                fread(data,1,edit->size,edit->mp3_file_pointer);
                fwrite(data,1,edit->size,edit->temp_file_pointer);
                break;
                
        }
        if(check ==1){
            copy_all_data(edit);
            remove(edit->mp3_name);          // delete original
            rename("temp.mp3", edit->mp3_name); // temp → original
            return 0;
        }
    }
    // copy_all_data(edit);
    // remove(edit->mp3_name);          // delete original
    // rename("temp.mp3", edit->mp3_name); // temp → original
    return 0;
}

