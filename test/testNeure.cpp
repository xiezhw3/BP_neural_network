/* ===============================================================================
￼* Filename:  testNeure.cpp
￼*
￼* Description: 测试 neure.h 的正确性
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 21:56:11
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
#include <vector>
#include "../src/neure.h"
#include "../src/connection.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Neure neure(1);
	Connection c1(1, 0.2);
	Connection c2(1, 0.2);
	Connection c3(1, 0.2);
	Connection c4(2, 0.2);
	Connection c5(3, 0.2);
	neure.addConnection(c1);
	neure.addConnection(c2);
	neure.addConnection(c3);
	neure.addConnection(c4);
	neure.addConnection(c5);

	cout << "Right: 0.83" << endl;
	cout << neure.getOutput() << endl;
	neure.setLayerType(0);
	cout << "Right: 1.6" << endl;
	cout << neure.getOutput() << endl;

	return 0;
}