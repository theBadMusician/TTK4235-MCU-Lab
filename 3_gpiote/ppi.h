#ifndef PPI_H
#define PPI_H
#include <stdint.h>

#define PPI ((NRF_PPI_REG*)0x4001F000)

typedef struct {
	uint32_t EN;
	uint32_t DIS;
} PPI_TASKS_TYPE;

typedef struct {
	uint32_t EEP;
	uint32_t TEP;
} PPI_CHANNEL_TYPE;

typedef struct {
    volatile PPI_TASKS_TYPE PPI_TASKS[6]; // Tasks for Chn Groups (0-5)
    volatile uint32_t RESERVED0[308];     // 308 words to 0x500
    
    volatile uint32_t CHEN;               // Channel enable register        [w]
    volatile uint32_t CHENSET;            // Channel enable set register    [rw]
    volatile uint32_t CHENCLR;            // Channel enable clear register  [rw]
    volatile uint32_t RESERVED1[1];       // 1 word to 0x510

    volatile PPI_CHANNEL_TYPE PPI_CH[20]; // PPI Chns (0-19)
    volatile uint32_t RESERVED2[148];     // 148 words to 0x800
    
    volatile uint32_t CHG[6];             // Channel Groups (0-5)
    volatile uint32_t RESERVED3[62];      // 62 words to 0x910
    
    volatile uint32_t FORK_TEP[32];       // Fork Task End Points (0-31)
} NRF_PPI_REG;

#endif
