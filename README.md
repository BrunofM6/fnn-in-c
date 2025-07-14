# Feedforward Neural Networks in C

## Objective
Make feedfoward neural networks in C from scratch, in hopes of furthering the understanding of how libraries work on a lower level.

This is the development roadmap

- [Objects](#Objects) [X]
    - [layer](#layer)[X]
    - [model](#lodel) [X]
- [Operations](#Operations) []
    - [feedfoward](#Feedforward) []
    - [backpropagation](#Backpropagation-Learning) []
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
These are the parameters:

- **num_neurons**: neuron count in layer.

- **num_inputs**: input values layer receives.

- **weights**: 2D matrix holding weights of the previous layer per neuron, used to compute *z*.

- **biases**: list of biases per neuron, used to compute *z*.

- **z_values**: list of *z* (logit) values per neuron.

- **activations**: list of values after transformation per neuron.

- **delta_values**: list of delta values per neuron.

#### neuron
----
A neuron of index *n* is represented through:

- weights[n][*input_index**] -> *weight*

    - ∀ *input_index* ∈ [0, num_neurons]

- bias[n] -> *bias*

- z_values[n] -> *z*

- delta_values[n] -> *delta*

### model
The 'model' structure encapsulates the Feedforward Neural Network, with an associated array of layers, number of layers, activation, optimizer type and cost function pointers to allow for modularity, as well as learning rate, current loss, epoch and batch size.

## Operations
There are two main operations happening:

### Feedforward (inference):
From an input, which serves as the initial *previous layer* with values as *activations*, perform operations, layer by layer based on present weights, biases and activation function.
   
- **Input**: previous layer activations, passed as an argument.
   
- **Uses**: num_inputs, weights and biases.

- **Stores**: z_values, activations.

Implemented on model.c's 'inference' method. Is the same for all instances on model.

### Backtracking
According to an expected result, which is used as the first *delta*, calculated through a designated loss function, perform backpropagation based on 
- **Input**: deltas from *next* layer, passed as an argument.

- **Uses**: weights, biases, z_values, activations and *next layer* deltas.

- **Updates**: weights and biases using calculated gradients.

Stored on model.c's 'backtracking' method, which means it can be different on a model by model basis.
