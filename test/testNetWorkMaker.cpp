/* =====================================================================================
￼* Filename:  testNetWorkMaker.cpp
￼*
￼* Description: 神经网络建立的测试
￼*
￼* Version:   1.0
￼* Created:   2015-01-02 15:54:29
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
#include "../src/netWorkMaker.h"

using namespace std;

int main(int argc, char const *argv[])
{
	NetworkMaker net;
	net.work("digitstra.txt", "digitstest.txt");
	return 0;
}