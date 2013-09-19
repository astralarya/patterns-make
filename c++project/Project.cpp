// Project.cpp
// Mara Kim
//
// Define statics

#include "Type.h"

#define PROJECT_STATICS
#include "Project.h"
#undef PROJECT_STATICS

// Defaults
template <typename ENUM>
typename TypeInfo<ENUM>::key_type TypeInfo<ENUM>::keys;
template <typename ENUM>
typename TypeInfo<ENUM>::defaults_type TypeInfo<ENUM>::defaults;
template <typename ENUM>
typename TypeInfo<ENUM>::init_type TypeInfo<ENUM>::init;
// NOTE: Integral types must define init in Project.h
