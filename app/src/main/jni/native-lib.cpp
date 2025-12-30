#include <jni.h>
#include <string>
#include <thread>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>

#include "Il2Cpp/il2cpp_dump.h"
#include "Includes/log.h"

#define libName "libil2cpp.so"

bool isLibraryLoaded(const char *libraryName) {
    char line[512] = {0};
    FILE *fp = fopen("/proc/self/maps", "rt");
    if (fp != nullptr) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, libraryName)) {
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}

void dump_thread() {

    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
      
    sleep(4);
    
    auto il2cpp_handle = dlopen(libName, 4);
    il2cpp_dump(il2cpp_handle);
}

__attribute__((constructor))
void lib_main() {
    
    std::thread(dump_thread).detach();
}
