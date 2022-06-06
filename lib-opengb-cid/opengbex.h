// OpenGB Exception

#if !defined(__opengbex_h_)
	#define __opengbex_h_
	
	#include <exception>
	#include <string>

namespace opengb{
	class OpenGBException:public std::exception{
	public:
		OpenGBException(std::string message): exception(message.c_str()) {; }
	};
	
	namespace cizidn{
		class CitizenIdException:public OpenGBException{
		public:
			CitizenIdException(std::string message): OpenGBException(message) {; }
		};
		
		class Not18CIdException:public CitizenIdException{
		public:
			Not18CIdException(std::string message): CitizenIdException(message) {; }
		};
	}
}

#endif