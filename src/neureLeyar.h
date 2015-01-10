/* =====================================================================================
￼* Filename:  neureLayer.h
￼*
￼* Description: 神经元网络层的基本结构
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:49:02
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

#ifndef NEURELAYER_H
#define NEURELAYER_H

#include <vector>
#include <memory>
#include "neure.h"
#include "neureFunction.h"

class NeureLayer {
public:
	NeureLayer(int neureNum = 0, int type = 0) : neureType(type) {
		neures.clear();
		for (int i = 0; i != neureNum; ++i) {
			neures.push_back(Neure(neureType));
		}
	}
	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  addNeure
	 *  Description: 往神经元层增加神经元节点
	 * ===================================================================================== 
	 */
	void addNeure(Neure &neure_) {
		neures.push_back(neure_);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setPreLayer
	 *  Description: 设置神经元层的前向神经元层
	 * ===================================================================================== 
	 */
	void setPreLayer(shared_ptr< NeureLayer > &preLayer_) {
		preLayer = preLayer_;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getNeures
	 *  Description: 返回神经元层元素
	 * ===================================================================================== 
	 */
	vector< Neure > &getNeures() {
		return neures;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getNeures
	 *  Description: 返回神经元层节点类型
	 * ===================================================================================== 
	 */
	int getNeureType() const {
		return neureType;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setNeuresConnectionWeightInit
	 *  Description: 初始化层内节点连接的权值
	 * ===================================================================================== 
	 */
	void setNeuresConnectionWeightInit(int size) {
		for (auto &n : neures)
			n.setConnectionWeight(size);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setNeuresConnectionWeight
	 *  Description: 设置层内节点连接的值
	 * ===================================================================================== 
	 */
	void setLayerConnectionValue(vector< double > &value) {
		for (auto &n : neures)
			n.setConnectionValue(value);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setNeuresOutput
	 *  Description: 设置层内节点的值
	 * ===================================================================================== 
	 */
	void setNeuresOutput(vector< double > &input_) {
		size_t size = input_.size();
		if (size != neures.size())
			return;

		for (size_t i = 0; i != size; ++i)
			neures[i].setOutput(input_[i]);
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  backPropagate
	 *  @argu: dError 后一层误差
	 *  @argu: pError 前一层误差
	 *  @argu: learningRate 学习率
	 *  Description: 后一层向前一层传播误差算法
	 * ===================================================================================== 
	 */
	void backPropagate(vector< double > &dError, vector< double > &pError, double learningRate) {
		vector< double > dErrorDyn;
		vector< Connection > con;

		//  当前层节点误差
		for (auto &i : dError) {
			double in = 0.0;
			for (auto &n : neures) {
				con = n.getConnection();
				for (auto &c : con) {
					in += c.getWeight() * c.getSourceNeureOutput();
				}
			}
			if (neures[0].getLayerType() == 0) {
				dErrorDyn.push_back(nFunction.dTanhFunction(in) * i);
			} else {
				dErrorDyn.push_back(nFunction.dSigmoidFunction(in) * i);
			}
		}

		// 下一层误差，作为微积分函数的导数的参数
		for (int i = 0; i != pError.size(); ++i) {
			int index = 0;
			for (auto &n : neures) {
				con = n.getConnection();
				pError[i] += (con[i].getWeight() * dErrorDyn[index++]);
			}
		}

		// 权值调整
		int errorIndex = 0;
		for (auto &n : neures) {
			con = n.getConnection();
			vector< double > weight(con.size());
			int index = 0;
			for (auto &c : con) {
				weight[index++] = c.getWeight() - learningRate * c.getSourceNeureOutput() * dErrorDyn[errorIndex];
			}
			errorIndex++;
			n.setConnectionWeight(weight);
		}
	}

private:
	vector< Neure > neures;
	shared_ptr< NeureLayer > preLayer;
	NeureFunction nFunction;
	int neureType;
};

#endif