#pragma once


/*output_after -> activation function -> weight -> output_before

Last-Layer:
MSE_dev * output_after * sigmoid_dev * output_before

Layer-before-last:
Last-Layer * weight 

Last-Layer * SGD * MSE_dev * output_after * sigmoid_dev

Layer-before-last:
Last-Layer * Layer-before-last * weight * MSE_dev * output_after * sigmoid_dev


*/
