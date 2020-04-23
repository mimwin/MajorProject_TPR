#pragma once
#include <iostream>
#include <string>

using namespace std;

class Schedule {
private:
    string content;
    string keyword;

public:
    Schedule();
    Schedule(string content, string keyowrd);
    string& getContent();
    string& getKeyword();
    void setContent(string& s);
    void setKeyword(string& s);

};