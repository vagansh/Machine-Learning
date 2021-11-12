#include <fstream>
#include <iostream>
using namespace std;

// Edit MACROs here, according to your Matrix Dimensions for w_i_h[R1][C1] and input[R2][C2]
#define R1 2 // number of rows in Matrix-1
#define C1 2 // number of columns in Matrix-1
#define R2 2 // number of rows in Matrix-2
#define C2 1 // number of columns in Matrix-2

void printArray(float theArray[][1], int sizeOfRow, int sizeOfCol)
{
    for (int x = 0; x < sizeOfRow; x++) {
        for (int y = 0; y < sizeOfCol; y++) {
            cout << theArray[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printArray2(float theArray[][2], int sizeOfRow, int sizeOfCol)
{
    for (int x = 0; x < sizeOfRow; x++) {
        for (int y = 0; y < sizeOfCol; y++) {
            cout << theArray[x][y] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(void)
{
    //Input to the neural network.
    float input[R2][C2] = {
        { 0.05 },
        { 0.10 }
    };

    float error_array[100];

    //Weight from input layer to hidden layer.
    // Row 1: Weight from input neurons to the first neuron in the hidden layer.
    // Row 2: Weight from input neurons to the second neuron in the hidden layer.
    float w_i_h[R1][C1] = {
        { 0.15, 0.20 },
        { 0.25, 0.30 }
    };

    //Weight from input layer to hidden layer.
    // Row 1: Weight from input neurons to the first neuron in the hidden layer.
    // Row 2: Weight from input neurons to the second neuron in the hidden layer.
    float w_h_o[R1][C1] = {
        { 0.40, 0.45 },
        { 0.50, 0.55 }
    };
    float bias[] = { 0.35, 0.60 };

    //learning rate
    float eta = 0.50;

    for (int a = 0; a < 100; a++) {

        // 2-D array containing the output of input neurons and weights connecting input layer to the hidden layer.
        float rslt[R1][C2];

        for (int i = 0; i < R1; i++) {
            for (int j = 0; j < C2; j++) {
                rslt[i][j] = 0;

                for (int k = 0; k < R2; k++) {
                    rslt[i][j] = rslt[i][j] + w_i_h[i][k] * input[k][j];
                }
                //ading bias to the net activation from the input layer
                rslt[i][j] = rslt[i][j] + bias[0];
            }
            cout << endl;
        }

        cout << "Result of net activation from input to hidden layer" << endl;
        printArray(rslt, 2, 1);

        //Computing the final output of the hidden layer neurons. We have used the sigmoid activation function.

        float hidden_1_output[R2][C2] = {
            { 1 / (1 + exp(-rslt[0][0])) },
            { 1 / (1 + exp(-rslt[1][0])) }
        };

        cout << "Net output from hidden layer neurons" << endl;
        printArray(hidden_1_output, 2, 1);

        // 2-D array containing the output of input hidden layer neurons and weights connecting it to the output layer.
        float rslt2[R1][C2];

        for (int i = 0; i < R1; i++) {
            for (int j = 0; j < C2; j++) {
                rslt2[i][j] = 0;

                for (int k = 0; k < R2; k++) {
                    rslt2[i][j] = rslt2[i][j] + w_h_o[i][k] * hidden_1_output[k][j];
                }
                //ading bias to the net activation from the input layer
                rslt2[i][j] = rslt2[i][j] + bias[1];
            }

            cout << endl;
        }

        cout << "Result of net activation from hidden to output layer" << endl;
        printArray(rslt2, 2, 1);

        //Computing the final output of neural network. We have used the sigmoid activation function.
        float final_output[R2][C2] = {
            { 1 / (1 + exp(-rslt2[0][0])) },
            { 1 / (1 + exp(-rslt2[1][0])) }
        };

        cout << "Net output from hidden layer neurons" << endl;
        printArray(final_output, 2, 1);

        //computing error
        float target_output[R2][C2] = {
            { 0.01 },
            { 0.99 }
        };

        float error = pow((final_output[0][0] - target_output[0][0]), 2) + pow((final_output[1][0] - target_output[1][0]), 2);
        error = error / 2;
        error_array[a] = error;
        cout << "The error is  " << error << endl;

        //Updating the weight from output layer to hidden layer
        //Since, for updating weight from hidden to input layer we require original weights,
        //we first update weights in input to hidden layer, because when we update weight from,
        //output to hidden layer, they might get changed.
        //For updating weight from hidden layer to input layer, we need original weights.

        // Updating weight_1
        float subtracting_factor = (target_output[0][0] - final_output[0][0]) * (-1) * (final_output[0][0]) * (1 - final_output[0][0]) * w_h_o[0][0];
        subtracting_factor = subtracting_factor + (target_output[1][0] - final_output[1][0]) * (-1) * (final_output[1][0]) * (1 - final_output[1][0]) * w_h_o[1][0];
        subtracting_factor = subtracting_factor * hidden_1_output[0][0] * (1 - hidden_1_output[0][0]) * input[0][0];

        w_i_h[0][0] = w_i_h[0][0] - eta * subtracting_factor;
        cout << "Updated weight 1  " << w_i_h[0][0] << endl;

        //Updating weight_2
        subtracting_factor = (target_output[0][0] - final_output[0][0]) * (-1) * (final_output[0][0]) * (1 - final_output[0][0]) * w_h_o[0][0];
        subtracting_factor = subtracting_factor + (target_output[1][0] - final_output[1][0]) * (-1) * (final_output[1][0]) * (1 - final_output[1][0]) * w_h_o[1][0];
        subtracting_factor = subtracting_factor * hidden_1_output[0][0] * (1 - hidden_1_output[0][0]) * input[1][0];

        w_i_h[0][1] = w_i_h[0][1] - eta * subtracting_factor;
        cout << "Updated weight 2  " << w_i_h[0][1] << endl;

        //Updating weight_3
        subtracting_factor = (target_output[0][0] - final_output[0][0]) * (-1) * (final_output[0][0]) * (1 - final_output[0][0]) * w_h_o[0][1];
        subtracting_factor = subtracting_factor + (target_output[1][0] - final_output[1][0]) * (-1) * (final_output[1][0]) * (1 - final_output[1][0]) * w_h_o[1][1];
        subtracting_factor = subtracting_factor * hidden_1_output[1][0] * (1 - hidden_1_output[1][0]) * input[0][0];

        w_i_h[1][0] = w_i_h[1][0] - eta * subtracting_factor;
        cout << "Updated weight 3  " << w_i_h[1][0] << endl;

        //Updating weight_4
        subtracting_factor = (target_output[0][0] - final_output[0][0]) * (-1) * (final_output[0][0]) * (1 - final_output[0][0]) * w_h_o[0][1];
        subtracting_factor = subtracting_factor + (target_output[1][0] - final_output[1][0]) * (-1) * (final_output[1][0]) * (1 - final_output[1][0]) * w_h_o[1][1];
        subtracting_factor = subtracting_factor * hidden_1_output[1][0] * (1 - hidden_1_output[1][0]) * input[1][0];

        w_i_h[1][1] = w_i_h[1][1] - eta * subtracting_factor;
        cout << "Updated weight 4  " << w_i_h[1][1] << endl;

        //Updating weight from hidden layer to output layer

        //Updating weight_5
        subtracting_factor = -(target_output[0][0] - final_output[0][0]) * final_output[0][0] * (1 - final_output[0][0]) * hidden_1_output[0][0];
        w_h_o[0][0] = w_h_o[0][0] - eta * subtracting_factor;
        cout << "Updated weight 5  " << w_h_o[0][0] << endl;

        //Updating weight_6
        subtracting_factor = -(target_output[0][0] - final_output[0][0]) * final_output[0][0] * (1 - final_output[0][0]) * hidden_1_output[1][0];
        w_h_o[0][1] = w_h_o[0][1] - eta * subtracting_factor;
        cout << "Updated weight 6  " << w_h_o[0][1] << endl;

        //Updating weight_7
        subtracting_factor = -(target_output[1][0] - final_output[1][0]) * final_output[1][0] * (1 - final_output[1][0]) * hidden_1_output[0][0];
        w_h_o[1][0] = w_h_o[1][0] - eta * subtracting_factor;
        cout << "Updated weight 7  " << w_h_o[1][0] << endl;

        //Updating weight_8
        subtracting_factor = -(target_output[1][0] - final_output[1][0]) * final_output[1][0] * (1 - final_output[1][0]) * hidden_1_output[1][0];
        w_h_o[1][1] = w_h_o[1][1] - eta * subtracting_factor;
        cout << "Updated weight 8  " << w_h_o[1][1] << endl;

        cout << "Updated weights from input layer to hidden layer  " << endl
             << endl;
        printArray2(w_i_h, 2, 2);

        cout << "Updated weights from hidden layer to the output layer" << endl
             << endl;
        printArray2(w_h_o, 2, 2);
    }

    //ofstream errorFile;
    //errorFile.open("err_100_3.csv");

    //for (int a = 0; a < 100; a++) {
    //    if (a == 0)
    //        errorFile << "Errors" << endl;

    //    errorFile << error_array[a] << " , " << endl;
    //}

  //  errorFile.close();

    return 0;
}
