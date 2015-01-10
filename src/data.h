/* =====================================================================================
￼* Filename:  data.h
￼*
￼* Description: 取得数据文件的数据内容
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:15:41
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
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "fileProcesser.h"

using namespace std;

class Data {
public:
	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getDataStringFromFile
	 *  Description: 从文件将数据以字符串的形式读取出来
	 * ===================================================================================== 
	 */
	vector<string> getDataStringFromFile(const string &filepath) {
		vector<string> dataString = fileProcesser.readFile(filepath);
		return dataString;
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getDataFromString
	 *  Description: 将字符串形式的数字提取出来并保存
	 * ===================================================================================== 
	 */
	void getDataFromString(const string &filepath) {
		vector<string> dataString = getDataStringFromFile(filepath);

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
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  getData
	 *  Description: 以 vector 的形式返回数字
	 * ===================================================================================== 
	 */
	vector< vector<int> > &getData(const string &filepath) {
		getDataFromString(filepath);
		return data;
	}

private:
	vector< vector<int> > data;
	FileProcesser fileProcesser;
};

#endif