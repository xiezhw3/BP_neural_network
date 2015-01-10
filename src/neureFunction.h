/* ===============================================================================
￼* Filename:  neureFunction.h
￼*
￼* Description: 根据输入连接的数值和权值计算神经元节点的输出函数
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:35:02
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

#ifndef NEUREFUNCTION_H
#define NEUREFUNCTION_H

#include <iostream>
#include <vector>
#include <cmath>
#include "connection.h"

using namespace std;

#define C 0
#define A 1

class NeureFunction {
public:
	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  calFunction
	 *  Description: 根据神经元节点所属层类型调用不同的函数计算节点的输出值
	 * ===================================================================================== 
	 */
	double calFunction(vector< Connection > &connection, int type, double threshold) {
		vector< double > outputMatrix;
		vector< double > weightMatrix;
		for (auto &i : connection) {
			weightMatrix.push_back(i.getWeight());
			outputMatrix.push_back(i.getSourceNeureOutput());
		}
		if (type == 0)
			return tanhFunction(outputMatrix, weightMatrix, threshold);

		return sigmoidFunction(outputMatrix, weightMatrix, threshold);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  tanhFunction
	 *  Description: 双曲正切函数计算神经元节点的输出值，用于非隐层节点的计算
	 * ===================================================================================== 
	 */
	double tanhFunction(vector< double > &X, vector< double > &W, double threshold) {
		double result = netActivation(X, W) - threshold;
		return tanhh(result);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  sigmoidFunction
	 *  Description: sigmoid函数计算神经元节点的输出值，用于隐层节点的计算
	 * ===================================================================================== 
	 */
	double sigmoidFunction(vector< double > &X, vector< double > &W, double threshold) {
		double result = netActivation(X, W) - threshold;
		return sigmoid(result);
	}

	double tanhh(double x) {
		 if (x < -10.0)
		 	return -1.0;
    	else if (x > 10.0)
    		return 1.0;
    	return tanh(x);
	}

	double sigmoid(double x) {
		if (x < -45.0)
			return 0.0;
    	else if (x > 45.0)
    		return 1.0;
		return (1.0 / (1 + exp(-A * x)));
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  sigmoidFunction
	 *  Description: 计算净激活 net
	 * ===================================================================================== 
	 */
	double netActivation(vector< double > &X, vector< double > &W) {
		double result = 0;
		size_t size = X.size();
		for (int i = 0; i != size; ++i) {
			result += X[i] * W[i];
		}
		return result;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  dTanhFunction
	 *  Description: tanh(x)的微积分倒数
	 * ===================================================================================== 
	 */
	double dTanhFunction(double x) {
		return (1 - tanh(x)) * (1 - tanh(x));
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  dSigmoidFunction
	 *  Description: sigmoid(x)的微积分倒数
	 * ===================================================================================== 
	 */
	double dSigmoidFunction(double x) {
		return sigmoid(x) * (1 - sigmoid(x));
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  squaredError
	 *  Description: 计算平方误差
	 * ===================================================================================== 
	 */
	double squaredError(vector< vector< double > > &output, vector< int > &right) {
		double result = 0.0;
		int index = 0;
		for (auto &predit : output) {
			int num = right[index++];
			for (int i = 0; i != predit.size(); ++i) {
				if (i == num)
					result += square(predit[i] - 1.0);
				else
					result += square(predit[i] - 0.0);
			}
		}
		return result / (2.0 * output.size());
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  square
	 *  Description: 计算平方
	 * ===================================================================================== 
	 */
	double square(double x) {
		return x * x;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  precision
	 *  Description: 计算准确率
	 * ===================================================================================== 
	 */
	 double precision(vector< vector< double > >  &output, vector< int > &right) {
	 	vector< int > predit;
	 	for (auto &da : output) {
	 		double v = 0.0;
			int index = 0;
			for (int m = 0; m != da.size(); m++) {
				if (da[m] > v) {
					v = da[m];
					index = m;
				}
			}
			predit.push_back(index);
	 	}
	 	
	 	int rightNum = 0;
	 	for (int i = 0; i != predit.size(); ++i)
	 		if (predit[i] == right[i])
	 			rightNum++;
	 	return (double)rightNum / (double)(predit.size());
	 }

private:
};

#endif