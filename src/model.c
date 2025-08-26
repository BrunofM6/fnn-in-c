#include "../include/model.h"
#include "../include/logger.h"

#include <stdint.h>

#define LOG_BUFFER 64

char log_buffer[LOG_BUFFER];

model_error_t verify_layer(layer *layer, int32_t l_index)
{
    if (!layer)
    {
        log_message("Null layer!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (l_index < 0)
    {
        log_message("Invalid layer index!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    if (layer->n_neurons <= 0)
    {
        sprintf(log_buffer, "Layer:%d has invalid (%d) number of neurons!", l_index, layer->n_neurons);
        log_message(log_buffer);
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    if (layer->n_inputs < 0 ||  (l_index == 0 && layer->n_inputs != 0))
    {
        sprintf(log_buffer, "Layer:%d has invalid (&%d) number of inputs!", l_index, layer->n_inputs);
        log_message(log_buffer);
        return MODEL_ERROR_LAYER_MISMATCH;
    }

    if (layer->weights == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL weights!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }

    if (layer->biases == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL biases!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }

    if (layer->z_values== NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL z values!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }    

    if (layer->activations == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL activations!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }

    if (layer->delta_values == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL delta values!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }

    if (layer->weight_gradients == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL weight gradients!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }    

    if (layer->bias_gradients == NULL)
    {
        sprintf(log_buffer, "Layer:%d has NULL bias gradients!", l_index);
        log_message(log_buffer);
        return MODEL_ERROR_NULL_POINTER;
    }

    return MODEL_SUCCESS;
}

model_error_t verify_model(model *model)
{
    if (!model)
    {
        log_message("Null model!");
        return MODEL_ERROR_NULL_POINTER;
    }

    if (model->layers == NULL || model->n_layers <= 0)
    {
        log_message("Invalid number/pointer of/to layers!");
        sprintf(log_buffer, "layers:%d | n_layers:%d", model->layers, model->n_layers);
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
        return MODEL_ERROR_FUNCTION_POINTER_NULL;
    }

    if (model->cost_fun == NULL)
    {
        log_message("Invalid cost function!");
        return MODEL_ERROR_FUNCTION_POINTER_NULL;
    }

    if (model->optimizer_fun == NULL)
    {
        log_message("Invalid optimizer function!");
        return MODEL_ERROR_FUNCTION_POINTER_NULL;
    }

    if (model->regularization_fun == NULL)
    {
        log_message("Invalid regularization function!");
        return MODEL_ERROR_FUNCTION_POINTER_NULL;
    }

    return MODEL_SUCCESS;
}

model_error_t feedforward(model *model, const float *inputs, const int32_t input_len)
{
    model_error_t MODEL_CODE = verify_model(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Feedforward model error!");
        return MODEL_CODE;
    }

    layer *input_layer = model->layers;
    MODEL_CODE = verify_layer(input_layer, 0);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Feedforward input layer error!");
        return MODEL_CODE;
    }

    if (input_layer->n_inputs != input_len)
    {
        log_message("Data and model have different input shape!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    for (int32_t i = 0; i < input_len; i++)
    {
        input_layer->activations[i] = inputs[i];
    }

    layer *current_layer;
    for (int32_t layer_counter = 1; layer_counter < model->n_layers; layer_counter++)
    {
        current_layer = &model->layers[layer_counter];
        MODEL_CODE = verify_layer(current_layer, layer_counter);
        if (MODEL_CODE != MODEL_SUCCESS) {
            log_message("Feedforward current layer error!");
            return MODEL_CODE;
        }
        if (current_layer->n_inputs != input_layer->n_neurons)
        {
            sprintf(log_buffer, "Layer %d has incompatible shape!", layer_counter);
            log_message(log_buffer);
            sprintf(log_buffer, "expected:%d | received:%d", current_layer->n_inputs, input_layer->n_neurons);
            log_message(log_buffer);
            return MODEL_ERROR_LAYER_MISMATCH;
        }

        for (int32_t current_neuron = 0; current_neuron < current_layer->n_neurons; current_neuron++)
        {
            float z = 0.0f;
            for (int32_t current_input = 0; current_input < current_layer->n_inputs; current_input++)
            {
                z += current_layer->weights[current_neuron * current_layer->n_inputs + current_input] * input_layer->activations[current_input];
            }
            z += current_layer->biases[current_neuron];
            current_layer->z_values[current_neuron] = z;

            current_layer->activations[current_neuron] = model->activation_funs[layer_counter](z);
        }
        input_layer = current_layer;
    }

    return MODEL_SUCCESS;
}

model_error_t backpropagation(model *model, const float *expected_outputs, const int32_t output_len)
{
    model_error_t MODEL_CODE = verify_model(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Backpropagation model error!");
        return MODEL_CODE;
    }

    if (model->layers[model->n_layers - 1].n_neurons != output_len)
    {
        log_message("Incompatible model shape with outputs!");
        return MODEL_ERROR_INVALID_DIMENSIONS;
    }

    MODEL_CODE = model->cost_fun(model->layers[model->n_layers - 1], expected_outputs, output_len);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Cost function error!");
        return MODEL_CODE;
    }

    MODEL_CODE = model->regularization_fun(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Regularization error!");
        return MODEL_CODE;
    }

    layer *current_layer, *previous_layer;
    // gradients
    for (int32_t layer_counter = model->n_layers - 1; layer_counter >= 1; layer_counter--)
    {
        current_layer = &model->layers[layer_counter];
        previous_layer = &model->layers[layer_counter - 1];
        
        for (int32_t current_neuron = 0; current_neuron < current_layer->n_neurons; current_neuron++)
        {
            current_layer->bias_gradients[current_neuron] = current_layer->delta_values[current_neuron];
        

            for (int32_t input = 0; input < current_layer->n_inputs; input++)
            {
                int current_weight = current_neuron * current_layer->n_inputs + input;
                current_layer->weight_gradients[current_weight] = current_layer->delta_values[current_neuron] * previous_layer->activations[input];
            }
        }

        // propagate (except to input)
        if (layer_counter > 1)
        {
            for (int32_t previous_neuron = 0; previous_neuron < previous_layer->n_neurons; previous_neuron++)
            {
                float delta_sum = 0.0f;
                
                for (int32_t current_neuron = 0; current_neuron < current_layer->n_neurons; current_neuron++)
                {
                    int32_t weight_idx = current_neuron * current_layer->n_inputs + previous_neuron;
                    delta_sum += current_layer->delta_values[current_neuron] * current_layer->weights[weight_idx];
                }
                
                previous_layer->delta_values[previous_neuron] = delta_sum * model->activation_derivative_funs[layer_counter - 1](previous_layer->z_values[previous_neuron]);
            }
        }
    }

    MODEL_CODE = model->optimizer_fun(model);
    if (MODEL_CODE != MODEL_SUCCESS)
    {
        log_message("Optimizer error!");
        return MODEL_CODE;
    }

    return MODEL_SUCCESS;
}
