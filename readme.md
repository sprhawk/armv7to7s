convert armv7 to armv7s arch type
================================

reference to http://www.galloway.me.uk/2012/09/hacking-up-an-armv7s-library/

built binary files: https://github.com/downloads/sprhawk/armv7to7s/bin.zip


hack armv7 lib to armv7s lib:

1. extract armv7 lib from a fat bin:

    ```shell
    lipo -thin armv7 fatbin -output armv7.a
    ```

2. extract object file from armv7 lib:

    ```shell
    ar -x armv7.a
    ``` 

3. convert all armv7 object file to armv7s object file

    ```shell
    find . -name "*.o" -exec ./armv7to7s {} {}7s \;
    ```

4. archive all armv7s object file into a static lib

    ```shell
    ar -r armv7s.a *.o7s
    ```

5. add armv7s lib into original fat bin

    ```shell
    xcrun -sdk iphoneos lipo -create fatbin armv7s.a -output newfatbin
    ```

