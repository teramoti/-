#ifndef MYNEURALNETWORKHEADER
#define MYNEURALNETWORKHEADER

class NeuralNetworkLayer
{
public:
	int			m_numberOfNodes;
	int			m_numberOfChildNodes;
	int			m_numberOfParentNodes;
	float**	    m_weights;
	float**  	m_weightChanges;
	float*		m_neuronValues;
	float*		m_desiredValues;
	float*		m_errors;
	float*		m_biasWeights;
	float*		m_biasValues;
	float		m_learningRate;

	bool		m_linearOutput;
	bool		m_useMomentum;
	float		m_momentumFactor;

	NeuralNetworkLayer*		m_parentLayer;
	NeuralNetworkLayer*		m_childLayer;

	NeuralNetworkLayer();

	void	Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child);
	void	CleanUp(void);
	void	RandomizeWeights(void);
	void	CalculateErrors(void);
	void	AdjustWeights(void);	
	void	CalculateNeuronValues(void);
	
};

// Implements a 3-Layer neural network with one input layer, one hidden layer, and one output layer
class NeuralNetwork 
{
public:
	NeuralNetworkLayer	m_inputLayer;
	NeuralNetworkLayer	m_hiddenLayer;
	NeuralNetworkLayer	m_outputLayer;

	void	Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
	void	CleanUp();
	void	SetInput(int i, float value);
	float	GetOutput(int i);
	void	SetDesiredOutput(int i, float value);
	void	FeedForward(void);
	void	BackPropagate(void);
	int		GetMaxOutputID(void);
	float	CalculateError(void);
	void	SetLearningRate(float rate);
	void	SetLinearOutput(bool useLinear);
	void	SetMomentum(bool useMomentum, float factor);
	void	DumpData(char* filename);


};

#endif