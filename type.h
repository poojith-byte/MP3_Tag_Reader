#ifndef TYPES_H
#define TYPES_H

    typedef enum 
    {
        
        e_sucess,e_failure
    }status;
    
    typedef enum 
    {
        e_view,e_edit,e_help,e_unsupported
    }operation;

    typedef  enum
    {
        e_TPE1,
        e_TIT2,
        e_TALB,
        e_TYER,
        e_COMM,
        e_TCOM
    }ed_operation;
    
#endif
