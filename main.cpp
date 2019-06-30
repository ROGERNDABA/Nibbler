/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/06/30 22:11:09 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include "Snake.hpp"

void dl_error(void) {
    std::cerr << "Error : " << dlerror() << std::endl;
}

typedef Snake *(*SNAKEALLEGRO)(int, int);
typedef void (*DELETESNAKEALLEGRO)(Snake *);

int main(int ac, char *av[]) {
    void *dl_handle;

    dl_handle = dlopen("SnakeAllegro/SnakeAllegro.so", RTLD_LAZY | RTLD_LOCAL);
    if (!dl_handle) {
        dl_error();
    }

    SNAKEALLEGRO sa = reinterpret_cast<SNAKEALLEGRO>(dlsym(dl_handle, "createSnakeAllegro"));
    Snake *ssa;
    if (!sa) {
        std::cerr << "Done!" << std::endl;
    } else {
        ssa = sa(900, 600);
    }
    DELETESNAKEALLEGRO dsa = reinterpret_cast<DELETESNAKEALLEGRO>(dlsym(dl_handle, "deleteSnakeAllegro"));

    dsa(ssa);
    dlclose(dl_handle);
    return 0;
}
