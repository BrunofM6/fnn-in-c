#ifdef LAYER_H
#define LAYER_h

typedef struct 
{
    int num_neurons;
    int num_inputs;
    float **weights;
    float *biases

    float *z_values;
    float *activations;
    
    float *delta_values;
} layer;

#endif