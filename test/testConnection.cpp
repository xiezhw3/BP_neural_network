/* ===============================================================================
￼* Filename:  testConnection.cpp
￼*
￼* Description: 测试 connection.h 的正确性
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 21:29:01
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
#include "../src/connection.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Connection connection(3, 2);
	cout << "Right: 2" << endl;
	cout << connection.getWeight() << endl;
	cout << "Right: 3" << endl;
	cout << connection.getSourceNeureOutput() << endl;
	connection.setWeight(12);
	cout << "Right: 12" << endl;
	cout << connection.getWeight() << endl;



	return 0;
}