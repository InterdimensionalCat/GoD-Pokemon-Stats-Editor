#include "include.h"

#include "MainEditor/DataEditorInstance.h"

/** On Windows release builds, hide the console window. */
#ifdef _WIN32
#ifdef IC_DEBUG

#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // IC_DEBUG
#endif // _WIN32

void OnProgramTerminated()
{
	// Called when the program is terminated unexpectedly.
	// Otherwise known as a crash.
	ICLogger::Critical("Uncaught exception has triggered a crash!");

	std::exception_ptr CurrentExceptionPtr = std::current_exception();
	try
	{
		std::rethrow_exception(CurrentExceptionPtr);
	} catch (const std::exception& e) 
	{
		ICLogger::Critical("Uncaught exception: {}", e.what());
	}

	DataEditorInstance::Get()->DestroyInstance();

	// TODO: Attempt to dump any unsaved data to a recovery log here.
	// TODO: Save a crash log with trace logging information and a call stack here. (std::stacktrace in C++23)

	ICLogger::ExitLoggerAfterCrash();

	std::abort();
}

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

	// Set a custom crash handler.
	std::set_terminate(OnProgramTerminated);

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
