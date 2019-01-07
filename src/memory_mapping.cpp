// Copyright (c) 2009-2018 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
// Author: Yoshi Jaeger

#include <memory_mapping.h>

#if defined(MEMORY_MAPPING) && !defined(WIN32)
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/mman.h>
	#include <limits.h>
	#include <fcntl.h>
	#include <stdio.h>

	DiskAllocator* DiskAllocator::instance = 0;

	DiskAllocator* DiskAllocator::getInstance() {
	    if (instance == 0) {
	        instance = new DiskAllocator();
	    }

	    return instance;
	}

	DiskAllocator::~DiskAllocator() {
		// unmap and close file 
		if (munmap(map, MEMORY_MAPPING_SIZE) == -1) {
			perror("[WARNING] DiskAllocator unmapping not successful");
	    }
		close(this->fd);
	}

	DiskAllocator::DiskAllocator() {
		const char* filename = MEMORY_MAPPING_PATH;
		printf("Creating memory mapped file: %s\n", filename);

		// allocator offset
		this->offset = 0;

		// retrieve file descriptor
		this->fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);// fileno(this->file);
		if (this->fd == -1) {
			perror("[CRITICAL] Could not create temporary file. Exiting due to error");
			exit(EXIT_FAILURE);
		}

		// preserve space
		if (ftruncate(fd, MEMORY_MAPPING_SIZE)) {
			perror("[CRITICAL] Could not allocate disk space. Exiting due to error");
			exit(EXIT_FAILURE);
		}

		// map the file to memory
		/* use MAP_SHARED instead of map_private if digibyted is supposed to write directly to the file */
		this->map = (char*) mmap(0, MEMORY_MAPPING_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, this->fd, this->offset);
		if (this->map == MAP_FAILED) {
			perror("[CRITICAL] Could not map file to disk. Exiting due to error");
			exit(EXIT_FAILURE);
		}
	}

	void* DiskAllocator::alloc(size_t size) {
		// return allocated memory
		void* ret = (map + offset);
		offset += size;
		
		return ret;
	}
#endif
