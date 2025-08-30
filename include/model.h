#ifndef MODEL_H
#define MODEL_H

#include <stdint.h>

#include "layer.h"
#include "activation.h"

// fn(output_layer, expected_array, len) -last layer deltas-> error_code
typedef model_error_t (*cost_fn)(layer*, float*, int32_t);

// fn(model) -> error_code
typedef model_error_t (*optimizer_fn)(model*);

// fn(parameters_array, len) -apply penalty-> error_code
typedef model_error_t (*regularization_fn)(model*);

typedef struct
{
    layer *layers;
    uint32_t n_layers;

    uint32_t epoch;
    float current_loss;
    float learning_rate;

    activation_fn_t *activation_funs;
    activation_derivative_fn_t *activation_derivative_funs;
    cost_fn cost_fun;
    optimizer_fn optimizer_fun;
    regularization_fn regularization_fun;
} model;

typedef enum
{
    MODEL_SUCCESS = 0,
    MODEL_ERROR_NULL_POINTER,
    MODEL_ERROR_INVALID_DIMENSIONS, // I/O
    MODEL_ERROR_MEMORY_ALLOCATION,
    MODEL_ERROR_FUNCTION_POINTER_NULL,
    MODEL_ERROR_LAYER_MISMATCH, // MODEL DEFINITION
    MODEL_ERROR_ACTIVATION_FAILED,
    MODEL_ERROR_COST_COMPUTATION_FAILED
} model_error_t;

model *create_model(int32_t n_layers, layer *layers, float learning_rate, activation_fn *activation_funs, activation_derivative_fn *activation_derivative_funs, output_fn output_fun, cost_fn cost_fun, optimizer_fn optimizer_fun, regularization_fn regularization_fun);

void destroy_model(model* model);

model_error_t verify_model(model *model);

model_error_t feedforward(model *model, const float *inputs, const int32_t input_len);

model_error_t backpropagation(model *model, const float *expected_outputs, const int32_t output_len);

#endif
