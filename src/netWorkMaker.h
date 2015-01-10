/* =====================================================================================
￼* Filename:  netWorkMaker.h
￼*
￼* Description: 建立一个可用于预测的神经网络
￼*
￼* Version:   1.0
￼* Created:   2015-01-02 14:29:52
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

#ifndef NETWORKMAKER_H
#define NETWORKMAKER_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include "data.h"
#include "neureNetwork.h"
#include "neureFunction.h"
#include "fileProcesser.h"

using namespace std;

class NetworkMaker {
public:
	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  work
	 * @argu: filepath 训练文件路径
	 * @argu: testFile 测试文件路径
	 *
	 *  Description: 根据训练文件与预测文件进行训练与判断
	 * ===================================================================================== 
	 */
	void work(const string &filepath, const string &testFile) {
		Data d;
		vector< vector<int> > data = d.getData(filepath);
		buildNet();
		train(data, testFile);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  buildNet
	 *  Description: 根据训练数据规模建立对应的神经网络
	 * ===================================================================================== 
	 */
	void buildNet() {
		vector< int > layerNum;
		layerNum.push_back(64);
		layerNum.push_back(32);
		layerNum.push_back(10);

		neureNetwork.create(3, layerNum);
		neureNetwork.init();
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  train
	 *  Description: 神经网络的训练，每训练 10 次进行一次预测，并输出预测结果
	 * ===================================================================================== 
	 */
	void train(vector< vector<int> > &data, const string &testFile) {
		for (int i = 0; i != 1000; ++i) {
			cout << "The " << i << " training" << endl;
			// 训练神经网络
			for (auto &d : data) {
				vector< double > input;
				vector< double > rightOutput;
				rightOutput.resize(10, 0.0);

				for(int k = 0; k < d.size() - 1; ++k) {
					input.push_back((double)(d[k]));
				}

				rightOutput[(double)(d[d.size() - 1])] = 1.0;

				train(input, rightOutput);
			}
			if (i % 10 == 0) {
				//double rate = neureNetwork.getLearningRate() - 0.001;
				//rate = rate >= 0.1 ? rate : 0.1;
				//neureNetwork.setLearningRate(rate);
				vector< double > errorAndPrecision = predit(data);
				writeOut(errorAndPrecision);

				if(errorAndPrecision[1] <= 0.1) {
					break;
				}
			}
		}
		cout << "Training end, testing..." << endl;
		test(testFile);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  test
	 *  Description: 使用测试数据进行结果测试
	 * ===================================================================================== 
	 */
	void test(const string &testFile) {
		Data d;
		vector< vector<int> > data = d.getData(testFile);
		vector< vector< double > > preditResult;
		vector< int > rightResult;
		for (auto &i : data) {
			vector< double > input;
	
			for(int k = 0; k < i.size() - 1; ++k)
				input.push_back((double)i[k]);

			rightResult.push_back(i[i.size() - 1]);

			for(auto &j : input) {
				j = (double)j / 300.0;
			}

			vector< double > output;
			neureNetwork.forwardCaculate(input, output);
			preditResult.push_back(output);
		}
		cout << "Precision of test data: " << fun.precision(preditResult, rightResult) << endl;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getTrainData
	 *  Description: 从训练文件选取十分之一作为训练数据【循环选取】
	 * ===================================================================================== 
	 */
	vector< vector< int > > getTrainData(vector< vector<int> > &data, int times) {
		int begin = (data.size() / 4) * ((times + rand()) % 4);
		vector< vector< int > > result;
		for (int i = begin; i < begin + (data.size() / 4) && i < data.size(); ++i) {
	    	result.push_back(data[i]);
		}
		return result;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  train
	 *  Description: 单次神经网络的训练
	 * ===================================================================================== 
	 */
	void train(vector< double > &input, vector< double > &rightOutput) {
		for(auto &i : input) {
			i = (double)i / 300.0;
		}

		vector< double > output;
		neureNetwork.forwardCaculate(input, output);
		neureNetwork.backPropagate(output, rightOutput);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  predit
	 *  Description: 数据预测测试
	 * ===================================================================================== 
	 */
	vector< double > predit(vector< vector< int > > &data) {
		vector< vector< double > > preditResult;
		vector< int > rightResult;
		for (auto &i : data) {
			vector< double > input;
	
			for(int k = 0; k < i.size() - 1; ++k)
				input.push_back((double)i[k] / 300.0);

			rightResult.push_back(i[i.size() - 1]);

			vector< double > output;
			neureNetwork.forwardCaculate(input, output);
			preditResult.push_back(output);
		}
		vector< double > errorAndPrecision;
		errorAndPrecision.push_back(fun.precision(preditResult, rightResult));
		errorAndPrecision.push_back(fun.squaredError(preditResult, rightResult));

		return errorAndPrecision;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  writeOut
	 *  Description: 将结果写到文件
	 * ===================================================================================== 
	 */
	void writeOut(vector< double > &errorAndPrecision) {
		file.writeToFileWithModeAdd("result/error.data", errorAndPrecision[1]);
		file.writeToFileWithModeAdd("result/precision.data", errorAndPrecision[0]);
	}

private:
	NeureNetwork neureNetwork;
	NeureFunction fun;
	FileProcesser file;
};

#endif