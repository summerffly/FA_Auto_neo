
/**************************************************/
/*          Advanced Configuration Class          */
/*             Coded by summer @ CMF              */
/*           Created on: May 06, 2021             */
/**************************************************/

#ifndef _XONFIG_H_
#define _XONFIG_H_

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <vector>


class Xonfig
{
/***** Data *****/
protected:
	std::string m_Delimiter;   // separator between key and value
	std::string m_Comment;     // separator between value and comments
	std::map<std::string,std::string> m_Contents;   // extracted keys and values
	std::vector<std::string> m_Lines;   // original entire line contents

	typedef std::map<std::string,std::string>::iterator mapi;
	typedef std::map<std::string,std::string>::const_iterator mapci;

/***** Methods *****/
public:
	Xonfig( std::string filename, std::string delimiter = "=", std::string comment = "#" );
	Xonfig();

	bool FileExist( std::string filename );
	void ReadFile( std::string filename, std::string delimiter = "=", std::string comment = "#" );

	// Check whether key exists in configuration
	bool KeyExists( const std::string& in_key ) const;

	// Search for key and read value or optional default value, call as read<T>
	template <class T> T Read( const std::string& in_key ) const;
	template <class T> T Read( const std::string& in_key, const T& in_value ) const;
	template <class T> bool ReadInto( T& out_var, const std::string& in_key ) const;
	template <class T> bool ReadInto( T& out_var, const std::string& in_key, const T& in_value ) const;

	// Modify keys and values  
	template<class T> void Add( const std::string& in_key, const T& in_value );
	void Remove( const std::string& in_key );

	// Check or change configuration syntax  
	std::string GetDelimiter() const
	{
		return m_Delimiter;
	}

	std::string GetComment() const
	{
		return m_Comment;
	}

	std::string SetDelimiter( const std::string& in_s )  
	{
		std::string old = m_Delimiter;
		m_Delimiter = in_s;
		return old;
	}

	std::string SetComment( const std::string& in_s )
	{
		std::string old = m_Comment;
		m_Comment =  in_s;
		return old;
	}

	// Write or Read Configuration
	friend std::ostream& operator<<( std::ostream& os, const Xonfig& cf );
	friend std::istream& operator>>( std::istream& is, Xonfig& cf );

protected:  
	template<class T> static std::string T_as_string( const T& t );
	template<class T> static T string_as_T( const std::string& s );

	static void Trim( std::string& inout_s );

/***** Exception Types *****/
public:  
	struct File_not_found
	{
		std::string filename;
		File_not_found( const std::string& filename_ = std::string() )
			: filename(filename_) {}
	};
	// thrown only by T read(key) variant of read()
	struct Key_not_found
	{
		std::string key;
		Key_not_found( const std::string& key_ = std::string() )
			: key(key_) {}
	};
};

/*** static ***/
template <class T> 
std::string Xonfig::T_as_string( const T& t )
{
	// Convert from a T to a string
	// Type T must support << operator
	std::ostringstream ost;
	ost << t;
	return ost.str();
}

/*** static ***/
template <class T> 
T Xonfig::string_as_T( const std::string& s )
{
	// Convert from a string to a T
	// Type T must support >> operator
	T t;
	std::istringstream ist(s);
	ist >> t;
	return t;
}

/*** static / specialized template ***/
template <> 
inline std::string Xonfig::string_as_T<std::string>( const std::string& s )
{
	// Convert from a string to a string
	// In other words, do nothing
	return s;
}

/*** static / specialized template ***/
template <> 
inline bool Xonfig::string_as_T<bool>( const std::string& s )
{
	// Convert from a string to a bool
	// Interpret "false", "F", "no", "n", "0" as false
	// Interpret "true", "T", "yes", "y", "1", "-1", or anything else as true
	bool b = true;
	std::string sup = s;
	for( std::string::iterator p = sup.begin(); p != sup.end(); ++p )
		*p = toupper(*p);   // make string all caps
	if( sup==std::string("FALSE") || sup==std::string("F") || 
		sup==std::string("NO") || sup==std::string("N") || 
		sup==std::string("0") || sup==std::string("NONE") )
		b = false;
	return b;
}

template<class T> 
T Xonfig::Read( const std::string& key ) const
{
	// Read the value corresponding to key
	mapci p = m_Contents.find(key);
	if( p == m_Contents.end() ) throw Key_not_found(key);
	return string_as_T<T>( p->second );
}

template<class T>
T Xonfig::Read( const std::string& key, const T& value ) const
{  
	// Return the value corresponding to key or given default value  
	// if key is not found  
	mapci p = m_Contents.find(key);  
	if( p == m_Contents.end() ) return value;  
	return string_as_T<T>( p->second );  
}  

template<class T>
bool Xonfig::ReadInto( T& var, const std::string& key ) const
{  
	// Get the value corresponding to key and store in var  
	// Return true if key is found  
	// Otherwise leave var untouched  
	mapci p = m_Contents.find(key);  
	bool found = ( p != m_Contents.end() );  
	if( found ) var = string_as_T<T>( p->second );  
	return found;  
}  

template<class T>  
bool Xonfig::ReadInto( T& var, const std::string& key, const T& value ) const
{  
	// Get the value corresponding to key and store in var  
	// Return true if key is found  
	// Otherwise set var to given default  
	mapci p = m_Contents.find(key);  
	bool found = ( p != m_Contents.end() );  
	if( found )  
		var = string_as_T<T>( p->second );  
	else 
		var = value;  
	return found;  
}  

template<class T> 
void Xonfig::Add( const std::string& in_key, const T& value )
{
	// Add a key with given value
	std::string v = T_as_string( value );
	std::string key=in_key;
	Trim(key);
	Trim(v);
	m_Contents[key] = v;
	return;
}

void Xonfig::Remove( const std::string& key )
{
	// Remove key and its value
	m_Contents.erase( m_Contents.find( key ) );
	return;
}

/**************************************************/
// Remove leading and trailing whitespace
/**************************************************/
/*** static ***/
void Xonfig::Trim( std::string& inout_s )
{
	static const char whitespace[] = " \n\t\v\r\f";
	inout_s.erase( 0, inout_s.find_first_not_of(whitespace) );
	inout_s.erase( inout_s.find_last_not_of(whitespace) + 1U );
}


#endif

/**************************************************/
/*             River flows in summer              */
/**************************************************/
