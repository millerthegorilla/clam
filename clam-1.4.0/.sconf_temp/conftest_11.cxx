
#include <xercesc/util/PlatformUtils.hpp>
int main( int argc, char** argv )
{
	namespace xercesc=XERCES_CPP_NAMESPACE;
	xercesc::XMLPlatformUtils::Initialize();
	return 0;
}
