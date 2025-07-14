#ifndef LAYER_H
#define LAYER_H

#include <stdint.h>

typedef struct 
{
    int32_t num_neurons;
    int32_t num_inputs;
    float **weights;
    float *biases;

    float *z_values;
    float *activations;
    
    float *delta_values;
} layer;

#endif