#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>

#include "layer.h"

// fn(neuron value) -> z-value
typedef float (*activation_fn)(float);

// fn(real_array, expected_array, len) -> total_cost
typedef float (*cost_fn)(float*, float*, int32_t);

// 'weights' in this context is any tunable parameter
// fn(weights_array, gradient_array, len, rate) -> nothing
typedef void (*optimizer_fn)(float*, float*, int32_t, float);

// fn(parameters_array, len) -> penalty
typedef float (*regularization_fn)(float*, int32_t);

typedef struct
{
    layer *layers;

    int32_t n_layers;
    int32_t epoch;

    float current_loss;
    float learning_rate;

    activation_fn *activation_fun;
    cost_fn cost_fun;
    optimizer_fn optimizer_fun;
    regularization_fn regularization_fun;
} model;

#endif
