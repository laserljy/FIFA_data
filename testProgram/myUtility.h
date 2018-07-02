#ifndef MY_UTILITY_H_
#define MY_UTILITY_H_

vector<string> str2Vec(string input, char delim){
	vector<string> result;
	// A bug was found when trying to use country name abbreviation instead of full name. Then the print out formation is quite confusing, after trying different elements, I finally identitified that it is because we access the last elem in the vector.
	// this is the OS dependent thing, in Windows there two chars at the end of line: \r\n, that is why unexpected things happen when accessing the last elem in the inputVec, need to get rid of the last char. See this link: http://www.cplusplus.com/forum/general/51349/, comments by mik2718
	input = input.substr(0, input.size()-1);
	istringstream iss(input);
	string token;
	while(getline(iss, token, delim)){
		result.push_back(token);
	}
	return result;
}

// This function is slightly different from the str2Vec, the reason is the input is from a getline() that ends with /r/n or a string without /r
vector<string> strSplit(string input, char delim){
	vector<string> result;
	istringstream iss(input);
	string token;
	while(getline(iss, token, delim)){
		result.push_back(token);
	}
	return result;
}

#endif // MY_UTILITY_H_