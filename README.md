# houndsniff
Houndsniff is a minimal hash identification and recognition tool written in C that uses a database to compare a hash's features to characteristics of other common hashing algorithm results. Email hashes that I missed at <mk@mcdim.xyz>

Website: https://mcdim.xyz/projects/hs.html

By Michael Constantine Dimopoulos, et al

with significant contributions by [Christopher Wellons](https://github.com/skeeto) and revisions & suggestions by [Martin K.](https://github.com/kurahaupo) as well as tuu and fizzie on ##c on Freenode.

Current version: 1.9

Also, check out [this](https://github.com/sal55/langs/tree/master/hash)!

![Screenshot](https://1.bp.blogspot.com/-NoLj1A28LTk/X25thDwJ2hI/AAAAAAAA8HU/l219Zr9vgCEZlY-GnsDK2VCbBQk6Um_QACLcBGAsYHQ/s16000/hound.png)

Clone
----
```
git clone https://github.com/michaeldim02/houndsniff.git && cd houndsniff/src
```

Build & install
----
```
sudo make install
```

Usage
---
```
houndsniff [HASH]
```
or, alternatively you can use the interactive shell:
```
houndsniff -s
```
You can exit with ^C.

Thanks
----
Thanks a lot to tuu and fizzie, as well as kurahaupo on ##c @ freenode for their revisions and suggestions! (even though I've yet to implement everything). I truly appreciate the help.
