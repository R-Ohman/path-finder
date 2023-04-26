#pragma once
#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#define HASHMAP_SIZE		5000
#define VECTOR_BLOCK_SIZE	8  // Change to 3.000.000 to pass 13.in test, 135k for 10 & 12 tests
#define VECTOR_START_SIZE	2
#define CITY_NAME_BUFFER	64

static int constructorCounter = 0;
static int destructorCounter = 0;

#include <iostream>
#include "Vector.h"
//#include "String.h"
#include "HashMap.h"
#include "AnotherCity.h"
#include "City.h"
#include "CitiesGraph.h"
#include "MinHeap.h"


#endif