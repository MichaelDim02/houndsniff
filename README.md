# houndsniff
Houndsniff is a minimal hash identification tool written in C that uses a database to compare a hash's features to characteristics of other common hashing algorithm results. It also prints out the percentages of likelihood for each hashing alogirthm to be the one that produced the hash based on their popularity. Email hashes that I missed at <mk@mcdim.xyz>

Website: https://mcdim.xyz/projects/hs.html

By Michael Constantine Dimopoulos, et al

with significant contributions by [Christopher Wellons](https://github.com/skeeto) and revisions & suggestions by [Martin K.](https://github.com/kurahaupo) as well as tuu and fizzie on ##c on Freenode.

Current version: 2.0

Also, check out [this](https://github.com/sal55/langs/tree/master/hash)!

![Screenshot](https://blogger.googleusercontent.com/img/a/AVvXsEh7UuJAMRdL4MOA82DH7C2g78X1t_kvsQuKcG-Cww6SqbZ68f_G8TZ3ibOJi7s09bMopa34NkzCbWILgWo0budEUbSlsTtK6GUDogOkZvtZQ0lqhiz2GBBkQkzR7PRDosDHm5RMbcQ6gHOQH3DxL-hJy2ncIlyxIb2gU1fcs5aLaIAM83ezm2NtnrPa=s16000)

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
