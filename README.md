# houndsniff
Houndsniff is a hash identification and recognition tool written in C that uses an SQLite database to compare a hash's features to characteristics of other commong hashing algorithm results. Email hashes that we missed at houndsniff@protonmail.com

![Screenshot](https://1.bp.blogspot.com/-vMfrFuul7Bc/X25oun-gQaI/AAAAAAAA8HA/dZ7n8jWByj4BE1VvbyoXp99gsPFZAlzjwCLcBGAsYHQ/s16000/hound.png)

Clone & Install
----
git clone https://github.com/michaeldim02/houndsniff.git && chmod +x hound

Compile
----
gcc upp.h upp.c main.c select.c select.h -lsqlite3 -std=c99 -o hound
