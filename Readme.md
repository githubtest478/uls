ULS

NAME
    uls - list directory content

SYNOPSIS
    uls [-l] [file ...]

DESCRIPTION
    List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -cftuv. Line up files by columes(default) or in long format. Mandatory arguments to long options are mandatory for short options too.

Realized flags
(Basic + Advanced):
    -@ Display extended attribute keys and sizes in long (-l) output
    -1 Force output to be one entry per line.  This is the default when output is not to a terminal.
    -A List all entries except for . and ..  Always set for the super-user.
    -a Include directory entries whose names begin with a dot (.).
    -C Force multi-column output; this is the default when output is to a terminal.
    -c Use time when file status was last changed for sorting (-t) or long printing (-l).
    -e Print the Access Control List (ACL) associated with the file, if present, in long (-l) output.
    -G Enable colorized output.  This option is equivalent to defining CLICOLOR in the environment.
    -h When used with the -l option, use unit suffixes: Byte, Kilobyte, Megabyte, Gigabyte, Terabyte and Petabyte in order to reduce the number of digits to three or less using base 2 for sizes.
    -l use a long listing format
    -R recursively list subdirectories recursively
    -r Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.
    -S Sort files by size
    -T used with the -l option, display complete time information for the file, including month, day, hour, minute, second, and year.
    -t Sort by time modified
    -u Use time of last access, instead of last modification of the file for sorting (-t) or printing (-l).

Aditional:
    -f Output is not sorted.
    -i For each file, print the file's file serial number 
    -x Stream output format; The same as -C, except that the multi-column output is produced with entries sorted across, rather than down, the columns.
    -p Write a slash (/) after each filename if that file is a directory.
    -m Stream output format; List files across the page, separated by commas.
    -s Display the number of file system blocks actually used by each file, in units of 512 bytes, where partial units are rounded up to the next integer value.

The SIZE argument is an integer and optional unit (example: 10K is 10*1024).  Units are K,M,G,T,P,E,Z,Y (powers of 1024) or KB,MB,... (powers of 1000).

The TIME_STYLE argument can be full-iso, long-iso, iso or locale. The TIME_STYLE environment variable sets the default style to use.

Using color to distinguish file types is disabled both by default. 

Long format structure with all aditional options:

[SERIAL NUMBER] [BLOCK SIZE] [PERMISSION] [LINK NUMBER] [OWNER] [GROUP] [SIZE] [TIME] [NAME] -> [LINC SOURCE]

   Exit status:
    0      if OK,
    1      if minor problems (e.g., cannot access subdirectory)

AUTHOR
    Written by dtretiakov and opovshenco (Ucode students)
