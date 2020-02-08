# FT_LS - A 42 Silicon Valley Project

## Description
<p>Ft_ls is the first project in the systems branch.</p>
<p>The Project outline is to recreate the functionality of the ls command.
</p>
<p> Running version:

***FreeBSD: src/bin/ls/ls.c,v 1.66 2002/09/21 01:28:36 wollman Ex***

Located via -> https://opensource.apple.com/source/file_cmds/file_cmds-230/ls/

Our goal is to recreate the program with flags l ('ell'), r, a, t, R.

__l flag:__ long list format (drw-rw-r-- 1 root wheel 0 Apr 20 11:42 fileA)

__r flag:__ reverse output

__a flag:__ print hidden files/directories along with normal output

__t flag:__ sort output by time last modified

__R flag:__ Recursivley interate through all subdirectories

The implementation is not allowed to segfault or fail for any reason.
The program cannot have any leaks.
The format of the source code must follow strict format guidelines employed by 42
This is the sole reason for all of the funky functions and the spacing of each program.
This task is carried out 'after' writting readable code.
</p>

## Program Features

<p>My implementation covers all required flags plus the bonus flags A, c, i.

__A flag:__ same as the (a flag) except with "." and ".." directories omitted.

__c flag:__ when used with the (t flag) sort time by last (file change).
When used with the (l flag) sort by creation time and output modification time.
when used with the (l flag) and (t flag) sort by and output creation time.

__i flag:__ output the inode of each file/directory
</p>
