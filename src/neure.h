/* =====================================================================================
￼* Filename:  neure.h
￼*
￼* Description: 神经元的基本结构
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:15:26
￼* Revision:  none
￼* Compiler:  g++
￼*
￼* Author:	Zhiwang Xie
 * Mail: 	xiezhw3@gmail.com
 * Github:  https://www.github/xiezhw3
￼* Organization:
￼*
￼* =====================================================================================
 */

#ifndef NEURE_H
#define NEURE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "neureFunction.h"
#include "connection.h"
#include "neureLeyar.h"

using namespace std;

class NeureLayer;

class Neure {
public:
	Neure(int type = 0) : layerType(type), output(0), outputSeted(false) {
		threshold = 0.01 * (rand() % 3 + 3);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  calOutput
	 *  Description: 根据神经网络层的类型(是否隐层) 和连接节点的输入来计算该节点的输出
	 * ===================================================================================== 
	 */
	void calOutput() {
		outputSeted = true;
		output = function.calFunction(connection, layerType, threshold);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setLayerType
	 *  Description: 为神经元节点所在层的类型
	 * ===================================================================================== 
	 */
	void setLayerType(int type) {
		outputSeted = false;
		layerType = type;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setConnectionWeight
	 *  Description: 为神经元节点所在层的所有节点设置连接权值
	 * ===================================================================================== 
	 */
	 void setConnectionWeight(vector< double > &weight) {
	 	outputSeted = false;
	 	size_t size = weight.size();
 		for (int i = 0; i != size; ++i)
 			connection[i].setWeight(weight[i]);
	 }

	 /*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setConnectionWeight
	 *  Description: 为神经元节点所在层的所有节点设置连接权值，用于初始化节点
	 * ===================================================================================== 
	 */
	 void setConnectionWeight(int size) {
 		for (int i = 0; i != size; ++i)
 			connection.push_back(Connection(0, 0.05 * rand() / RAND_MAX));
	 }

	 /*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setConnectionValue
	 *  Description: 为神经元节点所在层的所有节点设置连接输入值
	 * ===================================================================================== 
	 */
	 void setConnectionValue(vector< double > &connectionValue) {
	 	outputSeted = false;
	 	int index = 0;
	 	for (auto &n : connectionValue) {
	 		connection[index++].setSourceNeureOutput(n);
	 	}
	 }

	 /*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setOutput
	 *  Description: 设置节点值
	 * ===================================================================================== 
	 */
	 void setOutput(double output_) {
	 	outputSeted = true;
	 	output = output_;	
	 }

	 /*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getOutput
	 *  Description: 取得神经元节点的输出
	 * ===================================================================================== 
	 */
	double getOutput() {
		if (!outputSeted)
			calOutput();
		return output;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getConnection
	 *  Description: 取得神经元节点的连接
	 * ===================================================================================== 
	 */
	vector< Connection > &getConnection() {
		return connection;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getLayerType
	 *  Description: 取得神经元节点的类型
	 * ===================================================================================== 
	 */
	int getLayerType() const {
		return layerType;
	}


	/* ===  FUNCTION  ====================================================================== 
	 *         Name:  getThreshold
	 *  Description: 返回阈值
	 * ===================================================================================== 
	 */
	double getThreshold() const {
		return threshold;
	}

private:
	NeureFunction function;
	vector< Connection > connection;
	double output;
	bool outputSeted;
	int layerType;
	double threshold;
};

#endif
