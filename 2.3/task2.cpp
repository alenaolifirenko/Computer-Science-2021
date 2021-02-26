#include <iostream>

std::size_t hash(const char * s)
{
	std::size_t h = 0U;

	for( const char* p = s; *p != '\0'; ++p)
	{
		h = h * 31 + static_cast < unsigned int > (*p);
	}

	return h % 128;
}

std::size_t hash_double( double d)
{
    double* pd = &d;
    char* c = (char*) pd;
    std::cout << sizeof(double) << std::endl;
    char cd[ sizeof(double) + 1 ];
    for( int i = 0; i < sizeof(double); ++i )
    {
        cd[i] = c[i];
    }
    cd[ sizeof(double) ] = '\0';

    return  hash(cd);
}

int main()
{

    double d = 3.1415926;

	std::cout << std::endl << hash_double(d) << std::endl;

	return 0;
}


// hash(d) = 38