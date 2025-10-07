#ifndef _VERSION_H_
#define _VERSION_H_


typedef struct {
    unsigned short major;
    unsigned short minor;
    unsigned short patch;
} const Why2_Version;


#define why2_version() (Why2_Version) {     \
    .major = 0                              \
    , .minor = 2                            \
    , .patch = 0                            \
}

#endif


