cmd_Release/clipboard.node := c++ -bundle -undefined dynamic_lookup -Wl,-no_pie -Wl,-search_paths_first -mmacosx-version-min=10.13 -arch x86_64 -L./Release -stdlib=libc++  -o Release/clipboard.node Release/obj.target/clipboard/clipboard.o -framework CoreFoundation -framework ApplicationServices -framework Carbon