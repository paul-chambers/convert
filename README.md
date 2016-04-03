# convert
tool that compares the files in a source directory against a destination directory,
and runs an executable when the destination file is missing or older.

<pre><code> convert -v -i /path/to/source -o /path/to/destination -e ext &lt;executable&gt; %i %o

 -v  be verbose about decisions being made
 -i  path to source directory
 -o  path to destination directory
 -e  substitute this extension for the destination file (e.g. m4v)
 
 %i  substitute source filename here
 %o  substitute destination filename here
</code></pre>
