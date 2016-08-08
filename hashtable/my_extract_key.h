#ifndef _MY_EXTRACT_KEY_H
#define _MY_EXTRACT_KEY_H

template <class Arg,class Result>
struct _unary_function
{
	typedef Arg argument_type;
	typedef Result result_type;
};

template <class T>
struct Identity:public _unary_function<T,T>
{
	const T& operator()(const T& x) const{return x;}
};

#endif  //!  _MY_EXTRACT_KEY_H
