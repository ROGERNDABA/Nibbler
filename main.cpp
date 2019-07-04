/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/04 17:11:10 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include "NibblerException.hpp"
#include "Snake.hpp"

void dl_error(void) {
    std::cerr << "Error : " << dlerror() << std::endl;
}

typedef Snake *(*SNAKEALLEGRO)(int, int);
typedef void (*DELETESNAKEALLEGRO)(Snake *);

int main(int ac, char *av[]) {
    (void)av;
    (void)ac;
    void *dl_handle;

    dl_handle = dlopen("lib/libSnakeSDL.so", RTLD_LAZY | RTLD_LOCAL);
    if (!dl_handle) {
        dl_error();
        exit(EXIT_FAILURE);
    }

    SNAKEALLEGRO sa = reinterpret_cast<SNAKEALLEGRO>(dlsym(dl_handle, "createSnake"));
    Snake *ssa = NULL;
    if (!sa) {
        std::cerr << "Done!" << std::endl;
    } else {
        try {
            ssa = sa(900, 600);
            ssa->init();
        } catch (const NibblerException &e) {
            std::cerr << e.what() << '\n';
        }
    }
    DELETESNAKEALLEGRO dsa = reinterpret_cast<DELETESNAKEALLEGRO>(dlsym(dl_handle, "deleteSnake"));

    dsa(ssa);
    dlclose(dl_handle);
    return 0;
}
