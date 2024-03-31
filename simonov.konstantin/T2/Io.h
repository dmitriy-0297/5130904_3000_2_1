#ifndef IO_H
#define IO_H

#include <string>
#include <iostream>
#include <vector>

namespace simonov
{
	struct Data
	{
		unsigned long long key1;
		unsigned long long key2;
		std::string key3;
		bool thatIsHorror = false;
	};

	struct ULLLit
	{
		unsigned long long& valueLit;
	};

	struct ULLOct
	{
		unsigned long long& valueOct;
	};

	struct StrKey
	{
		std::string& valueStr;
	};

	struct Border
	{
		std::vector<std::string> borders;
		short length_;
		Border(const std::vector<std::string> myVector, const short len) :
			borders(myVector), length_(len)
		{
		}
	};

	class StreamGuard
	{
	public:
		StreamGuard(std::basic_ios< char >& s);
		~StreamGuard();
	private:
		std::basic_ios< char >& strm_;
		char fill_;
		std::streamsize precision_;
		std::basic_ios< char >::fmtflags fmt_;
	};

	std::istream& operator >> (std::istream& in, Border&& fence);
	std::istream& operator >> (std::istream& in, StrKey&& str);
	std::istream& operator >> (std::istream& in, ULLLit&& lit);
	std::istream& operator >> (std::istream& in, ULLOct&& oct);
	std::istream& operator >> (std::istream& in, Data& data);
	std::ostream& operator << (std::ostream& out, const Data& fence);
	void whichKeyYouWrote(const std::string& key, Data& data, std::istream& stream, bool flags[]);
}

#endif // !IO_H
