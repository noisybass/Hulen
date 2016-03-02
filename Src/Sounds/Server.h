#ifndef SOUNDS_SERVER_H
#define SOUNDS_SERVER_H

namespace Sounds{

	class CServer{
	
	public:

		static bool Init();

		static bool Release();

		static bool tick();


	private:
	
		/**
		Constructor
		*/
		CServer();

		/**
		Destructor
		*/
		virtual ~CServer();

		//Instancia del servidor
		CServer* _instance;
	
	
	};


} // Namespace Sounds



#endif SOUNDS_SERVER_H