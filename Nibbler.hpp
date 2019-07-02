/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:13 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/02 19:24:37 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Snake.hpp"

class Nibbler {
   private:
   public:
    class NibblerException : std::exception {
       public:
        NibblerException(void);
        NibblerException(NibblerException const &);
        NibblerException &operator=(NibblerException const &);
        virtual const char *what() const throw();
    };

    Nibbler();
    Nibbler(Nibbler const &);
    Nibbler &operator=(Nibbler const &);
    ~Nibbler();
};

#endif  //NIBBLER_HPP