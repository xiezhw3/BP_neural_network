/* =====================================================================================
￼* Filename:  testNetwork.cpp
￼*
￼* Description: 测试 neureNetwork.h 的正确性
￼*
￼* Version:   1.0
￼* Created:   2015-01-01 14:23:16
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

#include <iostream>
#include "../src/neureLeyar.h"
#include "../src/neure.h"
#include "../src/connection.h"
#include "../src/neureNetwork.h"

using namespace std;

int main(int argc, char const *argv[])
{
	NeureNetwork network;
	vector< int > layerNum{64, 300, 10};
	network.create(3, layerNum);
	network.init();

	vector< double > input{0,1,6,15,12,1,0,0,0,7,16,6,6,10,0,0,0,8,16,2,0,11,2,0,0,5,16,3,0,5,7,0,0,7,13,3,0,8,7,0,0,4,12,0,1,13,5,0,0,0,14,9,15,9,0,0,0,0,6,14,7,1,0,0};
	vector< double > output;
	vector< double > need{1, 0, 0,0,0,0,0,0,0,0};
	for (auto &i : input)
		i = (double)i / 16.0;

	network.forwardCaculate(input, output);
	for (int i = 0; i != 3000; ++i) {
		network.backPropagate(output, need);
		network.forwardCaculate(input, output);
	}

	network.forwardCaculate(input, output);
	for (auto &i : output)
		cout << i << ' ';
	cout << endl;

	return 0;
}