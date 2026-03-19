#ifndef MCAL_CONST_H
#define MCAL_CONST_H

typedef enum {
    MOVE_MODE_POLLING = 1,
    MOVE_MODE_INTERRUPT = 2,
    MOVE_MODE_DMA = 3,
    MOVE_MODE_UNDEF = 0,
}MoveMode_t;

#endif /* MCAL_CONST_H */
