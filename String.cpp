#include "String.h"

using namespace dstring;

wchar_t* expand(const wchar_t* ptr, size_t n)
{
	auto p = new wchar_t[n];
	wcscpy_s(p, n, ptr);

	return p;
}


String::String()
	: sz(0),
	space{ 0 },
	pStr{ new wchar_t[sz + 1]{ 0 } }
{
}

String::String(const wchar_t* s)
	: sz(wcslen(s)),
	space{ 0 },
	pStr{ new wchar_t[sz + 1] }
{
	wcscpy_s(pStr, sz + 1, s);
}

String::String(const String& s)
{
	copy_from(s);
}

String::~String()
{
	delete[] pStr;
}

String& String::operator=(const String& s)
{
	if (this == &s)
		return *this;

	auto p = pStr;
	copy_from(s);
	delete[] p;

	return *this;
}


String& String::operator+=(wchar_t c)
{
	if (space == 0) {
		auto n = sz + sz + 2; // double the allocation (+2 because of the terminating 0)

		auto p = expand(pStr, n);
		delete[] pStr;
		pStr = p;

		space = n - sz - 2;
	}
	else
	{
		--space;
	}

	pStr[sz] = c; // add "c" at end
	pStr[++sz] = 0; // increase size and set terminator

	return *this;
}

void String::copy_from(const String& x)
{
	sz = x.sz;
	pStr = expand(x.pStr, x.sz + 1);
	space = 0;
}

String& dstring::operator+=(String& a, const String& b)
{
	for (auto c = b.c_str(); c != b.c_str() + b.size(); ++c)
		a += *c;

	return a;
}

String dstring::operator+(const String& a, const String& b)
{
	auto sum{ a };
	sum += b;

	return sum;
}

std::wostream& dstring::operator<<(std::wostream& os, const String& s)
{
	return os << s.c_str();
}

std::wistream& dstring::operator>>(std::wistream& is, String& s)
{
	s = L""; // clear the target string
	is >> std::ws; // skip whitespace

	wchar_t ch;
	while (is.get(ch) && !isspace(ch))
		s += ch;

	return is;
}

bool dstring::operator<(const String& a, const String& b)
{
	return _wcsicmp(a.c_str(), b.c_str()) < 0 ? true : false;
}

bool dstring::operator>(const String& a, const String& b)
{
	return _wcsicmp(a.c_str(), b.c_str()) > 0 ? true : false;
}
