#ifndef TRACYAPI_H
#define TRACYAPI_H

#if defined _WIN32
#if defined TRACY_EXPORTS
#define TRACY_API __declspec(dllexport)
#elif defined TRACY_IMPORTS
#define TRACY_API __declspec(dllimport)
#else
#define TRACY_API
#endif
#else
#define TRACY_API __attribute__((visibility("default")))
#endif

#endif// TRACYAPI_H
