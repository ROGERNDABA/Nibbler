/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:51:21 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/05 11:23:31 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include "NibblerException.hpp"
#include "Snake.hpp"

void dl_error(void) {
    std::cerr << "Error : " << dlerror() << std::endl;
}

typedef Snake *(*SNAKE)(int, int);
typedef void (*DELETESNAKE)(Snake *);

int main(int ac, char *av[]) {
    (void)av;
    (void)ac;
    void *dl_handle;

    dl_handle = dlopen("lib/libSNAKE.so", RTLD_LAZY | RTLD_LOCAL);
    if (!dl_handle) {
        dl_error();
        exit(EXIT_FAILURE);
    }

    SNAKE sa = reinterpret_cast<SNAKE>(dlsym(dl_handle, "createSnake"));
    Snake *ssa = NULL;
    if (!sa) {
        std::cerr << "Done!" << std::endl;
    } else {
        try {
            ssa = sa(900, 600);
            ssa->init();
            std::cout << "++++++ " << ssa->getEvent() << " ++++++" << std::endl;

        } catch (const NibblerException &e) {
            std::cerr << e.what() << '\n';
        }
    }
    DELETESNAKE dsa = reinterpret_cast<DELETESNAKE>(dlsym(dl_handle, "deleteSnake"));

    dsa(ssa);
    dlclose(dl_handle);
    return 0;
}
