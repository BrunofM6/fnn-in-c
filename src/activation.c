#include "../include/activation.h"

float sigmoid(activation_config config)
{
    return 1.0f / (1.0f + expf(-config.z_value));
}

float sigmoid_derivative(activation_config config)
{
    float s = sigmoid(config);
    return s * (1.0f - s);
}

float tanh_act(activation_config config)
{
    return tanhf(config.z_value);
}

float tanh_derivative(activation_config config)
{
    float t = tanh_act(config);
    return 1.0f - (t * t);
}

float relu(activation_config config)
{
    return (config.z_value > 0.0f) ? config.z_value : 0.0f;
}

float relu_derivative(activation_config config)
{
    return (config.z_value > 0.0f) ? 1.0f : 0.0f;
}

float leaky_relu(activation_config config)
{
    return (config.z_value > 0.0f) ? config.z_value : (config.alpha * config.z_value);
}

float leaky_relu_derivative(activation_config config)
{
    return (config.z_value > 0.0f) ? 1.0f : config.alpha;
}

float elu(activation_config config)
{
    return (config.z_value > 0.0f) ? config.z_value : (config.alpha * (expf(config.z_value) - 1));
}

float elu_derivative(activation_config config)
{
    return (config.z_value > 0.0f) ? 1.0f : (config.alpha * expf(config.z_value));
}

float linear(activation_config config)
{
    return config.z_value;
}

float linear_derivative(activation_config config)
{
    (void)config;
    return 1.0f;
}

float swish(activation_config config)
{
    return config.z_value * sigmoid(config);
}

float swish_derivative(activation_config config)
{
    float s = sigmoid(config);
    return s + config.z_value * s * (1.0f - s);
}

activation_fn get_activation_fn(activation_config config)
{
    activation_fn_t type = config.type;
    switch (type)
    {
        case SIGMOID:
            return &sigmoid;
        case TANH:
            return &tanh_act;
        case RELU:
            return &relu;
        case LEAKY_RELU:
            return &leaky_relu;
        case ELU:
            return &elu;
        case LINEAR:
            return &linear;
        case SWISH:
            return &swish;
        default:
            return NULL;
    }
}

activation_derivative_fn get_activation_derivative_fn(activation_config config)
{
    activation_fn_t type = config.type;
    switch (type)
    {
        case SIGMOID:
            return &sigmoid_derivative;
        case TANH:
            return &tanh_derivative;
        case RELU:
            return &relu_derivative;
        case LEAKY_RELU:
            return &leaky_relu_derivative;
        case ELU:
            return &elu_derivative;
        case LINEAR:
            return &linear_derivative;
        case SWISH:
            return &swish_derivative;
        default:
            return NULL;
    }
}