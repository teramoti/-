#include "MyNeuralNetwork.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>


//---------------------------------------------------------------------------
/*Å@
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Neural Networks, Chapter 14
*/
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetworkLayer Class
/////////////////////////////////////////////////////////////////////////////////////////////////
NeuralNetworkLayer::NeuralNetworkLayer()
{
	m_parentLayer = NULL;
	m_childLayer = NULL;
	m_linearOutput = false;
	m_useMomentum = false;
	m_momentumFactor = 0.9;
}

void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{

	// Allocate memory
	m_neuronValues = (float*) malloc(sizeof(float) * m_numberOfNodes);
	m_desiredValues = (float*) malloc(sizeof(float) * m_numberOfNodes);
	m_errors = (float*) malloc(sizeof(float) * m_numberOfNodes);

	if(parent != NULL) {		
		m_parentLayer = parent;
	}

	if(child != NULL) {
		m_childLayer = child;

		m_weights = (float**) malloc(sizeof(float*) * m_numberOfNodes);
		m_weightChanges = (float**) malloc(sizeof(float*) * m_numberOfNodes);
		for(int i = 0; i<m_numberOfNodes; i++) {
			m_weights[i] = (float*) malloc(sizeof(float) * m_numberOfChildNodes);
			m_weightChanges[i] = (float*) malloc(sizeof(float) * m_numberOfChildNodes);
		}

		m_biasValues = (float*) malloc(sizeof(float) * m_numberOfChildNodes);
		m_biasWeights = (float*) malloc(sizeof(float) * m_numberOfChildNodes);
	} else {
		m_weights = NULL;
		m_biasValues = NULL;
		m_biasWeights = NULL;
	}

	// Make sure everything contains zeros
	for(int i = 0; i < m_numberOfNodes; i++) {
		m_neuronValues[i] = 0;
		m_desiredValues[i] = 0;
		m_errors[i] = 0;
		
		if (m_childLayer != NULL) {
			for (int j = 0; j < m_numberOfChildNodes; j++) {
				m_weights[i][j] = 0;
				m_weightChanges[i][j] = 0;
			}
		}
	}

	if (m_childLayer != NULL) {
		for (int j = 0; j < m_numberOfChildNodes; j++) {
			m_biasValues[j] = -1;
			m_biasWeights[j] = 0;
		}
	}
}

void NeuralNetworkLayer::CleanUp(void)
{
	int	i;

	free(m_neuronValues);
	free(m_desiredValues);
	free(m_errors);
	
	if(m_weights != NULL) {
		for(i = 0; i<m_numberOfNodes; i++) {
			free(m_weights[i]);
			free(m_weightChanges[i]);
		}
		free(m_weights);
		free(m_weightChanges);
	}

	if(m_biasValues != NULL) 
		free(m_biasValues);
	if(m_biasWeights != NULL) 
		free(m_biasWeights);
}

void NeuralNetworkLayer::RandomizeWeights(void)
{
	int	min = 0;
	int	max = 200;
	int	number;

	srand( (unsigned)time( NULL ) );

	for(int i = 0; i < m_numberOfNodes; i++) {
		for(int j = 0; j < m_numberOfChildNodes; j++) {	
			number = (((abs(rand()) % (max - min + 1)) + min));    
			if(number > max)
				number = max;
			if(number < min)
    			number = min;
			m_weights[i][j] = number / 100.0f - 1;
		}
	}
	
	for(int j = 0; j < m_numberOfChildNodes; j++) {
		number = (((abs(rand()) % (max - min + 1)) + min));    
		if(number > max)
			number = max;
		if(number < min)
    		number = min;
		m_biasWeights[j] = number / 100.0f - 1;		
	}
}

void NeuralNetworkLayer::CalculateErrors(void)
{
	float	sum = 0.0;
	// èoóÕëw(output layer)
	if(m_childLayer == NULL) { 
		for(int i=0; i<m_numberOfNodes; i++){
			m_errors[i] = (m_desiredValues[i] - m_neuronValues[i]) * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	} // ì¸óÕëw(input layer)
	else if(m_parentLayer == NULL) { 
		for(int i=0; i<m_numberOfNodes; i++) {
			m_errors[i] = 0.0f;
		}
	} // âBÇÍëw(hidden layer)
	else { 
		for(int i=0; i<m_numberOfNodes; i++) {
			sum = 0;
			for(int j=0; j<m_numberOfChildNodes; j++){
				sum += m_childLayer->m_errors[j] * m_weights[i][j];
			}
			m_errors[i] = sum * m_neuronValues[i] * (1.0f - m_neuronValues[i]);
		}
	}
}

void NeuralNetworkLayer::AdjustWeights(void)
{
	float	dw = 0.0;
	if(m_childLayer != NULL) {
		for(int i = 0; i < m_numberOfNodes; i++){
			for(int j = 0; j < m_numberOfChildNodes; j++){
				dw = m_learningRate * m_childLayer->m_errors[j] * m_neuronValues[i];
				m_weights[i][j] += dw + m_momentumFactor * m_weightChanges[i][j];			
				m_weightChanges[i][j] = dw;
			}
		}

		for(int j = 0; j < m_numberOfChildNodes; j++){
			m_biasWeights[j] += m_learningRate * m_childLayer->m_errors[j] * m_biasValues[j];
		}
	}
}

void NeuralNetworkLayer::CalculateNeuronValues(void)
{
	float	x;
	if(m_parentLayer != NULL) {
		for(int j = 0; j < m_numberOfNodes; j++) {
			x = 0;
			for(int i = 0; i < m_numberOfParentNodes; i++) {
				x += m_parentLayer->m_neuronValues[i] * m_parentLayer->m_weights[i][j];
			}			
			x += m_parentLayer->m_biasValues[j] * m_parentLayer->m_biasWeights[j];
			
			if((m_childLayer == NULL) && m_linearOutput)
				m_neuronValues[j] = x;
			else
				m_neuronValues[j] = 1.0f / (1.0f + (float)exp(-x));	
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetwork Class
/////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
{
	m_inputLayer.m_numberOfNodes = nNodesInput;
	m_inputLayer.m_numberOfChildNodes = nNodesHidden;
	m_inputLayer.m_numberOfParentNodes = 0;	
	m_inputLayer.Initialize(nNodesInput, NULL, &m_hiddenLayer);
	m_inputLayer.RandomizeWeights();
	m_hiddenLayer.m_numberOfNodes = nNodesHidden;
	m_hiddenLayer.m_numberOfChildNodes = nNodesOutput;
	m_hiddenLayer.m_numberOfParentNodes = nNodesInput;		
	m_hiddenLayer.Initialize(nNodesHidden, &m_inputLayer, &m_outputLayer);
	m_hiddenLayer.RandomizeWeights();
	
	m_outputLayer.m_numberOfNodes = nNodesOutput;
	m_outputLayer.m_numberOfChildNodes = 0;
	m_outputLayer.m_numberOfParentNodes = nNodesHidden;		
	m_outputLayer.Initialize(nNodesOutput, &m_hiddenLayer, NULL);	
}

void NeuralNetwork::CleanUp()
{
	m_inputLayer.CleanUp();
	m_hiddenLayer.CleanUp();
	m_outputLayer.CleanUp();
}

void	NeuralNetwork::SetInput(int i, float value)
{
	if((i >= 0) && (i < m_inputLayer.m_numberOfNodes)) {
		m_inputLayer.m_neuronValues[i] = value;
	}
}

float	NeuralNetwork::GetOutput(int i)
{
	if((i >= 0) && (i < m_outputLayer.m_numberOfNodes)) {
		return m_outputLayer.m_neuronValues[i];
	}
	return (float) INT_MAX; // to indicate an error
}

void NeuralNetwork::SetDesiredOutput(int i, float value)
{
	if((i >= 0) && (i < m_outputLayer.m_numberOfNodes)) {
		m_outputLayer.m_desiredValues[i] = value;
	}
}

void NeuralNetwork::FeedForward(void)
{
	m_inputLayer. CalculateNeuronValues();
	m_hiddenLayer.CalculateNeuronValues();
	m_outputLayer.CalculateNeuronValues();
}

void NeuralNetwork::BackPropagate(void)
{
	m_outputLayer.CalculateErrors();
	m_hiddenLayer.CalculateErrors();

	m_hiddenLayer.AdjustWeights();
	m_inputLayer.AdjustWeights();
}

int	NeuralNetwork::GetMaxOutputID(void)
{
	float maxval = m_outputLayer.m_neuronValues[0];
	int id = 0;

	for(int i = 1; i < m_outputLayer.m_numberOfNodes; i++) {
		if(m_outputLayer.m_neuronValues[i] > maxval) {
			maxval = m_outputLayer.m_neuronValues[i];
			id = i;
		}
	}
	return id;
}

float NeuralNetwork::CalculateError(void)
{
	float	error = 0.0;

	for(int i = 0; i < m_outputLayer.m_numberOfNodes; i++) {
		error += (float)pow(m_outputLayer.m_neuronValues[i] - m_outputLayer.m_desiredValues[i], 2);
	}
	error = error / m_outputLayer.m_numberOfNodes;
	return error;
}

void NeuralNetwork::SetLearningRate(float rate)
{
	m_inputLayer.m_learningRate = rate;
	m_hiddenLayer.m_learningRate = rate;
	m_outputLayer.m_learningRate = rate;
} 

void NeuralNetwork::SetLinearOutput(bool useLinear)
{
	m_inputLayer.m_linearOutput = useLinear;
	m_hiddenLayer.m_linearOutput = useLinear;
	m_outputLayer.m_linearOutput = useLinear;
}

void NeuralNetwork::SetMomentum(bool useMomentum, float factor)
{
	m_inputLayer.m_useMomentum = useMomentum;
	m_hiddenLayer.m_useMomentum = useMomentum;
	m_outputLayer.m_useMomentum = useMomentum;

	m_inputLayer.m_momentumFactor = factor;
	m_hiddenLayer.m_momentumFactor = factor;
	m_outputLayer.m_momentumFactor = factor;
}

void NeuralNetwork::DumpData(char* filename)
{
	FILE*	f;

	f = fopen(filename, "w");
	
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Input Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for(int i=0; i<m_inputLayer.m_numberOfNodes; i++)		
		fprintf(f, "(%d) = %f\n", i, m_inputLayer.m_neuronValues[i]);
	fprintf(f, "\n");
	fprintf(f, "m_weights:\n");
	fprintf(f, "\n");
	for(int i=0; i<m_inputLayer.m_numberOfNodes; i++)
		for(int j=0; j<m_inputLayer.m_numberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, m_inputLayer.m_weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias m_weights:\n");
	fprintf(f, "\n");
	for(int j=0; j<m_inputLayer.m_numberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, m_inputLayer.m_biasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Hidden Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "m_weights:\n");
	fprintf(f, "\n");
	for(int i=0; i<m_hiddenLayer.m_numberOfNodes; i++)
		for(int j=0; j<m_hiddenLayer.m_numberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, m_hiddenLayer.m_weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias m_weights:\n");
	fprintf(f, "\n");
	for(int j=0; j<m_hiddenLayer.m_numberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, m_hiddenLayer.m_biasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Output Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for(int i=0; i<m_outputLayer.m_numberOfNodes; i++)		
		fprintf(f, "(%d) = %f\n", i, m_outputLayer.m_neuronValues[i]);
	fprintf(f, "\n");

	fclose(f);
}