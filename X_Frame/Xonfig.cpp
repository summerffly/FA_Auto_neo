
/**************************************************/
/*          Advanced Configuration Class          */
/*             Coded by summer @ CMF              */
/*           Created on: May 06, 2021             */
/**************************************************/

#include "Xonfig.h"


//------------------------------------------------//
//   Construct a Config
//   Getting keys and values from given file
//------------------------------------------------//
Xonfig::Xonfig( std::string filename, std::string delimiter, std::string comment ) : m_Delimiter(delimiter), m_Comment(comment)
{
	std::ifstream in( filename.c_str() );

	if( !in )
		throw File_not_found( filename );

	in >> (*this);
}

//------------------------------------------------//
//   Construct a Config without a file; empty
//------------------------------------------------//
Xonfig::Xonfig() : m_Delimiter( std::string(1,'=') ), m_Comment( std::string(1,'#') )
{
	// ~
}

//------------------------------------------------//
//   Indicate whether file exists
//------------------------------------------------//
bool Xonfig::FileExist( std::string filename )
{
	bool exist = false;
	std::ifstream in( filename.c_str() );
	if( in )
		exist = true;
	return exist;
}

void Xonfig::ReadFile( std::string filename, std::string delimiter, std::string comment )
{
	m_Delimiter = delimiter;
	m_Comment = comment;
	std::ifstream in( filename.c_str() );
	if( !in )
		throw File_not_found( filename );
	in >> (*this);
}

//------------------------------------------------//
//   Indicate whether key is found
//------------------------------------------------//
bool Xonfig::KeyExists( const std::string& key ) const
{
	mapci p = m_kv_Map.find( key );
	return ( p != m_kv_Map.end() );
}

//######  operator overloading  ######//
//------------------------------------------------//
//   Save a Config to os by original format
//------------------------------------------------//
std::ostream& operator<<( std::ostream& os, const Xonfig& cf )
{
	for( Xonfig::vecci p = cf.m_neo_Lines.begin();
		p != cf.m_neo_Lines.end();
		p++ )
	{
		os << p->fullline << std::endl;
	}
	return os;
}

//######  operator overloading  ######//
//------------------------------------------------//
//   Load a Config from is
//------------------------------------------------//
std::istream& operator>>( std::istream& is, Xonfig& cf )
{
	// Read in keys and values, keeping internal whitespace
	typedef std::string::size_type pos;

	const std::string& delim  = cf.m_Delimiter;   // separator
	const std::string& comm   = cf.m_Comment;     // comment
	const pos delimLen = delim.length();   // length of separator
	const pos commLen = comm.length();     // length of comment

	cf.m_neo_Lines.clear();

	std::string line;
	NEO_LINE neo_line;
	while( std::getline( is, line ) )
	{
		/*****  Store original entire line  *****/
		memset(&neo_line, 0, sizeof(NEO_LINE));
		neo_line.fullline = line;

		/*****  Extract the comments  *****/
		std::string note;
		pos commPos = line.find( comm );
		if( commPos < std::string::npos )
		{
			note = line.substr( commPos+commLen );
			line = line.substr( 0, line.find(comm) );
		}

		// Parse the line if it contains a delimiter
		pos delimPos = line.find( delim );
		if( delimPos < std::string::npos )
		{
			/*****  Extract the key  *****/
			std::string key = line.substr( 0, delimPos );
			line.replace( 0, delimPos+delimLen, "" );

		#if 0   // DO NOT support multi-line value
			// See if value continues on the next line
			// Stop at blank line, next line with a key, end of stream, or end of file sentry
			bool terminate = false;
			while( !terminate && is )
			{
				std::getline( is, nextline );
				cf.m_Lines.push_back(nextline);
				terminate = true;

				std::string nlcopy = nextline;
				Xonfig::Trim(nlcopy);
				if( nlcopy == "" )
					continue;

				nextline = nextline.substr( 0, nextline.find(comm) );
				if( nextline.find(delim) != std::string::npos )
					continue;

				nlcopy = nextline;
				Xonfig::Trim(nlcopy);
				if( nlcopy != "" )
					line += "\n";
				line += nextline;
				terminate = false;
			}
		#endif

			/*****  Store key and value  *****/
			Xonfig::Trim(key);
			Xonfig::Trim(line);
			cf.m_kv_Map[key] = line;   // overwrites if key is repeated

			neo_line.key = key;
			neo_line.value = line;
			neo_line.comment = note;
		}
		cf.m_neo_Lines.push_back(neo_line);
	}

	return is;
}

//######  static  ######//
//------------------------------------------------//
//   Remove leading and trailing whitespace
//------------------------------------------------//
void Xonfig::Trim( std::string& inout_s )
{
	static const char whitespace[] = " \n\t\v\r\f";
	inout_s.erase( 0, inout_s.find_first_not_of(whitespace) );
	inout_s.erase( inout_s.find_last_not_of(whitespace) + 1U );
}

void Xonfig::Remove( const std::string& in_key )
{
	// Remove key and its value from map
	m_kv_Map.erase( m_kv_Map.find( in_key ) );

	// Remove fullline from vector
	for( veci it = m_neo_Lines.begin(); it != m_neo_Lines.end(); it++ )
	{
		if( it->key == in_key )
		{
			m_neo_Lines.erase(it);
			break;
		}
	}

	return;
}


/**************************************************/
/*             River flows in summer              */
/**************************************************/
