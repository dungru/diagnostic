# Diagnostic

# Build Code 1st time
```
make redis
```
# Build diag_engine.so
```
make
```
# Start Redis Server
```
./redis-server redis.conf

# Another Terminal
./redis-cli

# Successful Output
127.0.0.1:6379> MODULE LIST
1) 1) "name"
   2) "diag_engine.so"
   3) "ver"
   4) (integer) 1
   5) "path"
   6) "./diag_engine.so"
   7) "args"
   8) (empty array)
```
# Fix your Coding Style
```
.ci/check-format.sh
```