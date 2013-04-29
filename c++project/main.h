// main.h
// Mara Kim
//
// Default values


#define PROJECT_STATICS
#include "Options.h"
#include "Project.h"

// Defaults
template <typename ENUM>
typename TypeInfo<ENUM>::key_type TypeInfo<ENUM>::keys;
template <typename ENUM>
typename TypeInfo<ENUM>::map_type TypeInfo<ENUM>::defaults;
template <typename ENUM>
typename TypeInfo<ENUM>::my_type TypeInfo<ENUM>::init;

#ifndef PROGRAM_NAME
#define PROGRAM_NAME
#endif
#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION
#endif
