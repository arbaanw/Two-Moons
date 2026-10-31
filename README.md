# NEURAL NETWORK FROM SCRATCH
This neural network was built in c++ from scratch to classify a custom-generated **two-moons dataset**.

## ARCHITECTURE

Number of layers: 4
### breakdown:
| Layer    | Neurons | Activation |
|----------|---------|------------|
| Input    | 2       | —          |
| Hidden 1 | 10      | ReLU       |
| Hidden 2 | 10      | ReLU       |
| Output   | 1       | Sigmoid    |

## DATASET

Two-Moons refers to two crescent shaped classes on a graph. Which Looks something like this 
![two-moons](assets/images/graph.png)

The dataset was generated using the following equations:
![two-moons equation](assets/images/two-moons-eqn.png)

A few samples:
```
0.748503,0.663131,0
0.878580,0.477595,0
1.231476,-0.472841,1
1.535606,-0.344468,1
0.101983,0.060040,1
```
- Training Dataset contains 149,948 samples
- Testing Dataset contains 50,000 samples

## IMPLEMENTATION
### Initialization of weights
- Hidden layers: He initialization
- Output layer: Xavier initialization
### Initialization of biases
- initialized to 0
### Forward Pass
- Weighted Sum is calculated
- ReLU activation function is applied to both hidden layers
- Sigmoid activation function is applied to output layer
### Cost Function
Binary Cross Entropy: 
L(y, ŷ) = -[y log(ŷ) + (1 - y) log(1 - ŷ)]
### Backpropagation
- Backpropagation using the chain rule
- Weight and bias gradient calculations
- Stochastic gradient descent (SGD)

## TRAINING
1. The network uses stochastic gradient descent (SGD), updating its weights and biases after each training sample.
2. The training process:
3. Load the training dataset.
4. Perform forward propagation.
5. Calculate binary cross-entropy loss.
6. Calculate gradients through backpropagation.
7. Update weights and biases.
8. Repeat for multiple epochs.

## EVALUATION
The trained model is evaluated using a separate testing dataset.

Evaluation metrics:
- Average binary cross-entropy loss.
- Classification accuracy.

A prediction threshold of 0.5 is used to convert output probabilities into binary classes.
![accuracy equation](assets/images/accuracy-eqn.png)

## RESULTS

The model was evaluated on 50,000 previously unseen testing samples.

| Metric | Result |
|---|---:|
| Training samples | 149,948 |
| Testing samples | 50,000 |
| Test Accuracy | 100.00% |
| Epochs | 6 |

## TECHNOLOGIES
- C++
- Eigen 3.4
- Python
- matplotlib
- g++
