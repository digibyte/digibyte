Build on Raspberry PI
=====================

Use the new flag ```bash
--enable-low-memory-mode
```

when running ./configure to use memory mapped files, which perform better than SWAP memory and prevent crashes.


Important Notes
---------------

This is still under development and needs a lot of testing. Make sure you have additional 8GB disk space left in your current working directory.



Technical notes
---------------

Currently it will place a 8GB file into your current working directory when running digibyted. 
This file will be mapped into memory to allow faster IO (no copies are done).
The file will contain only null-bytes, until the applications encounters memory issues. At that very moment, the operating system will write unused pages to disk


ToDo
----

Use ```madvise()``` in order to help the OS deciding whether pages are still needed.
Also export ```MEMORY_MAPPING_PATH``` and ```MEMORY_MAPPING_SIZE```. Currently these makros are fixed.


