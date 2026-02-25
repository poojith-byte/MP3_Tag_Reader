#include<stdio.h>
#include<string.h>
#include"type.h"
#include"view.h"
#include<stdlib.h>
status read_and_evaluate(char *argv,MP3 *mp3)
{   // 1. Find the last occurrence of '.'
    char *rec = strrchr(argv,'.');
    // 2. Check if '.' exists AND if the string from that point matches ".mp3"
    if(rec!=NULL&&(!(strcmp(rec,".mp3")))){
        //printf("cla contain .mp3 file\n");
        return e_sucess;
    }
    // 3. If either condition fails
    printf(".mp3 not match\n");
    return e_failure;

}
status open_file(MP3 *mp3){
    mp3->fmp3 =fopen(mp3->mp3_name,"r");
    if(mp3->fmp3==NULL){
        printf("could not open the file\n");
        return e_failure;
    }
    else{
        //printf("file sucessfully opned\n");
        return e_sucess;
    }
}
status read_tag_name(MP3 *mp3,Tag_Data *tag_data)
{
    if(fread(tag_data->tag,1,4,mp3->fmp3)!=4){
        printf("couldnot able to read tag name\n");
        return e_failure;
    }
    tag_data->tag[4] = '\0';
    //printf("tag name is %s\n",tag_data->tag);
    return e_sucess;

};

status read_tag_data_size(MP3 *mp3,Tag_Data *tag_data){
    unsigned char size[4];
    unsigned int res = 0;
    if(fread(size,1,4,mp3->fmp3)!=4)
    {
        printf("couldnot read the data from mp3\n");
    }
    for(int i=0;i<4;i++){
        res = (res << 8) | size[i];
    }
    tag_data->size = res;
    //printf("size is : %u\n", tag_data->size);
    return e_sucess;
}
status read_tag_data(MP3 *mp3, Tag_Data *tag_data)
{
    int size = tag_data->size;

    tag_data->data = malloc(size + 1);
    if (!tag_data->data)
        return e_failure;

    if (fread(tag_data->data, 1, size, mp3->fmp3) != size)
        return e_failure;

    tag_data->data[size] = '\0';

    //printf("data is : %s\n", tag_data->data+1);

    return e_sucess;
}

status print_tag_table(Tag_Data *tag_data, int count)
{
    printf("\n");
    printf("+----------------------------------+----------+----------------------------------+\n");
    printf("|        MP3 TAG INFORMATION       |          |                                  |\n");
    printf("+----------------------------------+----------+----------------------------------+\n");
    printf("| %-32s | %-8s | %-32s |\n", "Tag Name", "Size", "Data");
    printf("+----------------------------------+----------+----------------------------------+\n");
    
    for(int i = 0; i < count; i++)
    {
        char tag_name[33];
        // Convert tag enum to readable name
        if(strcmp(tag_data[i].tag, "TPE1") == 0) strcpy(tag_name, "Artist");
        else if(strcmp(tag_data[i].tag, "TIT2") == 0) strcpy(tag_name, "Title");
        else if(strcmp(tag_data[i].tag, "TALB") == 0) strcpy(tag_name, "Album");
        else if(strcmp(tag_data[i].tag, "TYER") == 0) strcpy(tag_name, "Year");
        else if(strcmp(tag_data[i].tag, "COMM") == 0) strcpy(tag_name, "Comment");
        else if(strcmp(tag_data[i].tag, "TCOM") == 0) strcpy(tag_name, "Composer");
        else strcpy(tag_name, "Unknown");
        
        char data_preview[33];
        if(tag_data[i].data != NULL)
        {
            // Skip first character (encoding byte) and get data
            int len = strlen(tag_data[i].data + 1);
            if(len > 32)
            {
                strncpy(data_preview, tag_data[i].data + 1, 29);
                data_preview[29] = '.';
                data_preview[30] = '.';
                data_preview[31] = '.';
                data_preview[32] = '\0';
            }
            else
            {
                strcpy(data_preview, tag_data[i].data + 1);
            }
        }
        else
        {
            strcpy(data_preview, "N/A");
        }
        
        printf("| %-32s | %8d | %-32s |\n", tag_name, tag_data[i].size, data_preview);
    }
    
    printf("+----------------------------------+----------+----------------------------------+\n\n");
    return e_sucess;
}

status start_view(MP3 *mp3,Tag_Data *tag_data)
{
    if(open_file(mp3)==e_sucess) ;//printf("sucessfully open the file");
    fseek(mp3->fmp3,10,SEEK_SET);
    for(int i=0;i<6;i++)
    {
        if(read_tag_name(mp3,&tag_data[i]) == e_sucess) ;//printf("tag name successfully read\n");
        if(read_tag_data_size(mp3,&tag_data[i]) == e_sucess) ;//printf("tag size successfully read\n");
        fseek(mp3->fmp3,2,SEEK_CUR);
        if(read_tag_data(mp3,&tag_data[i]) == e_sucess) ;//printf("tag data successfully read\n");
    }
    
    // Print all tag data in table format
    print_tag_table(tag_data, 6);
    
    return e_sucess;
    
     
}