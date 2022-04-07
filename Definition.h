#pragma once
#include <iostream>
#include <string>


int randRange(int min, int max);

void log(std::string i_msg);

template<typename Base, typename T>
inline bool instanceof(const T *ptr);
