# Feedfoward Neural Networks in C

## Objective
Make neural networks in C from scratch, in hopes of furthering the understanding of how libraries work on a lower level. Want to implement all the basics:


- [Layers](#layers)
- [Activation Functions](#activation-functions)
- [Feedforward](#feedforward)
- [Loss Functions](#loss-functions)
- [Backpropagation](#backpropagation)
- [Gradient Descent](#gradient-descent)

## TODO
- [objects](#objects) []
    - [layer](#layer)[]
    - [model](#model) []
- [operation](#operations)
    - [feedfoward](#feedforward-inference) []
    - [backtracking](#backtracking-learning) []
- activation function []
    - sigmoid []
    - tanh []
    - relu []
- loss operation []
- backpropagation []
- paralelize []

## Objects

### layer
The layer structure encapsulates the parameters and state for a single computational layer within the neural network. Its fields are designed for the [feedforward and backtracking operations](#Operationss) objectives.
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

## Operations
There are two main operations happening:

### Feedforward (inference):
From an input, which serves as the initial *previous layer* with values as *activations*, perform operations, layer by layer based on present weights, biases and activation function.
   
- **Input**: previous layer activations, passed as an argument.
   
- **Uses**: num_inputs, weights and biases.

- **Stores**: z_values, activations.

### Backtracking (learning):
According to an expected result, which is used as the first *delta*, calculated through a designated loss function, perform backpropagation based on 
- **Input**: deltas from *next* layer, passed as an argument.

- **Uses**: weights, biases, z_values, activations and *next layer* deltas.

- **Updates**: weights and biases using calculated gradients.



