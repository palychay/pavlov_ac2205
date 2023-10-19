#include <iostream>

template <typename T> 
T get_correct(T max, T min){
    T x;
	while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max)	// is buffer empty (int/float check)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Incorrect input. Please enter again:  ";
	}
    return x;
}