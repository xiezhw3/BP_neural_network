/* =====================================================================================
￼* Filename:  testData.cpp
￼*
￼* Description: 训练文件特征判断
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 17:11:32
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
#include <string>
#include <vector>
#include "../src/fileProcesser.h"
#include <sstream>

using namespace std;

/*  
 * ===  FUNCTION  ====================================================================== 
 *         Name:  getData
 *  Description: 取得训练数据
 * ===================================================================================== 
 */
vector< vector <int> > getData(const string &filePath) {
	FileProcesser fileProcessor;
	vector<string> dataString = fileProcessor.readFile(filePath);
	vector< vector <int> > data;
	for (auto &line : dataString) {
		stringstream ss(line);
		string temp;
		int num;
		vector <int> dataLine;
		while (getline(ss, temp, ',')) {
			istringstream snum(temp);
			snum >> num;
			dataLine.push_back(num);
		}
		data.push_back(dataLine);
	}
	return data;
}

/*  
 * ===  FUNCTION  ====================================================================== 
 *         Name:  getDataFeature 
 *  Description: 判断训练数据的特征
 * ===================================================================================== 
 */
 void getDataFeature(const string &filePath) {
 	vector< vector <int> > data = getData(filePath);
 	for (auto &line : data)
 		cout << line.size() << endl;
 }


int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Input with form [./test] [file path]" << endl;
		exit(1);
	}

	cout << "--------------- The feature of each test data ----------------" << endl;
	getDataFeature(argv[1]);

	return 0;
}