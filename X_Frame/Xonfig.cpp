
/**************************************************/
/*          Advanced Configuration Class          */
/*             Coded by summer @ CMF              */
/*           Created on: May 06, 2021             */
/**************************************************/

#include "Xonfig.h"


/**************************************************/
//   Construct a Config
//   Getting keys and values from given file
/**************************************************/
Xonfig::Xonfig( std::string filename, std::string delimiter, std::string comment ) : m_Delimiter(delimiter), m_Comment(comment)
{
	std::ifstream in( filename.c_str() );

	if( !in )
		throw File_not_found( filename );

	in >> (*this);
}

/**************************************************/
//   Construct a Config without a file; empty
/**************************************************/
Xonfig::Xonfig() : m_Delimiter( std::string(1,'=') ), m_Comment( std::string(1,'#') )
{
	// ~
}

// Indicate whether key is found
bool Xonfig::KeyExists( const std::string& key ) const
{
	mapci p = m_Contents.find( key );
	return ( p != m_Contents.end() );
}

std::ostream& operator<<( std::ostream& os, const Xonfig& cf )
{  
	// Save a Config to os
	for( Xonfig::mapci p = cf.m_Contents.begin();
		p != cf.m_Contents.end();
		++p )
	{  
		os << p->first << " " << cf.m_Delimiter << " ";  
		os << p->second << std::endl;  
	}
	return os;
}

std::istream& operator>>( std::istream& is, Xonfig& cf )
{  
	// Load a Config from is
	// Read in keys and values, keeping internal whitespace
	typedef std::string::size_type pos;
	const std::string& delim  = cf.m_Delimiter;  // separator
	const std::string& comm   = cf.m_Comment;    // comment
	const pos skip = delim.length();        // length of separator

	std::string nextline = "";  // might need to read ahead to see where value ends

	while( is || nextline.length() > 0 )
	{
		// Store original entire line
		cf.m_Lines.push_back(nextline);

		// Read an entire line at a time
		std::string line;
		if( nextline.length() > 0 )
		{
			line = nextline;  // we read ahead; use it now
			nextline = "";
		}
		else
		{
			std::getline( is, line );
		}

		// Ignore comments
		line = line.substr( 0, line.find(comm) );

		// Parse the line if it contains a delimiter
		pos delimPos = line.find( delim );
		if( delimPos < std::string::npos )
		{
			// Extract the key
			std::string key = line.substr( 0, delimPos );
			line.replace( 0, delimPos+skip, "" );

			// See if value continues on the next line
			// Stop at blank line, next line with a key, end of stream,
			// or end of file sentry
			bool terminate = false;
			while( !terminate && is )
			{
				std::getline( is, nextline );
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

			// Store key and value
			Xonfig::Trim(key);
			Xonfig::Trim(line);
			cf.m_Contents[key] = line;   // overwrites if key is repeated
		}
	}

	return is;
}

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

/**************************************************/
/*             River flows in summer              */
/**************************************************/
