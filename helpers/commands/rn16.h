#ifndef RN16_H
#define RN16_H

typedef struct
{
    unsigned short value;
    unsigned int size;
} rn16;

unsigned short rn16_generate(void);

#endif /* RN16_H */
