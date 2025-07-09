#ifdef LAYER_H
#define LAYER_h

typedef struct 
{
    float **weights;
    float *biases
    int *layer_size;

    float *z_values;
    float *activations;
    
    float *delta_values;
} layer;

#endif