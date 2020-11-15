#pragma once

extern "C" {

    const char *get_script_path(void);
    int launch_file(const char* fn);
    int launcher(const char* filename);

}

