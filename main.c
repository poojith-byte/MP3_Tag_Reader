#include<stdio.h>
#include<string.h>
#include"view.h"
#include"type.h"
#include"edit.h"
#include<stdlib.h>
MP3 mp3;
Edit edit;
void print_help(){
    printf(
    "Usage:\n"
    "------\n"
    "To view the data:\n"
    "  Example: ./a.out -v <mp3_file_name>\n\n"
    "To edit tags:\n"
    "  Example: ./a.out -e -t \"hello how r u\" <mp3_file_name>\n"
    "  (Note: write the text inside double quotes)\n\n"
    "Options:\n"
    "  -e  : Edit mode\n"
    "  -v  : View mode\n"
    "  -h  : Help\n"
    "  -t  : Modify Title tag\n"
    "  -T  : Modify Track tag\n"
    "  -a  : Modify Artist tag\n"
    "  -A  : Modify Album tag\n"
    "  -y  : Modify Comment tag\n"
    "  -c  : TCOM tag\n"
    "  -C  : Compression\n"
);
    // printf("To view the data\n");
    // printf("example: ./a.out -v mp3 file name");
    // printf("To edit\n");
    //  printf("for example : ./a.out -e -t \"hello how r u\" file name (note write the text inside "")\n");
    // printf("-e : edit\n-v : view\n-h : help\n-t : modifies a title tag\n-T : modifies Track Tag\n-a : modifies Artist tag\n-A : modifies albam tag\n-y : modifies comment tag\n-c: Tcom\n-C : Compresson\n");
   
}
operation check_operation_type(char *argv)
    {
        if((!strcmp(argv,"-v"))){
            return e_view;
        }       
        else if (!strcmp(argv,"-e")){
            return e_edit;
        }
        else if(!strcmp(argv,"-h")){
            return e_help;
        }
        else{
            return e_unsupported;
        }
    }
operation check_edit_operation(char *argv,Edit *edit)
{
    if(!strcmp(argv,"-t")){
        //printf("selected to change title\n");
        strcpy(edit->tag,"TIT2");
        //printf("%s\n",edit->tag);
        return e_TIT2;
    }
    // else if(!strcmp(argv,"-T")){
    //     printf("selected to change title\n");
    //     return e_TIT2;
    // }
    else if(!strcmp(argv,"-a")){
        //printf("selected to change artist tag\n");
        strcpy(edit->tag,"TPE1");
        return e_TPE1;
    }
    else if(!strcmp(argv,"-A")){
        //printf("selected to change albam\n");
        strcpy(edit->tag,"TALB");
        return e_TALB;
    }
    else if(!strcmp(argv,"-y")){
        //printf("selected to change year\n");
        strcpy(edit->tag,"TYER");
        return e_TYER;
    }
    else if(!strcmp(argv,"-c")){
        //printf("selected to change title\n");
        strcpy(edit->tag,"COMM");
        return e_COMM;
    }
    else if(!strcmp(argv,"-C")){
        //printf("selected to change TCOM\n");
        strcpy(edit->tag,"TCOM");
        return e_TCOM;
    }
    else{
        printf("plz enter the correct tag\n");
        print_help();
        return 0;
    }
}

int main(int argc,char *argv[])
{
        Tag_Data tag_data[6];
        if(argc<2){
            printf("no arguments found\n");
            return 0;
        }
        int check = check_operation_type(argv[1]);
        switch (check){
            case e_view:
                if(argc==3){
                    if(read_and_evaluate(argv[2],&mp3)==e_failure)
                    {
                        //printf("enter .mp3 file\n");
                        return e_failure;
                    }
                    mp3.mp3_name = argv[2];
                    //printf("file name is %s\n",mp3.mp3_name);
                    if(start_view(&mp3,tag_data)==e_failure)
                    {
                        return e_failure;
                    }
                    else{
                        return e_sucess;
                    }
                }
                else{
                    printf("for view enter 3 arguments\n");
                }
                break;

            case e_help:
                print_help();
                break;
            
            case e_edit:
                
                if(argc==5)
                {
                    if(read_and_evaluate(argv[4],&mp3)==e_failure)
                    {
                        printf("enter .mp3 file\n");
                        return 0;
                    }

                    edit.mp3_name=argv[4];
                    //printf("file name is : %s\n",edit.mp3_name);
                    int check = check_edit_operation(argv[2],&edit);
                    edit.data_size = strlen(argv[3]);
                    edit.data = (char *)malloc(edit.data_size+1);
                    strcpy(edit.data,argv[3]);
                    //printf("text is : %s\n",edit.data);
                    if(Edit_tag(&edit)==e_sucess)
                    {
                        printf("sucessfully mp3 edited \n");
                        return 0;
                    }
                    else
                    {
                        printf("couldnot edit\n");
                        return 0;
                    }
                    

                    
                }
                else
                {
                    ("enter 5 argumrnts\n");
                    print_help();
                }
                break;

            default: printf("error\n");
                
        
    }
    return 0;
}