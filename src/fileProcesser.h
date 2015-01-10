/* =====================================================================================
￼* Filename:  fileProcesser.h
￼*
￼* Description: 文件读取处理
￼*
￼* Version:   1.0
￼* Created:   2014-12-31 19:15:32
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

#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class FileProcesser {
public:
	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  writeToFile 
	 *  Description: 写文件操作
	 * ===================================================================================== 
	 */
	void writeToFile(const string &filePath, vector<string> &result) {
		ofstream out(filePath);
		if (!out.is_open()){ 
			cout << "Error opening file" << endl; 
			exit (1); 
		}

		for (auto &i : result) {
			out << i << endl;
		}

		out.close();
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  writeToFileWithModeAdd
	 *  Description: 写文件操作
	 * ===================================================================================== 
	 */
	void writeToFileWithModeAdd(const string &filePath, double result) {
		ofstream out(filePath, ios::app);
		if (!out.is_open()){ 
			cout << "Error opening file" << endl; 
			exit (1); 
		}
		out << result << endl;

		out.close();
	}

	/*  
	 * ===  FUNCTION  ====================================================================== 
	 *         Name:  readFile 
	 *  Description: 读文件操作
	 * ===================================================================================== 
	 */
	vector<string> readFile(const string &filePath) {
		vector<string> readResult;
		ifstream in(filePath);
		if (!in.is_open()){ 
			cout << "Error opening file" << endl; 
			exit (1); 
		}
		char line[1024];

		while (in.getline(line, sizeof(line))) {
			string s(line);
			readResult.push_back(s);
		}
		in.close();
		return readResult;
	}
private:
	
};

#endif