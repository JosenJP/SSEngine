
#ifdef SSENGINE_PROJECT
    #define SSENGINECLASS __declspec(dllexport)
#else
    #define SSENGINECLASS __declspec(dllimport)
#endif
