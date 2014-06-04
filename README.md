# EEG-Based-BCI

## Overview
A project to obtain EEG signals from a neuroheadset and process the subsequent data produced for classification of objects. With adequate training, the model can be used to idenity the objects seen by a person wearing the headset. The neuroheadset used was the Emotiv Epoc headset which has 14 sensors giving reading of EEG activities.

## Methodology
The processing of the EEG signals is done through a basic three step method:

1. Converting EEG signals to readings or values
2. Singular Value Decomposition
3. Classification

There are two kinds of use cases involving these:

1. Training the model involves employing the first two steps with known, labeled data
2. Classification involves using all the three steps including the training data produced from step 1

### Convertig EEG signals to values
This step is accomplished using an example application in the Emotiv SDK implemented in C++. The code was modified slightly to collect readings for about 10 seconds and write them to a file. The values are space separated.

### Singular Value Decomposition
Singular Value Decompostion (SVD) is used to remove noise from the values obtained. The eigen vectors and eigen values of the data are obtained by applying SVD. The eigen values and their corresponding eigen vectors are sorted in decreasing order of eigen values. The sum of the eigen values is found and the eigen values that contribute 99% of this sum are retained and the ones that contribute to the last 1% are set to zero (0). This removes the effect of the eigen vectors corresponding to these eigen values. The rationale is that the small contributions from these eigen vectors must represent noise. This module is implemented in C/C++.

### Classification
The final task is to classify the records into one of the labels defined using training. The model can be built as the training is being performed (early learner approach) or when classification needs to be performed (late learners approach). The project uses k Nearest Neighbors (kNN) algorithm of [scikit-learn](http://scikit-learn.org/stable/modules/neighbors.html) implemented in Python. This is a late learners technique. This takes longer to classify as it involves a lot of computation at the time classification needs to be performed. Approaches like Decision Trees or Rule based classifiers can allow for fast classification as the model is created during training.

## Web UI
The web page made using PHP offers a simple interface for the user to train and classify new readings using training data.
