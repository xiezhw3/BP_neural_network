/* =====================================================================================
￼* Filename:  neureNetwork.h
￼*
￼* Description: 神经元网络基本结构及各种功能函数
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:59:03
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

#ifndef NEURENETWORK_H
#define NEURENETWORK_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include "neureLeyar.h"
#include "neure.h"
#include "neureFunction.h"

class NeureNetwork {
public:
	NeureNetwork() : learnRate(0.5) { }

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  init
	 *  Description: 初始化网络，包括设置一些初始值等
	 * ===================================================================================== 
	 */
	void init() {
		int type = 0;

		for (int i = 0; i != layerNum; ++i) {
			if (i > 0 && i < (layerNum - 1)) {
				type = 1;
			} else {
				type = 0;
			}

			if (i == 0) {
				layers.push_back(shared_ptr< NeureLayer >(new NeureLayer(layerNeureNum[i], type)));
			} else {
				layers.push_back(createLayer(layerNeureNum[i], type, layerNeureNum[i - 1]));
			}
		}
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  create
	 *  Description: 建立一个神经元网络
	 * ===================================================================================== 
	 */
	void create(int layerNum_, vector< int > &layerNeureNum_) {
		layerNum = layerNum_;
		layerNeureNum = layerNeureNum_;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  createLayer
	 *  Description: 建立一个神经元网络层
	 * ===================================================================================== 
	 */
	shared_ptr< NeureLayer > createLayer(int neureNum, int type, int preLayerNode) {
		shared_ptr< NeureLayer > layer =
						shared_ptr< NeureLayer >(new NeureLayer(neureNum, type));
		layer->setNeuresConnectionWeightInit(preLayerNode);
		return layer;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  forwardCaculate
	 *  Description: 前向传播算法
	 * ===================================================================================== 
	 */
	void forwardCaculate(vector< double > &input_, vector< double > &output_) {
		output_.clear();
		int layerNumTemp = 0;
		while (layerNumTemp < layerNum) {
			if (layerNumTemp == 0) {
				layers[layerNumTemp]->setNeuresOutput(input_);
			} else {
				vector< double > connectionValue;
				for (auto &preLayerNode : layers[layerNumTemp - 1]->getNeures()) {
					connectionValue.push_back(preLayerNode.getOutput());
				}
				layers[layerNumTemp]->setLayerConnectionValue(connectionValue);
			}
			layerNumTemp++;
		}

		for (auto &preLayerNode : layers[layerNumTemp - 1]->getNeures()) {
			output_.push_back(preLayerNode.getOutput());
		}
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  backPropagate
	 *  @argu: tRect 计算结果
	 *  @argu: oRect 期望结果
	 *  Description: 后向传播算法
	 * ===================================================================================== 
	 */
	void backPropagate(vector< double > &tRect, vector< double > &oRect) {
		vector< vector< double > > layerError(layerNum);
		size_t size = tRect.size();

		// 输出层的误差，作为微积分函数倒数的输入
		for (int i = 0; i != size; ++i)
			layerError[layerNum - 1].push_back(tRect[i] - oRect[i]);

		// 其它层的误差先设为 0
		for (int i = layerNum - 2; i >= 0; --i) {
			layerError[i].resize(layerNeureNum[i], 0.0);
		}

		// 逐层向后传递
		for (int i = layerNum - 1; i > 0; --i) {
			layers[i]->backPropagate(layerError[i], layerError[i - 1], this->learnRate);
		}
		layerError.clear();
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setLearningRate
	 *  Description: 设置学习率
	 * ===================================================================================== 
	 */
	void setLearningRate(double rate) {
		learnRate = rate;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getLearningRate
	 *  Description: 返回学习率
	 * ===================================================================================== 
	 */
	double getLearningRate() const {
		return learnRate;
	}


private:
	int layerNum;
	vector< int > layerNeureNum;
	vector< shared_ptr< NeureLayer > > layers;
	int iterNum;
	double learnRate;
	NeureFunction nFunction;
};

#endif