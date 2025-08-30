#ifndef LAYER_H
#define LAYER_H

#include <stdint.h>

typedef struct
{
    uint32_t n_neurons;
    uint32_t n_inputs;
    float *weights;
    float *biases;

    float *z_values;
    float *activations;
    
    float *delta_values;

    float *weight_gradients;
    float *bias_gradients;
} layer;

layer *create_layer(int32_t n_neurons, int32_t n_inputs);

void destroy_layer(layer *layer);

#endif
