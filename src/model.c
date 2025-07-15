#include <stdint.h>

#include "../include/model.h"

#include "../utils/logger.c"

#define LOG_BUFFER 64

void feedforward(model model, float *inputs, int32_t input_len)
{
    if (model.layers == NULL|| model.n_layers <= 0)
    {
        log_message("Invalid number of layers!");
        char log_buffer[LOG_BUFFER];
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

    model.epoch++;

    layer *input_layer = model.layers[0];

    if (input_layer->n_inputs != input_len)
    {
        log_message("Data and model have different input shape!");
        return;
    }

    

    model.current_loss += loss;
}
