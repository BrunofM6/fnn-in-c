# Feedforward Neural Networks in C

## Objective
Make feedfoward neural networks in C from scratch, in hopes of furthering the understanding of how libraries work on a lower level. Also trained some nice gitflow.

This is the development roadmap

- [Objects](#Objects) [X]
    - [layer](#layer)[X]
    - [model](#lodel) [X]
- [Logger](#Logger) [X]
- [Operations](#Operations) []
    - [feedfoward](#Feedforward) [X]
    - [backpropagation](#Backpropagation) []
- Activation Function []
    - sigmoid []
    - tanh []
    - relu []
- Loss Operation []
- Training Loop []
- Paralelize []

## Objects

### layer
The 'layer' structure encapsulates the parameters and state for a single computational layer within the neural network. Its fields are designed for the [feedforward and backtracking operations](#operations).

Parameters:
- **n_neurons**: neuron count in layer.

- **n_inputs**: input values layer receives.

- **weights**: 2D matrix holding input weights of the layer per neuron, used to compute *z*.

- **biases**: list of biases per neuron, used to compute *z*.

- **z_values**: list of *z* (logit) values per neuron.

- **activations**: list of values after transformation per neuron.

- **delta_values**: list of delta values per neuron.

#### neuron
----
A neuron of index *n* is represented through:

- weights[*input_index**][n] -> *weight* (W^T)

    - ∀ *input_index* ∈ [0, n_neurons]

- bias[n] -> *bias*

- z_values[n] -> *z*

- delta_values[n] -> *delta*

### model
The 'model' structure encapsulates the Feedforward Neural Network, managing its configuration, state, and function pointers for flexibility in defining activation, loss, optimization, and regularization behaviours. It's designed for modularity and extensibility.

Parameters:
- **layers**: pointer to an array of layer structures representing each layer of the network, ordered from input to output.

- **n_layers**: total number of layers in the network.

- **epoch**: current training epoch counter, tracking how many full passes over the dataset have occurred.

- **current_loss**: stores the loss value computed during the last forward and backward pass, useful for monitoring training progress.

- **learning_rate**: scalar controlling the step size during parameter updates in optimization.

- **activation_fun**: pointer to an array of activation functions (one per layer), where each function transforms the layer’s weighted inputs (z_values) into activations.

- **cost_fun**: pointer to the cost (loss) function used to evaluate the error between predicted outputs and target outputs.

- **optimizer_fun**: pointer to the optimizer function, responsible for updating the model’s weights and biases based on gradients, learning rate, and optionally other parameters.

- **regularization_fun**: pointer to the regularization function that computes penalty terms to discourage overfitting by adding constraints on weights.

Apropriate `typedef` definitions were utilized to enforce 32-bit float type for all elements expect length, which use 32-bit ints.

## Logger 
Simple implementation of a logger that writes into the 'log/log.txt' file at source.

### log_message()
Takes in message and records it with associated timestamp.

### clear_logger()
Clears text file.

#### Format
[%Y-%m-%d %H:%M:%S] [message]

## Operations
There are two main operations happening:

### Feedforward
From an input, which serves as the initial *previous layer* with values as *activations*, perform operations, layer by layer based on present weights, biases and activation function.

- **Input**: previous layer activations, passed as an argument.
   
- **Uses**: n_inputs, weights and biases.

- **Stores**: z_values, activations.

Implemented on model.c's 'inference' method. Is the same for all instances on model.

### Backpropagation
According to an expected result, which is used as the first *delta*, calculated through a designated loss function, perform backpropagation.

- **Input**: deltas from *next* layer, passed as an argument.

- **Uses**: weights, biases, z_values, activations and *next layer* deltas.

- **Updates**: weights and biases using calculated gradients.

Stored on model.c's 'backtracking' method, which means it can be different on a model by model basis.
