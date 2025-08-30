#ifndef LOSS_H
#define LOSS_H

// CE -> cross-entropy
// M[...]E -> mean [...] error
typedef enum
{
    // regression
    MSE, // squared 
    MAE, // absolute
    HUBER, // huber loss
    MSLE, // logarithmic

    // classification
    BCE, // binary
    CCE, // categorical
    SCCE, // sparse categorical
} loss_fn_t;



// fn(output_layer, expected_array, len) -last layer deltas-> error_code
typedef model_error_t (*loss_fn)(layer*, float*, int32_t);

#endif
