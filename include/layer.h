#ifndef LAYER_H
#define LAYER_H

#include <stdint.h>

typedef struct 
{
    int32_t n_neurons;
    int32_t n_inputs;
    float **weights;
    float *biases;

    float *z_values;
    float *activations;
    
    float *delta_values;
} layer;

#endif