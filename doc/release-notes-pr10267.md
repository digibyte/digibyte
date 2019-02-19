Changed command-line options
----------------------------

- `-includeconf=<file>` can be used to include additional configuration files.
  Only works inside the `digibyte.conf` file, not inside included files or from
  command-line. Multiple files may be included. Can be disabled from command-
  line via `-noincludeconf`. Note that multi-argument commands like
  `-includeconf` will override preceding `-noincludeconf`, i.e.

    noincludeconf=1
    includeconf=relative.conf

  as digibyte.conf will still include `relative.conf`.
