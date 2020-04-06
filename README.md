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
The format of the source code must follow strict format guidelines employed by 42.
This is the sole reason for all of the funky functions and the spacing of each program.
This task is carried out 'after' writting readable code.

Along with the other requirments we are restricted by system functions that are available to us.
The allowed functions for this project are:

__write__, __opendir__, __readdir__, __closedir__, __stat__,

__lstat__, __getpwuid__, __getgrgid__, __listxattr__, __getxattr__

__time__, __ctime__, __readlink__, __malloc__, __free__,

__perror__, __strerror__, __exit__
</p>

<p>Plus, anything we've created for our libft and/or printf projects/implementations.

For this project i've refrained from including my printf implementation due to the large amount of added
work each call represents and because of the time sensitivity of the program during larger recursive calls it must handle.

I've chosen to implement merge sort for all sorting (lexographical and time).

The program uses a few stacks for storing output data but sorts using a 2d character array.

The time complexity of merge sort is O(NLogN)
and the lookup of each sorted output is O(N)

O(n) + O(n log(n)) = O(n log(n)) ...Sound about right??

Output is not buffered and is noticeably slower during large recursive calls.

## Program Features

<p>My implementation covers all required flags plus the bonus flags A, c, i.

__A flag:__ same as the (a flag) except with "." and ".." directories omitted.

__c flag:__ when used with the (t flag) sort time by last (file change).
When used with the (l flag) sort by creation time and output modification time.
when used with the (l flag) and (t flag) sort by and output creation time.

__i flag:__ include the inode of each file/directory with output
</p>

## Using This Program:

__*requires git*__

__*headers and src/ls_get_info3.c modified to run on https://repl.it*__

<p>From a command line; clone the repository.</p>
<pre>$> git clone https://github.com/fractalfox01/ft_ls.git
$> cd ft_ls
$> make</pre>
