#pragma once
#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#define HASHMAP_SIZE            5000
#define VECTOR_START_SIZE       64
#define CITY_NAME_BUFFER        64

static int constructorCounter = 0;
static int destructorCounter = 0;

#include <iostream>
#include "Vector.h"
#include "HashMap.h"
#include "AnotherCity.h"
#include "City.h"
#include "CitiesGraph.h"
#include "MinHeap.h"


#endif