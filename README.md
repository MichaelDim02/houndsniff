# houndsniff
Houndsniff is a minimal hash identification and recognition tool written in C that uses an SQLite database to compare a hash's features to characteristics of other common hashing algorithm results. Email hashes that I missed at houndsniff@protonmail.com

![Screenshot](https://1.bp.blogspot.com/-NoLj1A28LTk/X25thDwJ2hI/AAAAAAAA8HU/l219Zr9vgCEZlY-GnsDK2VCbBQk6Um_QACLcBGAsYHQ/s16000/hound.png)

Clone & Install
----
git clone https://github.com/michaeldim02/houndsniff.git && cd houndsniff && chmod +x hound

Compile (c90)
----
gcc main.c select.c -lsqlite3 -std=c90 -o hound

Thanks
----
Thanks a lot to tuu and fizzie, as well as Martin K. on ##c @ freenode for their revisions and suggestions! (even though I've yet to implement everything). I truly appreciate the help.
