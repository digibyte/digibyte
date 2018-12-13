// Copyright (c) 2009-2018 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
// Author: Yoshi Jaeger

// This class provides disk memory allocations to reduce the overall memory usage.
// It is very important to mention, that this allocator does not provide an implementation for delete(),
// hence, memory allocated with this class can't be freed.
// In this case, it is acceptable since CBlockIndex are kept in memory and never will be deleted until the application terminates.

#include <config/digibyte-config.h>

#if defined(MEMORY_MAPPING) && !defined(WIN32)
	#ifndef DIGIBYTE_DISK_ALLOCATOR_H
	#define DIGIBYTE_DISK_ALLOCATOR_H

	#include <stddef.h>

	#ifndef MEMORY_MAPPING_SIZE
		// default: 8 GB
		#define MEMORY_MAPPING_SIZE (1024 * 1024 * 1024 * 8ULL)
	#endif

	#ifndef MEMORY_MAPPING_PATH
		// ToDo: use daemon flag to define the path or use ENV_VAR
		#define MEMORY_MAPPING_PATH "./digibyte-memory"
	#endif

	class DiskAllocator
	{
	    private:
	    	DiskAllocator();
	    	~DiskAllocator();
	        static DiskAllocator* instance;

	        int fd;
	        unsigned long long offset;
	        char* map;

	    public:
	        static DiskAllocator* getInstance();
	        void* alloc(size_t size);
	};

	#endif
#endif
