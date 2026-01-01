#pragma once


#ifndef ExpInteropAPI_EXPORT
#define ExpInteropAPI __declspec(dllimport)
#else
#define ExpInteropAPI __declspec(dllexport)
#endif