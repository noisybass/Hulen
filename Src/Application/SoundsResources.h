#ifndef SOUNDS_RESOURCES_H
#define SOUNDS_RESOURCES_H

namespace Application 
{
	
	class CSoundsResources
	{
	public:
		
		// Constructor and Destructor
		CSoundsResources();
		virtual ~CSoundsResources();

		// Sounds Resources
		static bool init();
		static void release();
		static CSoundsResources *getSingletonPtr() { return _instance; }

		// Global sound
		static void loadAll();
		static void unloadAll();

		// Main Menu
		static void loadMainMenu();
		static void unloadMainMenu();

	protected:

		static CSoundsResources* _instance;
	}; // SoundsResources

} // namespace Application

#endif //  SOUNDS_RESOURCES_H
