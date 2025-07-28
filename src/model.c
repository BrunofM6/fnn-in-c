#include "../include/model.h"
#include "../include/logger.h"

#include <stdint.h>

#define LOG_BUFFER 64

char log_buffer[LOG_BUFFER];

model_error_t verify_model(model *model)
{
    if (!model)
    {
        log_message("Null model!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (model->layers == NULL|| model->n_layers <= 0)
    {
        log_message("Invalid number of layers!");
        sprintf(log_buffer, "layers:%p | n_layers:%d", model->layers, model->n_layers);
        log_message(log_buffer);
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    if (model->learning_rate <= 0)
    {
        log_message("Invalid learning rate!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    if (model->activation_funs == NULL)
    {
        log_message("Invalid activation function!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (model->cost_fun == NULL)
    {
        log_message("Invalid cost function!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (model->optimizer_fun == NULL)
    {
        log_message("Invalid optimizer function!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (model->regularization_fun == NULL)
    {
        log_message("Invalid regularization function!");
        return MODEL_ERROR_NULL_POINTER;
    }

    layer *input_layer = model->layers[0];

    if (input_layer->n_inputs != input_len)
    {
        log_message("Data and model have different input shape!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    return MODEL_SUCCESS;
}

model_error_t feedforward(const model *model, const float *inputs, const int32_t input_len)
{
    model_error_t MODEL_CODE = verify_model(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        return MODEL_CODE;
    }

    for (int32_t i = 0; i < input_len; i++)
    {
        input_layer->activations[i] = inputs[i];
    }

    layer *current_layer;
    for (int32_t layer_count = 1; layer_count < model->n_layers - 1; layer_count++)
    {
        current_layer = model->layers[layer_count];
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
            z += current_layer->biases[current_neuron];
            current_layer->z_values[current_neuron] = z;

            current_layer->activations[current_neuron] = model->activation_funs(z);
        }
        input_layer = current_layer;
    }

    current_layer = model->layers[model->n_layers - 1];
    for (int32_t output_neuron = 0; output_neuron < current_layer->n_neurons; output_neuron++)
    {
        current_layer->activations[output_neuron] = model->output_fun(input_layer[output_neuron]);
    }

    return MODEL_SUCCESS;
}

model_error_t backpropagation(model *model, const float *expected_outputs, const int32_t output_len)
{
    model_error_t MODEL_CODE = verify_model(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        return MODEL_CODE;
    }

    if (model->layers[model->n_layers - 1]->n_neurons != output_len)
    {
        log_message("Incompatible model shape with outputs!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    MODEL_CODE = model->cost_fun(model->layers[model->n_layers - 1]);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Cost function error!");
        return MODEL_CODE;
    }


    MODEL_CODE = model->optimizer_fun(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Optimizer error!");
        return MODEL_CODE;
    }
    
    MODEL_CODE = model->regularization_fun(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Regularization error!");
        return MODEL_CODE;
    }

    return MODEL_SUCCESS;
}
