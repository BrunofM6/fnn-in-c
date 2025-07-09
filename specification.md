# Feedfoward Neural Networks in C

## Objective
Make neural networks in C from scratch, in hopes of furthering the understanding of how libraries work on a lower level. Want to implement all the basics:

- [Neurons](#neuron)
- [Layers](#layers)
- [Activation Functions](#activation-functions)
- [Feedforward](#feedforward)
- [Loss Functions](#loss-functions)
- [Backpropagation](#backpropagation)
- [Gradient Descent](#gradient-descent)

## TODO
- objects []
    - neuron []
    - layer[]
- activation function []
    - sigmoid []
    - tanh []
    - relu []
- feedfoward operation []
- loss operation []
- backpropagation []
- paralelize []

## Objects

### neuron.h
The neuron structure represents a single artificial neuron. Each neuron maintains the data necessary to perform forward propagation, cache inputs for backward propagation, and stores error gradients for learning.

- **weights**: The weights controlling the influence of each input on the neuron's output. These are adjusted during training to minimize the error.

**bias**: A constant value added to the weighted sum before applying the activation function. It allows the neuron to shift the activation threshold.

**z**: The raw weighted sum of inputs plus bias (also called the logits). This is the value the activation function processes to produce the output value.

**value**: The output of the neuron after applying the activation function to the weighted sum (z). This is the value passed forward to subsequent layers.

**input_cache**: Stores the inputs received during the last forward pass. These cached inputs are essential for calculating gradients with respect to weights during backpropagation.

- **input_size**: Specifies how many inputs the neuron has, basically size of previous layer, always 1 in input layer.

**delta**: The error term calculated during backpropagation. It quantifies how much this neuron contributed to the total error, guiding the adjustment of weights and bias.

