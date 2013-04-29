// main.h
// Mara Kim
//
// Default values


#include "Options.h"
#define PROJECT_STATICS
#include "Project.h"

// Defaults
template <typename ENUM>
typename TypeInfo<ENUM>::key_type TypeInfo<ENUM>::keys;
template <typename ENUM>
typename TypeInfo<ENUM>::defaults_type TypeInfo<ENUM>::defaults;
template <typename ENUM>
typename TypeInfo<ENUM>::init_type TypeInfo<ENUM>::init;

#ifndef PROGRAM_NAME
#define PROGRAM_NAME
#endif
#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION
#endif
