/* ===============================================================================
￼* Filename:  connection.h
￼*
￼* Description: 神经元之间的连接
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:35:44
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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include <vector>

using namespace std;

class Connection {
public:
	Connection(double s = 0, double w = 0) :
		sourceNeureOutput(s), weight(w) { }

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setWeight
	 *  Description: 设置源神经元节点传递到目标神经元节点的权值
	 * ===================================================================================== 
	 */
	void setWeight(double weight_) {
		weight = weight_;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  setSourceNeureOutput
	 *  Description: 设置源神经元节点传递到目标神经元节点的权值
	 * ===================================================================================== 
	 */
	void setSourceNeureOutput(double source) {
		sourceNeureOutput = source;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getWeight
	 *  Description: 取得源神经元节点传递到目标神经元节点的权值
	 * ===================================================================================== 
	 */
	double getWeight() const {
		return weight;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getSourceNeureOutput
	 *  Description: 取得源神经元节点传递到目标神经元节点的原输出值
	 * ===================================================================================== 
	 */
	double getSourceNeureOutput() const {
		return sourceNeureOutput;
	}

private:
	double weight;
	double sourceNeureOutput;
};

#endif
