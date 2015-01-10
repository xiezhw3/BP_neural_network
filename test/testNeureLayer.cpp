/* =====================================================================================
￼* Filename:  testNeureLayer.cpp
￼*
￼* Description: 测试 neureLayer.h 的正确性
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 22:07:58
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

using namespace std;

int main(int argc, char const *argv[])
{
	NeureLayer layer(12, 0);
	vector< Neure > n = layer.getNeures();
	cout << "Right: 12" << endl;
	cout << n.size() << endl;
	layer.createLayer(100, 1);
	n = layer.getNeures();
	cout << "Right: 100" << endl;
	cout << n.size() << endl;

	cout << "Right: 1" << endl;
	cout << layer.getNeureType() << endl;

	return 0;
}