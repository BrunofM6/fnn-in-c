#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>

typedef enum
{
    SIGMOID,
    TANH,
    RELU,
    LEAKY_RELU,
    ELU,
    LINEAR,
    SWISH
} activation_fn_t;

typedef struct activation_config
{
    activation_fn_t type;
    float z_value;
    float alpha;
} activation_config;

// fn(neuron value) -> z-value
typedef float (*activation_fn)(activation_config);

// fn(neuron value) -> derivative-z-value
typedef float (*activation_derivative_fn)(activation_config);

float sigmoid(activation_config config);
float sigmoid_derivative(activation_config config);

// float tanh(float z); -> already in math.c
float tanh_act(activation_config config);
float tanh_derivative(activation_config config);

float relu(activation_config config);
float relu_derivative(activation_config config);

float leaky_relu(activation_config config);
float leaky_relu_derivative(activation_config config);

float elu(activation_config config);
float elu_derivative(activation_config config);

float linear(activation_config config);
float linear_derivative(activation_config config);

float swish(activation_config config);
float swish_derivative(activation_config config);

activation_fn get_activation_fn(activation_config config);
activation_derivative_fn get_activation_derivative_fn(activation_config config);

#endif
