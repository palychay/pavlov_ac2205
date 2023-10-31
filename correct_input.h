#include <iostream>
#include <fstream>

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
    }
	void redirect (std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};


template <typename T> 
T get_correct(T max, T min){
    T x;
	while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max)	// is buffer empty (int/float check)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Incorrect input. Please enter again:  ";
	}
	std::cerr << x << std::endl;
    return x;
}