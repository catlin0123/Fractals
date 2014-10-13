#pragma once
#include "Structs.h"

class GenWindow
{
public:
	GenWindow();
	~GenWindow();

	//Members
	vector<TransformMatrix> Transforms;

	//Functions
	void Init();
};

