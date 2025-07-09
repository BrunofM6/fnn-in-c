#ifndef NEURON_H
#define NEURON_H

typedef struct
{
    float *weights;
    float bias;
    float z; // logits
    float value;

    float *input_cache; // weights backprop value
    int input_size;

    float delta; // error gradient
} neuron;

#endif
