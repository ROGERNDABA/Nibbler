/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:24:13 by Roger Ndaba       #+#    #+#             */
/*   Updated: 2019/07/05 12:32:38 by Roger Ndaba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "NibblerException.hpp"
#include "Snake.hpp"

typedef Snake *(*SNAKE)(int, int);
typedef void (*DELETESNAKE)(Snake *);

class Nibbler {
   private:
    int _w;
    int _h;
    int _lib;
    int _softExit;
    void *_dl;
    // bool _started;
    std::map<int, std::string> _libs;

   public:
    class NibblerExceptionE : public NibblerException {
       private:
        std::string _exc;

       public:
        NibblerExceptionE(std::string);
        NibblerExceptionE(NibblerExceptionE const &);
        NibblerExceptionE &operator=(NibblerExceptionE const &);
        virtual const char *what() const throw();
    };

    Nibbler();
    Nibbler(std::string, std::string, std::string);
    Nibbler(Nibbler const &);
    Nibbler &operator=(Nibbler const &);
    ~Nibbler();

    void setup(std::string);
};

#endif  //NIBBLER_HPP