#pragma once
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct _WeightMatrix {
	int _rows;
	int _cols;
	vector<float> _weights;
} WeightMatrix;

typedef struct _NeuronsLayer {
	int _width;
	int _height;
	vector<float> _layer_output_vector;//record the last output
} NeuronsLayer;


class MemoryPredictNN
{
private:
	//////////////////////////////////////////////////////////////////////////
	//general
	//////////////////////////////////////////////////////////////////////////
	//NN status
	int _layers;

	vector<NeuronsLayer> _neurons_layers;//include input layer, output layer and middle layer
	vector<WeightMatrix> _pattern_matrix;//the weight matrix between the adjacent layers. the rows is the number of neurons of the lower layer and the cols is the upper layer.
	vector<WeightMatrix> _prediction_matrix;//the weight matrix among the neurons in the layer.
	vector<WeightMatrix> _inhibition_matrix;

	//parameters
	int _input_layer_neuron_central_field;//unit:the pixel; positive field
	int _input_layer_neuron_surround_field;//unit:the number of neuron; negative field, which define the diameter of prediction in the input layer
	int _input_layer_width;//the number of neurons
	int _input_layer_height;//the number of neurons

	float _layer_shrink_ratio;//(0,1]. the number of neurons in the i-th layer is n_i = n_{i-1}* _layer_shrink_ratio
	int _receptive_field;//the number of links from the i-1 layer accepted by the neuron in the i layer (except for the input layer)
	int _max_axons; //the maximum number of links generated by the neuron
	int _prediction_field;// the maximum radius of surrounding neurons in the layer, where the neurons will be associated with the neuron.
	int _inhibition_field;// the maximum radius of surrounding neurons in the layer, where the neurons will be inhibited from activing by the neuron.
	int _neuron_active_hold_duration;//the steps of neuron keeping activation. by default: 1.

	//train data
	vector<float>	_train_data;
	int				_train_data_label;
	int				_train_data_width;
	int				_train_data_height;


	//////////////////////////////////////////////////////////////////////////
	//minst
	//////////////////////////////////////////////////////////////////////////
	ifstream _minst_train_image;
	ifstream _minst_train_label;
	ifstream _minst_test_image;
	ifstream _minst_test_label;

	__int32 _minst_train_image_number;
	__int32 _minst_train_image_rows;
	__int32 _minst_train_image_cols;
	__int32 _minst_train_label_number;
	int _read_minst_train_image_number;

	__int32 _minst_test_image_number;
	__int32 _minst_test_image_rows;
	__int32 _minst_test_image_cols;
	__int32 _minst_test_label_number;
	int _read_minst_test_image_number;

	vector<char> _minst_train_image_buf;
	char _minst_train_image_buf_label;
	vector<char> _minst_test_image_buf;
	char _minst_test_image_buf_label;

public:
	//////////////////////////////////////////////////////////////////////////
	//general
	//////////////////////////////////////////////////////////////////////////
	MemoryPredictNN(void);
	~MemoryPredictNN(void);
	//mpnn
	bool CreateInputLayer();
	bool CreateLayer();
	bool TrainInputLayer();
	bool TrainLayer(int layer);

	float active_sigmoid(int layer, int nid);
	float active_relu(int layer, int nid);
	float active_tanh(int layer, int nid);

	float active_input_neuron(int r, int c);

	//////////////////////////////////////////////////////////////////////////
	//minst
	//////////////////////////////////////////////////////////////////////////
	bool OpenMINSTTrainImage(string image, string label);
	bool ReadNextMINSTTrainImage();
	bool LearnMINSTImage();
	bool CloseMINSTTrainImage();

	bool OpenMINSTTestImage(string image, string label);
	bool ReadNextMINSTTestImage();
	bool RecognativeMINSTImage();
	bool CloseMINSTTestImage();

};

