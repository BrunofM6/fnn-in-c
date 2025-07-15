#include <stdint.h>

#include "../include/model.h"

#include "../utils/logger.c"

#define LOG_BUFFER 64

char log_buffer[LOG_BUFFER];

void feedforward(model model, float *inputs, int32_t input_len)
{
    if (model.layers == NULL|| model.n_layers <= 0)
    {
        log_message("Invalid number of layers!");
        sprintf(log_buffer, "layers:%p | n_layers:%d", model.layers, model.n_layers);
        log_message(log_buffer);
        return;
    }

    if (model.learning_rate <= 0)
    {
        log_message("Invalid learning rate!");
        return;
    }

    if (model.activation_fun == NULL)
    {
        log_message("Invalid activation function!");
        return;
    }

    if (model.cost_fun == NULL)
    {
        log_message("Invalid cost function!");
        return;
    }

    if (model.optimizer_fun == NULL)
    {
        log_message("Invalid optimizer function!");
        return;
    }

    if (model.regularization_fun == NULL)
    {
        log_message("Invalid regularization function!");
        return;
    }

    layer *input_layer = model.layers[0];

    if (input_layer->n_inputs != input_len)
    {
        log_message("Data and model have different input shape!");
        return;
    }

    for (int32_t i = 0; i < input_len; i++)
    {
        input_layer->activations[i] = inputs[i];
    }

    layer *current_layer;
    for (int32_t layer_count = 1; layer_count < model.n_layers; layer_count++)
    {
        current_layer = model.layers[layer_count];
        if (current_layer->n_inputs != input_layer->n_neurons)
        {
            sprintf(log_buffer, "Layer %d has incompatible shape!", layer_count);
            log_message(log_buffer);
            sprintf(log_buffer, "expected:%d | received:%d", current_layer->n_inputs, input_layer->n_neurons);
            log_message(log_buffer);
            return;
        }

        for (int32_t current_neuron = 0; current_neuron < current_layer->n_neurons; current_neuron++)
        {
            float z = 0;
            for (int32_t current_input = 0; current_input < current_layer->n_inputs; current_input++)
            {
                z += current_layer->weights[current_input][current_neuron] * input_layer->activations[current_input];
            }
            z += current_layer->biases[current_neuron]
            current_layer->z_values[current_neuron] = z;

            current_layer->activations[current_neuron] = model.activation_fun(z);
        }
        input_layer = current_layer;
    }
}
