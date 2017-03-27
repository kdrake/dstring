#ifndef __STRING_H_
#define __STRING_H_

#include <iostream>

namespace dstring {

	class String
	{
	public:
		/// ctor/dtor
		String();
		String(const wchar_t* s);
		String(const String& s);
		~String();

		///
		String&			operator =(const String& s);
		String&			operator +=(wchar_t c);

		/// ancillary functions
		const wchar_t*	c_str() const { return pStr; }
		size_t			size() const { return sz; }

	private:
		size_t			sz; // number of characters
		size_t			space; // unused allocated space 
		wchar_t*		pStr{ nullptr }; // points to the start of the character sequence

		void			copy_from(const String& x);
	};

	String&				operator +=(String& a, const String& b);
	String				operator +(const String& a, const String& b);
	std::wostream&		operator <<(std::wostream& os, const String& s);
	std::wistream&		operator >>(std::wistream& is, String& s);
	bool				operator <(const String& a, const String& b);
	bool				operator >(const String& a, const String& b);

}	// namespace dstring
#endif	// __STRING_H_
