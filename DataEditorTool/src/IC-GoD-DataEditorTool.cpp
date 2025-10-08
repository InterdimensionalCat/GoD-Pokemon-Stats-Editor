#include "include.h"

#include "MainEditor/DataEditorInstance.h"

/** On Windows release builds, hide the console window. */
#ifdef _WIN32
#ifdef IC_DEBUG

#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // IC_DEBUG
#endif // _WIN32

void RunApplication()
{
	// Create an instance of the application.
	DataEditorInstance::CreateInstance();

	// Init application.
	DataEditorInstance::Get()->Init();

	// Run application loop.
	DataEditorInstance::Get()->ApplicationLoop();

	// Destroy the application instance, which allows
	// various contexts to be destroyed, and ends
	// the logging session.
	DataEditorInstance::Get()->DestroyInstance();

}

int main(int argc, char* args[])
{
	std::cout.flush();

	/** Initialize logger. */
	ICLogger::InitLogger();

#ifdef _WIN32
#ifdef IC_DEBUG
	/** Uncomment to check for memory leaks on Windows debug mode. */

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//ICLogger::Debug("Windows debug mode memory leak checking enabled.");
#endif // IC_DEBUG
#endif // _WIN32

	/** Run the application. */
	RunApplication();

	/** Uninitialize Logger. */
	ICLogger::ExitLogger();

	/** Uncomment to pause app before exiting on Windows. */
	// system("pause");

	return 0;
}
